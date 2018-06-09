/*************************************************************************
    > File Name: test1.cpp
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2017年10月11日 星期三 09时16分21秒
 ************************************************************************/
#include <iostream>
#include <string.h>
using namespace std;
class person
{
	public:
		int age;
		char name[10];
		person(int a, char* n);
		void print();
};

person::person(int a, char *n)
{
	age = a;
	strcpy(name,n);
}
void person::print()
{
	cout<<"age: "<<this->age<<endl;
	cout<<"name: "<<this->name<<endl;
}
int main()
{
	person p(1,"aasd");
	p.print();
}
