#include <iostream>
#include "Course.h"
#include <string>
#include <vector>
#include <fstream> 
#include "HASH_NODE.h"

using namespace std;


const int COURSE_SIZE = 83;
Course courseList[COURSE_SIZE];

const int HASH_SIZE = 111;
HASH_NODE* hashTable[HASH_SIZE];

struct course{
    string s_courseID;
    string  s_courseName;
    string s_preRequisite;
    string s_creditValue;
    string s_link;
};

struct RESULT{
    Course result_course;
    int show_times = 0;
    RESULT* next = NULL;
};


//data input
void ini();
string readInfor(int);
course informationProcess(string);
string changeToLower(string source);

//data search
int Hash(string word); // input a word and return the hash number of the word 
void iniHashTable(); // initiallize the HashTable
string* keyWordProcess(string keyword,int& wordNumber); // divided the key words into different word part and return the link of the Dynamic array
void loadResult(RESULT* resultHead, HASH_NODE* node); // input the head of result and load answer to the result
RESULT *hashSearch(string keyword);
bool compare(string a, string b);
void insert(COURSE_INDEX* &courseIndex, COURSE_INDEX* index);
void add(string word, int index);
vector<string> split(const string& str);


//data output
void printResult(RESULT*);




int main(){
     
    ini();
    iniHashTable();
    /*
    int doculinenum;
    string keyword;
    string actkey
    readInfor(81);
    informationProcess(result);
    cout << "Please input the key word: " ;
    cin >> keyword;
    changeToLower(keyword);
    */




    //introduction information
    //request for input
    string keyword; char next;
    do{
        
        cout<<"Welcome to the course search application!"<<endl;
        cout<<"Please input keyword(s) of the course(s) you want to search for:"<<endl;
        cin>>keyword;
        RESULT* result=hashSearch(keyword);
        printResult(result);


        cout<<"Do you want to search for other courses?('Y' for yes and press any other key for no)"<<endl;
        cin>>next;
    }while(next=='Y');
 

    return 0;
}






// data input
//initialize all courses
void ini(){
    for(int i=0;i<COURSE_SIZE;i++){
        //get information from the document
        string inforString=readInfor(i+2);
        course inforStruct=informationProcess(inforString);
        
        Course newCourse=Course();
        newCourse.setValue(inforStruct.s_courseID,inforStruct.s_courseName,inforStruct.s_preRequisite,inforStruct.s_creditValue,inforStruct.s_link);
        courseList[i]=newCourse;
    }

}

//read from document
string readInfor(int sequenceNum){
    ifstream  myfile;
    myfile.open("D:\\Visual code\\COMP 1011 Project\\Course-Search-In-COMP\\data.tsv", ios::out | ios::in );

    if(!myfile.is_open()) {
        cout << "open false";
    }
    
    string result;

    for(int i=0;i<sequenceNum;i++){
        getline(myfile,result);
    } 
    return result;
}

//deal with "1  COMP1011   Programming Fundamentals    Null    3   https://www.comp.polyu.edu.hk/files/COMP1011_Programming_Fundamentals_Dec2018.pdf"
course informationProcess(string infor){
    
    
    string cid;
    string cname;
    string cpre;
    string ccredit;
    string clink;

    size_t n = infor.find("\t");
    //level
    string level = infor.substr(0,n);

    infor = infor.substr(n + 1);
    n = infor.find("\t");
    //course id
    cid = infor.substr(0, n);

    infor = infor.substr(n + 1);
    n = infor.find("\t");
    //course name
    cname = infor.substr(0, n);

    infor = infor.substr(n + 1);
    n = infor.find("\t");
    //pre-requisite
    cpre = infor.substr(0, n);

    infor = infor.substr(n + 1);
    n = infor.find("\t");
    //credit value
    ccredit = infor.substr(0, n);
    
    infor = infor.substr(n + 1);
    n = infor.find("\t");
    //link
    clink = infor.substr(0, n);

    course a;
    a.s_courseID=cid;
    a.s_courseName=cname;
    a.s_preRequisite=cpre;
    a.s_creditValue=ccredit;
    a.s_link=clink;

    return a;
}


string changeToLower(string source) {
    string result = source;
    for(int i = 0; i<source.length(); i++) {
        result[i] = tolower(source[i]);
    }
    return result;
}



// data search
//Hash function
int Hash(string s){
    const int p =31;
    const int m =111;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s){
        hash_value = (hash_value + (c - 'a' + 1)*p_pow) % m;
        p_pow = (p_pow * p)%m;
    }
    return hash_value;
}

void iniHashTable(){
     for(int i=0;i<111;i++){ 
        HASH_NODE* temp= new HASH_NODE();
        hashTable[i]= temp;
    }

    for(int i=0;i<83;i++){
        Course currentCourse=courseList[i];
        string currentCourseName=courseList[i].getCourseName();
        vector<string> elements=split(currentCourseName);

        vector<string>::iterator it;
        for(it=elements.begin();it!=elements.end();it++){
            add(*it,i);
        }

    }
}

