
/*************** 双向链表的创建与基本操作 **********************/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1

typedef int Status;

//双向链表的结构s
typedef struct Node {
	struct Node * prior;
	int data;		//数据类型都默认定义为 int
	struct Node * next;
}Node, *DLinkList;

//初始化双向链表
Status initDlinklist(DLinkList *L) {

	//1.首元结点
	(*L) = (DLinkList)malloc(sizeof(Node));	//头指针指向首元结点（而不是临时指针）
	(*L)->prior = NULL;
	(*L)->next = NULL;
	(*L)->data = 1;

	//临时结点指针变量取得首元结点地址
	DLinkList temp = (*L);

	//2.数据结点
	for (int i = 2; i < 7; i++) {
		DLinkList newNode = (DLinkList)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = NULL;
		//尾插法
		newNode->prior = temp;
		temp->next = newNode;

		//后移
		temp = temp->next;
	}
	return OK;
}

//插入操作
//操作结果：在链表L中的第n个位置之前插入新数据元素elem
Status insertDlinklist(DLinkList *L, int n, int elem) {
	if (n == 1) {//插入到链表表头，要特殊考虑
		//1.生成新节点
		DLinkList newNode = (DLinkList)malloc(sizeof(Node));
		newNode->data = elem;

		//2.插入(此时*L为指向首元结点的指针,其数值即为首元结点的地址)
		newNode->next = (*L);
		newNode->prior = NULL;
		(*L)->prior = newNode;
		(*L) = newNode;
		return OK;
	}
	else {
		DLinkList temp = (*L);	//取得首元结点的地址（头指针中存放的就是首元结点的地址）

		//1.找到要插入位置的前一个结点
		for (int i = 1; i < n-1; i++) {
			temp = temp->next;
		}

		//2.生成新节点
		DLinkList newNode = (DLinkList)malloc(sizeof(Node));
		newNode->data = elem;

		//3.插入(最后一个结点单独操作)
		if (temp->next != NULL)
		{
			newNode->next = temp->next;
			newNode->prior = temp;
			temp->next->prior = newNode;
			temp->next = newNode;
		}
		else {
			newNode->next = temp->next;
			newNode->prior = temp;
			temp->next = newNode;
		}
		return OK;
	}
}

//删除操作
//操作结果：删除链表L第n个元素
Status deleteDlinklist(DLinkList *L, int n) {
	if (n == 1)
	{
		DLinkList del = (*L);
		(*L)->next->prior = NULL;
		(*L) = (*L)->next;
		free(del);
	}
	else {
		//取得首元结点的地址
		DLinkList temp = (*L);
		//找到要删除结点的前一个位置
		for (int i = 1; i < n - 1; i++) {
			temp = temp->next;
		}
		if (temp->next->next != NULL) {
			//删除
			DLinkList del = temp->next;
			temp->next->next->prior = temp;
			temp->next = temp->next->next;
			free(del);
		}
		else {
			DLinkList del = temp->next;
			temp->next = NULL;
		}
	}
}

//打印双向链表
Status displayDlinklist(DLinkList *L) {
	//临时变量取得头结点地址
	DLinkList temp = (*L);

	while (temp) {		
		printf(" %d", temp->data);
		temp = temp->next;
	}

	printf("\n");
	return OK;
}

//主函数
//测试时，应输入合理的测试值，本例子没有判断输入是否合理
int main() {

	DLinkList D = NULL;
	
	//初始化结点
	initDlinklist(&D);
	displayDlinklist(&D);

	//插入操作
	insertDlinklist(&D,7,0);
	displayDlinklist(&D);

	//删除操作
	deleteDlinklist(&D, 7);
	displayDlinklist(&D);

	return 0;
}
