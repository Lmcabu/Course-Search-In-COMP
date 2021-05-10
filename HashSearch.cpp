#include <iostream> // iostream
#include "course.h"
#include <string>  // string
#include <vector>
#include <sstream> //istringstream
#include <iostream> // cout
#include <fstream> // ifstream
#include "HASH_NODE.h"

 
using namespace std;//Hello world


const int COURSE_SIZE = 81;
Course courseList[COURSE_SIZE];

const int HASH_SIZE = 111;
HASH_NODE* hashTable[HASH_SIZE];

struct RESULT{
    Course result_course;
    int show_times = 0;
    RESULT* next = NULL;
};

string changeToLower(string source); // change a string to lower and return a new lower string
int Hash(string word); // input a word and return the hash number of the word 
void iniHashTable(); // initiallize the HashTable
string* keyWordProcess(string keyword,int& wordNumber); // divided the key words into different word part and return the link of the Dynamic array
void loadResult(RESULT* resultHead, HASH_NODE* node); // input the head of result and load answer to the result


//change a string to lower and return a new lower string
string changeToLower(string source) {
    string result = source;
    for(int i = 0; i<source.length(); i++) {
        result[i] = tolower(source[i]);
    }
    return result;
}

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

// input keyword and wordNumber and return a wordlist. return null if there is no keyword input
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





//input the key words and return the Result link list


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
    while(current!=NULL){
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

void iniHashTable(){
     for(int i=0;i<111;i++){
        hashTable[i]=new HASH_NODE;
    }

    for(int i=0;i<81;i++){
        Course currentCourse=courseList[i];
        string currentCourseName=courseList[i].getCourseName();
        vector<string> elements=split(currentCourseName);

        vector<string>::iterator it;
        for(it=elements.begin();it!=elements.end();it++){
            add(*it,i);
        }

    }
}






