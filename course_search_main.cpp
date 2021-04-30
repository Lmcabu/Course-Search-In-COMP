#include <iostream> // iostream
#include "Course.h"
#include <string>  // string
#include <vector>
#include <sstream> //istringstream
#include <iostream> // cout
#include <fstream> // ifstream
 
using namespace std;//Hello world


const int COURSE_SIZE = 81;
Course courseList[COURSE_SIZE];


struct course{
    string  s_courseName;
    string s_preRequisite;
    string s_creditValue;
    string s_link;
};

struct course_link_list{
    Course value;
    course_link_list* next; 
};


void ini();
string readInfor(int);
course informationProcess(string);
Course *search(string);
void printResult(Course result);
string changeToLower(string source); // change a string to lower and return a new lower string



//initialize all courses
 void ini(){
    for(int i=0;i<81;i++){
        //get information from the document
        string inforString=readInfor(i+1);
        course inforStruct=informationProcess(inforString);
        
        courseList[i]=Course();
        courseList[i].setValue(inforStruct.s_courseName,inforStruct.s_preRequisite,inforStruct.s_creditValue,inforStruct.s_link);
    }

}

//PAN Yalu read from document
string readInfor(int sequenceNum){
    return NULL;
}


//PAN Yalu deal with "COMP1011 Programming Fundamentals Null 3 https://www.comp.polyu.edu.hk/files/COMP1011_Programming_Fundamentals_Dec2018.pdf"
course informationProcess(string information){
    course a;
    return a;
}


//input a string and return its lower case;

string changeToLower(string source) {
    string result = source;
    for(int i = 0; i<source.length(); i++) {
        result[i] = tolower(source[i]);
    }
    return result;
}




//return the course object
//case-sensitive
// input keyword and return a link list of related coures

Course *search(string keyword){
    Course* head = new Course();
    Course* end = head;
    Course* current;
    int size = 1;
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
