
struct COURSE_INDEX {
    int course_index;
    COURSE_INDEX* next = NULL;
};

class HASH_NODE {
    public:
    HASH_NODE* next;
    string getWord();
    COURSE_INDEX* getCourseIDPtr();
    HASH_NODE();
    void setHashNode(string _word, COURSE_INDEX* _courseIDPtr);
<<<<<<< HEAD
=======
    
>>>>>>> 4f04ae318246b8a76dbc00fdc079a6f9a28db9f9
    void setCourseIndex(COURSE_INDEX* _courseIDPtr);

    private:
    string word;
    COURSE_INDEX* courseIDPtr;

};


HASH_NODE::HASH_NODE() {
    word = "";
    courseIDPtr = new COURSE_INDEX();
}

void HASH_NODE::setHashNode(string _word, COURSE_INDEX* _courseIDPtr) {
    word = _word;
    courseIDPtr = _courseIDPtr;
}

string HASH_NODE::getWord() {
    return word;
}

COURSE_INDEX* HASH_NODE::getCourseIDPtr() {
    return courseIDPtr;
}

void HASH_NODE::setCourseIndex(COURSE_INDEX* _courseIDPtr) {
    courseIDPtr = _courseIDPtr;
}