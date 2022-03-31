
/******************** 串的块链存储方式 C语言程序 ********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LinkNum 3	//全局设置链表中节点存储数据的个数
#define ERROR -1
#define OK 1

typedef int Status;


typedef struct Link {
	char a[LinkNum];	//数据域可存放LinkNum个数据
	struct Link *next;	//指针域
}Link, *LinkString;

Status InitLink(LinkString *LinkStr, char *str);
void Display(LinkString LinkStr);

int main() {
	LinkString L;

	InitLink(&L, "sunxinghui");

	Display(L);

	return 0;
}

//*LinkStr为头指针，str为存储的字符串
Status InitLink(LinkString *LinkStr, char *str) {
	int length = strlen(str);
	//根据字符串的长度，计算初链表中使用节点的个数
	int num = length / LinkNum;
	if (length % LinkNum != 0) {
		num++;
	}

	//创建并初始化首元节点
	LinkString temp = (LinkString)malloc(sizeof(Link));
	temp->next = NULL;
	(*LinkStr) = temp;	//头指针指向首元节点

	//初始化链表
	for (int i = 0; i < num; i++) {
		int j = 0;
		for (; j < LinkNum; j++) {
			if (i * LinkNum + j < length) {
				temp->a[j] = str[i * LinkNum + j];
			}
			else {
				temp->a[j] = '#';
			}

		}
		if (i * LinkNum + j < length) {
			LinkString newlink = (LinkString)malloc(sizeof(Link));
			newlink->next = NULL;
			temp->next = newlink;
			temp = newlink;
		}
	}
	return OK;
}

//输出块链表
void Display(LinkString LinkStr) {
	LinkString temp = LinkStr;
	while (temp) {
		for (int i = 0; i < LinkNum; i++) {
			printf("%c", temp->a[i]);
		}
		temp = temp->next;
	}
}
