#include <iostream> // iostream
#include "course.h"
#include <string>  // string
#include <vector>
#include <sstream> //istringstream
#include <iostream> // cout
#include <fstream> // ifstream
#include "HASH_NODE.h"
#include "search.cpp"

int HASHSIZE=233;

struct Node{
    string word;
    CourseIndex* courseIndex;
    Node *next;
};

struct CourseIndex{
    int index;
    CourseIndex* next;
};

class HashTable{
    private:
        Node* node[233];
    public:
        HashTable();
        int hash(string word);
        void add(string word,int index);
};

HashTable::HashTable(){
    for(int i=0;i<233;i++){
        node[i]=new Node;
    }
}

int HashTable::hash(string word){
     int sum = 0;
        for (int k = 0; k < word.length(); k++)
            sum = sum + int(word[k]);
        return  sum % HASHSIZE;
}


bool compare(string a, string b){
    if(a.length()!=b.length()) return false;
    int len=a.length();
    for(int i=0;i<len;i++){
        if(a[i]!=b[i]) return false;
    }
    return true;
}

void HashTable::add(string word, int index){
    int hashCode=hash(word);
    Node* current=node[hashCode];

    bool dup=false;
    while(current->next!=NULL){
        if(compare(word,current->word)){
            dup=true;
            current->courseIndex->next=new CourseIndex;
            current->courseIndex->next->index=index;
        }
        current=current->next;
    }

    if(!dup){
        current->next=new Node;
        current->next->word=word;
        current->next->courseIndex=new CourseIndex;
        current->next->courseIndex->index=index;
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
    HashTable *hashTable=new HashTable();

    for(int i=0;i<81;i++){
      Course currentCourse=courseList[i];
        string currentCourseName=courseList[i].getCourseName();
        vector<string> elements=split(currentCourseName);

        vector<string>::iterator it;
        for(it=elements.begin();it!=elements.end();it++){
            hashTable->add(*it,i);
        }

    }
}