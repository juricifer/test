#include<iostream>
using namespace std;

class student{
	//static int number;
	int n;
	string name;

public:
void set(string str){
	static int number=0;
	name = str;
	n = ++number;
};
void print(){
	cout<<name<<":student are:"<<n<<" number\n";
};
};
/*
void student::set(string str){
	static int number=0;
	name = str;
	++number;
}

void student::print(){

	cout<<name<<":student are:"<<number<<"number\n";
}
*/
//int student::number =0;

void fun()
{
	student s1;
	s1.set("evan");
	student s2;
	s2.set("chengbi");
	s1.print();
}

int main(){
	student s;
	s.set("zewen");
	student s1;
	s1.set("evan");
	student s2;
	s2.set("chengbi");
	s1.print();
	s2.print();
	//fun();
	s.print();
}









