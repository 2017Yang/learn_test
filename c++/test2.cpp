/*************************************************************************
    > File Name: test2.cpp
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2017年10月24日 星期二 08时58分50秒
 ************************************************************************/
#include <iostream>
using namespace std;
template<typename T>
T Max(T a, T b)
{
	return a>b?a:b;
}
int main()
{
	int ret = 0;
	ret = Max(4,3);
	cout<<ret<<endl;
	return 0;
}
