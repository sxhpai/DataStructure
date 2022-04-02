/********************** 两种朴素的写法 ****************************/
/******************** 朴素的模式匹配算法 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********* 写法一 *********/
//字符数组的第0位用于存储该串的长度
int IndexDa(char *mainstr, char * substr, int pos) {
	int i = pos;	//i 用于主串mainstr的当前下标值，
					//pos表示从主串的pos位置开始匹配
	int j = 1;		//j 用于子串substr的当前的下标值。
	while (i <= mainstr[0] && j <= substr[0]) {//若i小于等于主串的长度 且 j小于等于子串的长度 则继续
		if (mainstr[i] == substr[j]) {	//两字母相等则继续
			i++;
			j++;
		}
		else {
			//i 退回到上次匹配首位的下一位
			i = i - j + 2;// 便于理解的写法：i = 1 + (i-j) + 1;
			//j 退回到子串的首位
			j = 1;
		}
	}

	if (j > substr[0]) {
		return i - substr[0];	//返回子串在主串中的下标值，和第几个元素一样的
	}
	return 0;
}

/********* 写法二 *********/
//字符数组的长度需要单独传入函数
int IndexYan(char *mainstr, int mainlen, char *substr, int sublen) {
	int i = 0;
	int j = 0;
	while (i < mainlen && j < sublen) {
		if (mainstr[i] == substr[j]) {
			i++;
			j++;
		}
		else
		{
			//i 退回到上次匹配首位的下一位
			i = i - j + 1;
			//j 退回到子串的首位
			j = 0;
		}
	}

	if (j == sublen) {
		return i - sublen;	//返回子串在主串中的下标值
	}
	return 0;
}


int main() {

	//大话数据结构的写法
	char str1[] = "0sunxinghuixinghui";
	char str2[] = "0xing";
	str1[0] = strlen(str1) - 1;
	str2[0] = strlen(str2) - 1;
	int num1 = IndexDa(str1, str2,11);
	printf(" %d\n", num1);

	//严长生的写法
	char str3[] = "sunsunxinghui";
	char str4[] = "xing";
	int num2 = IndexYan(str3, strlen(str3), str4, strlen(str4));
	printf(" %d\n", num2);

	return 0;
}
