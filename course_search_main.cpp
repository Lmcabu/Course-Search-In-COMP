#include <iostream> // iostream
#include "course.h"
#include <string>
#include <vector>
#include <sstream> //istringstream
#include <iostream> // cout
#include <fstream> // ifstream
 
using namespace std;

Course courseList[81];
struct course{
    string  s_courseName;
    string s_preRequisite;
    string s_creditValue;
    string s_link;
};
void ini();
string readInfor(int);
course informationProcess(string);
Course search(string);
void printResult(Course result);



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

//return the course object
//case-sensitive
Course search(string keyword){
    Course a;
    return a;
}

void printResult(Course result){

}






int main(){
     
     ini();

    //introduction information
    //request for input
    

    return 0;
}
