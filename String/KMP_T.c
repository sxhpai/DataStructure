/********************* KMP算法 ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//返回子串 str 的 next数组
void get_next(char *str, int *next) {

	int i = 1;	
	int j = 0;	
	next[1] = 0;
	while (i < str[0]) {
		if (j == 0 || str[i] == str[j]) {	//str[i] 表示后缀的单个字符
			i++;							//str[j] 表示前缀的单个字符
			j++;
			next[i] = j;
		}
		else {
			j = next[j];	//j值回溯
		}
	}
}

//返回子串 str 的 nextval数组
void get_nextval(char *str, int *nextval) {
	int i = 1;
	int j = 0;
	nextval[1] = 0;
	while (i < str[0]) {	//此处str[0]代表串str的有效长度
		if (j == 0 || str[i] == str[j]) {	//str[i]表示后缀的单个字符
			i++;							//str[j]表示前缀的单个字符
			j++;
			if (str[i] != str[j]) {		//若当前字符与前缀字符不同
				nextval[i] = j;			//则当前的j为nextval在i位置的值
			}
			else {
				nextval[i] = nextval[j];//若与前缀字符相同，则将前缀字符的nextval值复制给nextval在i位置的值
			}
		}
		else {	
			j = nextval[j];	//若字符不相同则j值回溯
		}
	}
}

/******************** KMP算法 **********************/
/*************************************************** 
该算法的关键在于：利用已经部分匹配这个有效信息，
保持i指针不回溯，通过修改j指针，让模式串尽量地移动到有效的位置。
*****************************************************/
//返回子串substr 在主串mainstr中第pos个字符之后的位置。若不存在则返回 0。
int Index_KMP(char *mainstr, char *substr, int pos)
{
	int i = pos;	//i 主串的当前位置下标值
	int j = 1;		//j 子串的当前位置下标值
	int next[255];	/* 定义一个next数组 */
	/****** next 和 nextval 两种方法 *******/
	get_next(substr, next);
	//get_nextval(substr, next);

	while (i <= mainstr[0] && j <= substr[0]) {	//i小于等于主串长度，j小于等于模式串长度时，
												//循环继续
		//只有当子串是首位 或 这子串与主串的单个字符匹配成功时，i值才会后移。
		if (j == 0 || mainstr[i] == substr[j]) {
			i++;
			j++;
		}
		else {//指针后退重新开始匹配
			j = next[j];	//j退回合适的位置,i值不变
		}
	}
	if (j > substr[0]) {
		return i - substr[0];
	}
	return 0;
}

int main() {

	//next nextval 检测代码
	//int next[255] = {0};
	//int nextval[255] = {0};

	//char str[] = "0ababaaaba";
	//str[0] = strlen(str) - 1;
	//get_next(str, next);
	//get_nextval(str, nextval);


	//KMP 算法检测代码
	char str1[] = "0aaaaaaaaaaaaaab";
	char str2[] = "0aaab";
	str1[0] = strlen(str1) - 1;
	str2[0] = strlen(str2) - 1;

	int num = Index_KMP(str1, str2, 1);
	printf(" num = %d\n", num);

	return 0;
}
