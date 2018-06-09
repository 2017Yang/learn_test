/*************************************************************************
    > File Name: 复制构造函数.cpp
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2017年10月12日 星期四 09时46分44秒
 ************************************************************************/
#include <iostream>
#include <string.h>
using namespace std;

class Name
{
	public:
		Name(char*pn);
		Name(const Name &Obj);
		~Name();
		void setName(char*);
		void showName();
	protected:
		char *pName;
		int size;
};
Name::Name(char *pn)
{
	cout<<"Copying:"<<pn<<endl;
	pName = new char[strlen(pn)+1];
	if (NULL != pName) strncpy(pName,pn,strlen(pn)+1);
	size = strlen(pn);
}
Name::Name(const Name &Obj)
{
	cout<<"Copy:"<<Obj.pName<<"into its own block"<<endl;
	pName = new char[strlen(Obj.pName)+1];
	if(pName != 0) strncpy(pName,Obj.pName,strlen(Obj.pName)+1);
	size = Obj.size;
}
Name::~Name()
{
	cout<<"destruct "<<pName<<endl;
	pName[0] = '\n';
	delete []pName;
	pName = NULL;
	size = 0;
}
void Name::setName(char *pn)
{
	delete []pName;
	pName = new char[strlen(pn)+1];
	if(pName != 0) strncpy(pName,pn,strlen(pn)+1);
	size = strlen(pn);
}
void Name::showName()
{
	cout<<pName<<endl;
}
int main()
{
	Name Obj1("NoName");
	Name Obj2 = Obj1;
	Obj1.showName();
	Obj2.showName();
	Obj1.setName("SuDondpo");
	Obj2.setName("DuFu");
	Obj1.showName();
	Obj2.showName();
}
