/*************************************************************************
    > File Name: arr_test.c
    > Author: yangyong
	在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
	> Created Time: 2018年05月02日 星期三 18时29分27秒
 ************************************************************************/

#include<stdio.h>
int fun(int (*arr)[4],int h,int l,int findNum)
{
	int i = 0;
	int j = 0;
	if (NULL == arr) {
		perror("arr is null");
		return -1;
	}
	j = l-1;
	while (i < h) {
		if (arr[i][j] == findNum) {
			printf("arr[i][j]: %d\n",arr[i][j]);
			break;
		}
		if (arr[i][j] >= findNum) {
			for (; j>=0; j--) {
				if (arr[i][j] == findNum) {
					printf("arr[i][j]: %d\n",arr[i][j]);
					return 0;
				}
			}
		} else {
			j = l-1;
			i++;
		}
	}
	return 0;
}
int main()
{
	int arr[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
	fun(arr,3,4,5);
	return 0;
}
