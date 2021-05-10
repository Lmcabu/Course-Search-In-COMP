#include <iostream>
#include "course.h"
#include <string>
#include <vector>

#include <fstream> // ifstream

//test git
//test git2
using namespace std;


const int COURSE_SIZE = 81;
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
void printResult(Course result);



//initialize all courses
 void ini(){
    for(int i=0;i<81;i++){
        //get information from the document
        string inforString=readInfor(i+2);
        course inforStruct=informationProcess(inforString);
        
        courseList[i]=Course();
        courseList[i].setValue(inforStruct.s_courseID,inforStruct.s_courseName,inforStruct.s_preRequisite,inforStruct.s_creditValue,inforStruct.s_link);
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

Course *search(string keyword){
    Course* head = new Course();
    Course* end = head;
    Course* current;
    int size = 1;
    keyword = changeToLower(keyword);
    for(int i = 0; i < COURSE_SIZE; i++) {
        if(changeToLower(courseList[i].getCourseName()).find(keyword) != string::npos) {
            current = &courseList[i];
            if(size == 1) {
                head = current;
                end = current;
            }
            else {
                end -> next = current;
                end = current;
            }
            size++;  
        }
    }
    return head;
    

}

void printResult(Course result){
    
}






int main(){
     
     ini();

    //introduction information
    //request for input
    

    return 0;
}