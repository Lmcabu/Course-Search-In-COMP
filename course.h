#include <string>
using namespace std;


class Course{
    
    public:
    Course();
    //Course(string courseName,string preRequisite,int creditValue,string link);
    void setValue(string courseName,string preRequisite,string creditValue,string link);

    private:
    string  m_courseName;
    string m_preRequisite;
    string m_creditValue;
    string m_link;


};

void Course::setValue(string courseName,string preRequisite,string creditValue,string link){
    m_courseName=courseName;
    m_preRequisite=preRequisite;
    m_creditValue=creditValue;
    m_link=link;
}
