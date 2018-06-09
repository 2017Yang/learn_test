/*************************************************************************
    > File Name: get_time.c
    > Author: yangyong 
    > Created Time: 2018年06月07日 星期四 15时02分11秒
	>获取当前的时间
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<time.h>

int main()
{	

	time_t timep;   
    struct tm *p;     
    time(&timep);   
    p = localtime(&timep);
 
    printf("%d-%d-%d %d:%d:%d\n", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                (p->tm_hour + 12), p->tm_min, p->tm_sec); 
	return 0;
}
