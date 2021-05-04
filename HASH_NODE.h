#include<string>
#include<iostream>


using namespace std;

struct COURSE_ID {
    int course_id;
    COURSE_ID* next = NULL;
};

class HASH_NODE {
    public:
    HASH_NODE* next;
    string getWord();
    COURSE_ID* getCourseIDPtr();
    HASH_NODE();
    void setHashNode(string _word, COURSE_ID* _courseIDPtr);

    private:
    string word;
    COURSE_ID* courseIDPtr;

};


HASH_NODE::HASH_NODE() {
    word = "";
    courseIDPtr = new COURSE_ID();
}

void HASH_NODE::setHashNode(string _word, COURSE_ID* _courseIDPtr) {
    word = _word;
    courseIDPtr = _courseIDPtr;
}

string HASH_NODE::getWord() {
    return word;
}

COURSE_ID* HASH_NODE::getCourseIDPtr() {
    return courseIDPtr;
}