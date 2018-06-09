/*************************************************************************
    > File Name: test.c
    > get_opt_long.c函数的用法
	> Author: yangyong
    > Created Time: 2018年05月30日 星期三 16时43分39秒
 ************************************************************************/

#include<stdio.h>
#include <getopt.h>
char *l_opt_arg;
char* const short_options = "nbl:";
struct option long_options[] = {
{ "name", 0, NULL, 'n' },
{ "bf_name", 0, NULL, 'b' },
{ "love xxxx", 2, NULL, 'l' },
{ 0, 0, 0, 0},
};

int printf_1()
{
	while(1) {
		sleep(1);
		printf("my name is xl.\n");
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int c;
	while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
		switch (c)
		{
			case 'n':
				printf_1();
				break;
			case 'b':
				printf("His name is ST.\n");
				break;
			case 'l':
				l_opt_arg = optarg;
				printf("Our love is %s!\n", l_opt_arg);
			break;
		}
	}
	return 0;
}
	
