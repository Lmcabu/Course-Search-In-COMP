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

const int HASH_SIZE = 11;
HASH_NODE* hashTable[HASH_SIZE];

struct RESULT{
    Course result_course;
    int show_times;
    RESULT* next;
};

string changeToLower(string source); // change a string to lower and return a new lower string
int Hash(string word); // input a word and return the hash number of the word 
void iniHashTable(); // initiallize the HashTable
string* keyWordProcess(string keyword,int& wordNumber); // divided the key words into different word part and return the link of the Dynamic array
void loadResult(RESULT* resultHead, const HASH_NODE* node); // input the head of result and load answer to the result


//change a string to lower and return a new lower string
string changeToLower(string source) {
    string result = source;
    for(int i = 0; i<source.length(); i++) {
        result[i] = tolower(source[i]);
    }
    return result;
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





int main(){
    return 0;
}
