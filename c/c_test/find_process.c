/*************************************************************************
    > File Name: find_process.c
    > Author: yangyong
    > Mail: yangyong.zh@star-net.cn 
    > Created Time: 2018年06月03日 星期日 17时06分39秒
 ************************************************************************/

#include<stdio.h>

#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<limits.h> 

#define BUFSZ PIPE_BUF 

static int find_process(char *process_name)
{
	FILE* fp; 
    int count; 
    int flag = 0;
    char buf[BUFSZ]; 
    char command[150];   
    sprintf(command, "ps -C %s|wc -l", process_name ); 
	if((fp = popen(command, "r")) == NULL) {
        printf("find fail\n");
        return -1;
    } else {
		if( (fgets(buf,BUFSZ,fp))!= NULL ){
            count = atoi(buf); 
            if((count - 1) == 0) {
                printf("%s not found\n",process_name);
                flag = -1;
            } else {
                printf("process : %s total is %d\n",process_name,(count - 1));
                flag = 0;
            }  
        }  
        pclose(fp); 
    }
	return flag;  
}


int main(int argc, char *argv[]) 
{ 
    
    if(argc < 2)  {
       perror("paras fail\n");
       return -1;
    }
    find_process(argv[1]);
    return 0;
} 

