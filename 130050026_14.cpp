#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std;

class Node
{
	int num;
	char ch;
	Node * left, *right;
	public:
	Node(char c)
	{
		ch=c;
		num=0;
		left=0;
		right=0;
	}
	void add()
	{
		num++;
	}
	int cap()
	{
		return num;
	}
	char character()
	{
		return ch;
	}
	Node * l()
	{
		return left;
	}
	Node * r()
	{
		return right;
	}
	void set(Node* a, Node*b)
	{
		left=a;
		right=b;
		num = a->cap()+b->cap();
	}
};

typedef bool(*CompareFunc)(Node*, Node*); // You need to have your function pointer 
                                          // type available
bool Compare(Node* n1, Node* n2)
	{
		return n2->cap()<n1->cap() ;
	}
void visit(Node * n)
{
	if(n->l()==0 && n->r()==0){
		cout<<n->character()<<endl;
		return;
	}
	visit(n->l());
	visit(n->r());
}
	
int main(int argv, char* args[])
{
	double len=0;
	ifstream in;
	in.open(args[1],ios::in);
	char ch;
	
	priority_queue<Node*, vector<Node*>, CompareFunc> pq(Compare); 
	vector <Node*> arr;
	for(int i=0;i<256;i++)
	{
		arr.push_back(new Node((char)i));
	}
	
	while(in.get(ch)){
		//cout<<ch;
		len++;
		arr[(int)ch]->add();
	}
	for(int i=0;i<256;i++){
		if(arr[i]->cap()!=0)
		{
			pq.push(arr[i]);
		}
	}
	while(pq.size()>1)
	{
		Node *n2=pq.top();
		pq.pop();
		Node *n1=pq.top();
		pq.pop();
		Node *n = new Node('@');
		n->set(n1,n2);
		pq.push(n);
	}
	//visit(pq.top());
	stack <Node*> str;
	stack <string> num;
	map <char,string> out;
	str.push(pq.top());
	num.push("");
	in.close();
	while(!str.empty())
	{
		Node* t=str.top();
		string i = num.top();
		str.pop();
		num.pop();
		if(t->l()==0 && t->r()==0)
		{
			out[t->character()]=i;
			continue;
		}
		if(t->l()!=0){ 
			str.push(t->l());
		    num.push(i+'0');
		}
		
		if(t->r()!=0){
		    str.push(t->r());
			num.push(i+'1');
		}
	}
	/*in.open("big.txt",ios::in);
	ofstream wr,wr1;
	wr.open("out.txt",ios::app);
	wr1.open("bin.txt",ios::app);
	char c;
	while(in.get(c))
	{
		int buffer[8];
		wr<<out[c];
		int it = c;
		for (int i = 0; i < 8; ++i) {  
			buffer[i] = it & (1 << i) ? 1 : 0;
			wr1<<buffer[i];
		}
		
	}*/
	float comp=0;
	for(map<char,string>::iterator it = out.begin();it!=out.end();it++)
	{
		cout<<it->first<<"   "<<it->second<<endl;
		comp += (arr[(int)it->first]->cap())*(it->second.size());
	}
	cout<<"The compression ratio is "<<(8.0/comp)*len<<endl;
}
