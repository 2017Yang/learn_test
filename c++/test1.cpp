/*************************************************************************
    > File Name: test1.cpp
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2017年10月18日 星期三 19时26分00秒
 ************************************************************************/
#include <iostream>
using namespace std;
#include <string.h>
class Employee
{
	public:
		Employee(int num, char*pName);
		void showPersonInfo();
		virtual void showEmployeeSalary();
	protected:
		int number;
		char name[10];
		int basicSalary;
};
Employee::Employee(int num, char *pName){
	number = num;
	strncpy(name,pName,strlen(name));
	basicSalary = 1000;
}
void Employee::showPersonInfo(){
	cout<<"number: "<<number<<endl;
	cout<<"name: "<<name<<endl;
}
void Employee::showEmployeeSalary(){
	cout<<basicSalary<<endl;
}
#if 1
class Salesman:public Employee
{
	public:
		Salesman(int num, char*pName,int s);
		void showEmployeeSalary();
	protected:
		int sales;
		static int commrate;
};
int Salesman::commrate = 0;
Salesman::Salesman(int num,char *pName,int s):Employee(num,pName){
	sales = s;
}
void Salesman::showEmployeeSalary(){
	commrate = 5;
	cout<<"Salesman salary: "<< basicSalary+sales*commrate<<endl;
}
#endif
int main()
{
	
	Employee em(1,"yy");
	em.showPersonInfo();
	em.showEmployeeSalary();
	cout<<endl;
	
	Employee *pEm = &em;
	pEm->showPersonInfo();
	((Salesman*)pEm)->showEmployeeSalary();
	
	cout<<endl;

	Salesman sm(2,"hh",5);	
	Salesman *pSm = &sm;
	pSm->showPersonInfo();

	sm.showPersonInfo();
	sm.showEmployeeSalary();
	return 0;
}