string* keyWordProcess(string keyword, int& wordNumber) {
    wordNumber++;
    char next;
    int i = 0;

    //remove started blank and end blank
    keyword.erase(0,keyword.find_first_not_of(" "));
    keyword.erase(keyword.find_last_not_of(" ")+1);

    // if their is no key word return null
    if(i == keyword.length()) {
        return NULL;
    }

    keyword = changeToLower(keyword);
    
    // cout word number;
    while(i < keyword.length()) {
        if(keyword[i] == ' ') {
            wordNumber++;
            while(keyword[i+1] == ' ' && (i+1 < keyword.length())) {
                i++;
            } // skip blank space if necessary
        }
        i++;
    }

    string* wordList = new string[wordNumber];

    // ini the word list
    for(int i = 0; i < wordNumber; i++) {
        wordList[i] = "";
    }

    int wordindex = 0;
    int index = 0;


    // add word to word list;
    while(index < keyword.length()) {
        if(keyword[index] == ' ') {
            while(keyword[index+1] == ' ' && (index+1 < keyword.length())) {
                index++;
            } // skip blank space if necessary
            index++;
            wordindex++; // move to next word
        }
        else {
            wordList[wordindex] = wordList[wordindex] + keyword[index];
            index++;

        }
    }

    return wordList;

}

void loadResult(RESULT* resultHead, HASH_NODE* node) {
    COURSE_INDEX* currentCouresIndexPtr = node -> getCourseIDPtr();

    if(resultHead -> show_times == 0) {

        int courseID = currentCouresIndexPtr -> course_index;
        resultHead -> result_course = courseList[courseID];
        resultHead -> show_times =  resultHead -> show_times + 1;

        currentCouresIndexPtr  = currentCouresIndexPtr -> next; //move to next ID

        while(currentCouresIndexPtr != NULL) {
            bool needNew = true;
            RESULT* currentResult = resultHead;
            while(currentResult != NULL) {
                // judeg if there is the same coure in the result
                if(currentResult -> result_course.getCourseName() ==  courseList[currentCouresIndexPtr -> course_index].getCourseName()) {
                    currentResult -> show_times = currentResult -> show_times + 1;
                    needNew = false;
                    break;
                }
            }

            if(needNew){
                currentResult = new RESULT();
                // add information to new result
                currentResult -> result_course = courseList[currentCouresIndexPtr -> course_index];
                currentResult -> show_times = currentResult -> show_times + 1;

                //add new result to the total result
                RESULT* tempPtr = resultHead;
                resultHead = currentResult;
                resultHead -> next = tempPtr;
            }

        }
    }
    else {
        // look up all the course ID;
        while(currentCouresIndexPtr != NULL) {
            bool needNew = true;
            RESULT* currentResult = resultHead;
            while(currentResult != NULL) {
                // judeg if there is the same coure in the result
                if(currentResult -> result_course.getCourseName() ==  courseList[currentCouresIndexPtr -> course_index].getCourseName()) {
                    currentResult -> show_times = currentResult -> show_times + 1;
                    needNew = false;
                    break;
                }
            }

            if(needNew){
                currentResult = new RESULT();
                // add information to new result
                currentResult -> result_course = courseList[currentCouresIndexPtr -> course_index];
                currentResult -> show_times = currentResult -> show_times + 1;

                //add new result to the total result
                RESULT* tempPtr = resultHead;
                resultHead = currentResult;
                resultHead -> next = tempPtr;
            }

        }

    }

}

RESULT *hashSearch(string keyword){
    int wordNumber = 0;
    RESULT* resultHead = new RESULT();
    string* wordList = keyWordProcess(keyword, wordNumber); // return dynamic string list with lower words
    for(int i = 0; i < wordNumber; i++) {
        int hashNumber = Hash(wordList[i]);
        HASH_NODE* hashHead = hashTable[hashNumber];
        while(hashHead != NULL) {
            if(hashHead -> getWord() == wordList[i]) {
                loadResult(resultHead, hashHead);
            }
            hashHead = hashHead -> next;
        }
    }
    return resultHead; 
}

bool compare(string a, string b){
    if(a.length()!=b.length()) return false;
    int len=a.length();
    for(int i=0;i<len;i++){
        if(a[i]!=b[i]) return false;
    }
    return true;
}

void insert(COURSE_INDEX* &courseIndex, COURSE_INDEX* index) {
    index->next = courseIndex;
    courseIndex = index;
}

void add(string word, int index){
    int hashCode=Hash(word);
    HASH_NODE* current=hashTable[hashCode];

    bool dup=false;
    //  may need to change
    while(current -> getWord() != ""){
        if(compare(word,current->getWord())){
            dup=true;
            
            COURSE_INDEX *newCourseIndex=new COURSE_INDEX;
            newCourseIndex->course_index=index;

            COURSE_INDEX *temp=current->getCourseIDPtr();
            insert(temp,newCourseIndex);

            current->setCourseIndex(temp);   
        }
        current=current->next;
    }

    if(!dup){
        current->next=new HASH_NODE;
        COURSE_INDEX *newCourseIndex=new COURSE_INDEX;
        newCourseIndex->course_index=index;
        current->next->setHashNode(word,newCourseIndex);
        
    }

}

vector<string> split(const string& str)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(" ", prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + 1;
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

//data output

void printResult(RESULT* result){
    //sorting
    RESULT sortedResultList[COURSE_SIZE];
    int index = 0;

    while (result != NULL) {
        sortedResultList[index++] = *result;
        result = result->next;
    }

    for (int i = 0; i < index; i++) {
        for (int j = i + 1; j < index; j++) {
            if (sortedResultList[i].show_times <sortedResultList[j].show_times) {
                RESULT temp = sortedResultList[i];
                sortedResultList[i] = sortedResultList[j];
                sortedResultList[j] = temp;
            }
        }
    }


    for(int i=0;i<index;i++){
       cout<< sortedResultList->result_course.getCourseID()<<"\t"
           << sortedResultList->result_course.getCourseName()<<"\t"
           << sortedResultList->result_course.getPreRequisite()<<"\t"
           << sortedResultList->result_course.getCreditValue()<<"\t"
           << sortedResultList->result_course.getLink()<<"\t"
           <<endl;
    }

    
}