/***************** 朴素的模式匹配算法 ******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LinkNum 3	//全局设置链表中节点存储数据的个数
#define ERROR -1
#define OK 1

typedef int Status;

//返回子串subString在主串mainSring中第pos个字符之后的位置。若不存在则返回值为0。 
int Index(char * mainString, int mainLen ,char *subString, int subLen) {
	int i = 0,j = 0;
	//跳出循环两种可能，i=mainLen说明已经遍历完主串；j=subLen说明子串遍历完成
	while (i < mainLen && j < subLen) {
		if (mainString[i] == subString[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	//判断匹配是否成功
	if (j == subLen) {
		return i - j + 1;	//返回主串的第几个位置
		//return i - j;		//返回主串的下标
	}
	//匹配失败返回0
	return 0;
}

int main() {

	char str1[] = "I am a dog!";
	char str2[] = "dog";

	int num = Index(str1, strlen(str1), str2, strlen(str2));

	printf("Index = %d", num);

	return 0;
}
