
/***************** KMP模式匹配算法 ******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//求模式串 str 的 next 数组
//str 为字符串指针，strLen为字符串长度，next数组。
void get_next(char *str, int *next)
{
	next[1] = 0;
	int i = 1; 
	int j = 0;
	while (i < str[0]) {	// 此处str[0]表示串str的有效长度（即：不包含str[0]的长度）
		if (j == 0 || str[i] == str[j]) {	//str[i]表示后缀的单个字符
			++i;							//str[j]表示前缀的单个字符
			++j;
			next[i] = j;
		}
		else {
			j = next[j];	//若字符不相同，则 j 回溯
		}
	}
}

//求模式串 str 的 next 数组的修正值并存入 nextval 数组
//str 为字符串指针，strLen为字符串长度，nextval数组。
void get_nextval(char *str, int *nextval)
{
	nextval[1] = 0;
	int i = 1;
	int j = 0;
	while (i < str[0]) {	// 此处str[0]表示串str的有效长度（即：不包含str[0]的长度）
		if (j == 0 || str[i] == str[j]) {		//str[i]表示后缀的单个字符
			i++;								//str[j]表示前缀的单个字符
			j++;
			if (str[i] != str[j]) {
				nextval[i] = j;
			}
			else {
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}
}

//返回子串subStr在主串S中第pos个字符之后的首个位置下标。若不存在则返回 0。
//subStr非空，且1<=pos<=Strlength(mainStr)。
int Index_KMP(char *mainStr, char *subStr, int pos) {
	int i = pos;	//i用于主串当前位置的下标值
	int j = 1;		//j用于子串当前位置的下标值
	int next[255];	//定义一个next数组
	get_next(subStr, next);	//获得next数组
	while (i <= mainStr[0] && j <= subStr[0]) {//mainStr[0]主串有效长度，subStr[0]子串的有效长度。
		if (j == 0 || mainStr[i] == subStr[j]) {
			i++;
			j++;
		}
		else {//指针后退重新开始匹配
			//j = 1;
			j = next[j];	//j退回合适的位置，i值不变
		}
	}

	if (j > subStr[0]) {	//j 等于子串的长度，说明匹配成功
		return i - subStr[0];	//数组的下标
	}
	return 0;
}

//主函数
int main()
{
	//char str[] = "0ababaaaba";//字符串第0位无效，从第1位开始，第0位应当用以存储字符串的长度。
	//str[0] = strlen(str) - 1;//求字符串的有效长度，并存入str[0]；char 类型的数据存储 -128 到 127 整数没问题。
	////声明两个足够长的数组
	//int next[15] = {0};
	//int nextval[15] = { 0 };
	
	//获得模式串 str 的 next 数组和 nextval 数组
	//get_next(str, next);
	//get_nextval(str, nextval);

	char str1[] = "0sunssxingasdfsxinghui";
	char str2[] = "0xing";
	str1[0] = strlen(str1) - 1;
	str2[0] = strlen(str2) - 1;

	int g = Index_KMP(str1, str2,9);
	printf("** %d **\n", g);

	return 0;
}
