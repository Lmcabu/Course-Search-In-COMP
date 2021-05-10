#include <iostream>
#include "course.h"
#include <string>
#include <vector>
#include <fstream> // ifstream
#include "Xu'ssearch.cpp"
#include "HashSearch.cpp"
#include "HASH_NODE.h"


//test git
//test git2
using namespace std;


const int COURSE_SIZE = 83;
Course courseList[COURSE_SIZE];

struct course{
    string s_courseID;
    string  s_courseName;
    string s_preRequisite;
    string s_creditValue;
    string s_link;
};
void ini();
string readInfor(int);
course informationProcess(string);
Course *search(string);
void printResult(RESULT*);



//initialize all courses
 void ini(){
    for(int i=0;i<83;i++){
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
    myfile.open("data.tsv", ios::out | ios::in );
    
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
    string clink = infor.substr(0, n);

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




RESULT* sorting(RESULT* result) {
    RESULT sortedResultList[81];
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

    return sortedResultList;
}




void printResult(RESULT* result){
    //sorting
    RESULT sortedResultList[81];
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






int main(){
     
    ini();
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
        result=sorting(result);
        printResult(result);


        cout<<"Do you want to search for other courses?('Y' for yes and press any other key for no)"<<endl;
        cin>>next;
    }while(next=='Y');
 

    return 0;
}