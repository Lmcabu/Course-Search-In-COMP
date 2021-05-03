#include<bits/stdc++.h>
using namespace std;

const int HASH_SIZE=100;
vector<string> container;
struct hash_node{
	int number;
	string key;
	hash_node* next;
	hash_node(string a="",int b=0,hash_node* c=NULL);
};
hash_node* hash_chain=NULL;
string word;

bool ReadFile(string source);
void PrintContainer();
void CreatHashTable();
int Hash(string &key);
char Cut(char c);
void SearchFor(string word);
void instruction();
void DeleteHashTable();

int main()
{
	instruction();
	if(ReadFile("test.txt")){
		//PrintContainer();
		CreatHashTable();
		cout<<"Please enter you key: ";
		while((cin>>word)&&word!="END"){
			SearchFor(word);
			cout<<"Please enter you key: ";
		}
		DeleteHashTable();
	}
	return 0;
}

void instruction(){//程序介绍 
	cout<<"Programme: Search.cpp"<<endl;
	cout<<"Author: Wsine"<<endl;
	cout<<"Date: 2014-11-29"<<endl;
	cout<<"Exit key is 'END'"<<endl<<endl;
}

bool ReadFile(string source){//读取文件并存储 
	ifstream fin;
	fin.open(source.c_str());
	if(!fin){//打开文件失败 
		cout<<"Unable to open "<<source<<"."<<endl;
		return false;
	}
	//cout<<"open success"<<endl;
	container.clear();
	char buffer[1024]={0};
	int k=0;
	string temp;
	while(!fin.eof()){
		buffer[k++]=fin.get();
		//断句符有三个 
		if(buffer[k-1]=='.'||buffer[k-1]=='?'||buffer[k-1]=='!'){
			temp=buffer;
			container.push_back(temp);
			memset(buffer,0,1024);
			k=0;
			while(!fin.eof()){
				if(isalpha(buffer[k]=fin.get())){
					k=1;
					break;
				}
			}
		}
	}
	fin.close();
	cout<<"succeed to open "<<source<<"."<<endl;
	return true;
}

void PrintContainer(){//打印函数供测试使用 
	for(int i=0;i<container.size();i++)
		cout<<container[i]<<endl;
}

int Hash(string &key){//哈希 string转int 
    int seed=31;
    int hash=0;
    int strln=key.length();
    for(int i=0;i<strln;i++)
        hash=(hash*seed+key[i])%HASH_SIZE;
    return hash%HASH_SIZE;
}

char Cut(char c){//自定义切割函数 
	if(isalpha(c)||c=='\0')
		return c;
	else
		return ' ';
}

void CreatHashTable(){//生成哈希表 
	hash_chain=new hash_node [HASH_SIZE];
	for(int i=0;i<HASH_SIZE;i++){//初始化 
		hash_chain[i].key="";
		hash_chain[i].number=0;
		hash_chain[i].next=NULL;
	}
	int pos;
	string temp;
	for(int i=0;i<container.size();i++){
		temp=container[i];//去除结尾符号 
		transform(temp.begin(),temp.end(),temp.begin(),Cut);
		//cout<<container[i]<<endl;
		istringstream iss(temp);
		while(iss>>temp){//读取单词 
			//cout<<temp<<endl;
			pos=Hash(temp);
			hash_node* p1=&hash_chain[pos];
			if(p1->key==""){
				p1->key=temp;
				p1->number=i;
			}
			else{
				bool repeat=false;
				while(p1->next!=NULL){
					if(temp==p1->key&&i==p1->number){
						repeat=true;
						break;
					}
					p1=p1->next;
				}
				if(temp==p1->key&&i==p1->number){
					repeat=true;
				}
				if(repeat)
					continue;
				hash_node* pnew=new hash_node(temp,i,NULL);
				pnew->next=p1->next;
				p1->next=pnew;
			}
		}
	}
}

hash_node::hash_node(string a,int b,hash_node* c){//结构体构造函数 
	key=a;
	number=b;
	next=c;
}

void SearchFor(string word){//搜索函数 
	int pos=Hash(word),k=1;
	hash_node* p1=&hash_chain[pos];
	while(p1!=NULL){//遍历链表 
		if(p1->key==word){
			cout<<endl;
			cout<<"Sentence "<<k++<<" :"<<endl;
			cout<<container[p1->number]<<endl;
		}
		p1=p1->next;
	}
	cout<<endl;
}

void DeleteHashTable(){//删除哈希表 
	hash_node *p1,*p2,*p3;
	for(int i=0;i<HASH_SIZE;i++){
		p1=&hash_chain[i];
		p2=p1->next;
		while(p2!=NULL){
			p3=p2->next;
			delete p2;
			p2=p3;
		}
	}
	delete [] hash_chain;
	container.clear(); 
}
