
/***************** 字符过滤系统 ****************/
/*
例如在字符串文本 “abcabc” 中检测是否含有字符 ‘a’ 时，
字符过滤系统应反馈给用户该字符存储于文本中的位置，即 1 和4，
同时询问用户是否将所有的字符 ‘a’ 替换成其它指定字符，
假设用户指定字符 ‘a’ 全部转换成字符 ‘d’，
系统应将替换后的字符串 “dbcdbc” 反馈给用户。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//get_nextval 函数
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

//KMP算法
int Index_KMP(char *mainstr, char *substr, int pos)
{
	int i = pos;	//i 主串的当前位置下标值
	int j = 1;		//j 子串的当前位置下标值
	int next[255];	

	get_nextval(substr, next);

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

//替换
//将str1中的子串str2替换为str3,串str2与str长度一样
void replaceString(char *str1, char *str2, char *str3) {
	int pos = 1;
	int res = -1;
	int i, j = 0;
	while (res != 0) {
		res = Index_KMP(str1, str2, pos);
		if (res != 0) {
			for (i = res, j = 1; j <= str3[0]; i++ ,j++) {
				str1[i] = str3[j];
			}
		}
		//printf(" %d", res);
		pos = res + 1;
	}
}

//查询
void Index(char *str1, char *str2) {
	int pos = 1;
	int res = -1;
	int num = 0;
	while (res != 0) {
		res = Index_KMP(str1, str2, pos);
		if (res != 0) {
			//printf(" %d", res);
			num++;
		}
		pos = res + 1;
	}
	printf("系统检测到该字符在原字符串中出现%d次,起始位置依次是：\n", num);
	pos = 1;
	res = -1;
	while (res != 0) {
		res = Index_KMP(str1, str2, pos);
		if (res != 0) {
			printf(" %d", res);
		}
		pos = res + 1;
	}
	printf("\n");
}



//主函数
int main() {

	char str1[255] = "0aaabb";
	char str2[255] = "0a";
	char str3[255] = "0d";

	char judge;
	//str1[0] = strlen(str1) - 1;
	//str2[0] = strlen(str2) - 1;
	printf("请输入原字符串：\n");
	scanf_s("%s",&str1[1], 254);
	getchar();//清空缓冲区
	str1[0] = strlen(str1) - 1;
	//printf("%s\n", &str1[1]);
	//printf("%d\n", str1[0]);

	printf("请输入要查找的字符串：\n");
	scanf_s("%s", &str2[1], 254);
	getchar();//清空缓冲区
	str2[0] = strlen(str2) - 1;
	//printf("%s\n", &str2[1]);
	//printf("%d\n", str2[0]);
	Index(str1, str2);

	printf("是否用新字符替换：(Y/N)\n");
	scanf_s("%c", &judge);
	getchar();//清空缓冲区
	if (judge == 'Y') {
		printf("请输入要替换的字符：\n");
		scanf_s("%s", &str3[1], 254);
		getchar();//清空缓冲区
		str3[0] = strlen(str3) - 1;
		//printf("%s\n", &str2[1]);
		//printf("%d\n", str2[0]);

		replaceString(str1, str2, str3);
		printf("替换后的新字符串是：\n");
		printf("%s\n", &str1[1]);
	}
	else{
		return 0;
	}
	
	return 0;
}
