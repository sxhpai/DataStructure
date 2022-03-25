
/****************************************************
------------------线性表链式存储结构----------------
----------------------基本操作----------------------
*****************************************************/

//单链表 

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1;

typedef int Status;
typedef int ElemType;

//单链表的存储结构
typedef struct Node {
	ElemType data;
	struct Node *next;
}Node,* LinkList;

/*-------------------为什么形参用 LinkList *L ？------------------*/
/*------------------------------------------------------------------
因为在单链表初始化之前
我们在主函数中定义一个头指针变量为空，我们只有把这个头指针变量的地址传入，
我们才能访问到这个头指针，进而改变头指针的指向，完成我们的目标；
否则，我们只传入头指针变量的值，是没有任何意义的。

但是当单链表初始化结束后，只需传入头指针变量的值（即：头结点的地址），
我们即可访问到整个链表的信息。
------------------------------------------------------------------*/

//创建链表（头插法）
//操作结果：生成一个长度为n的链表L
Status InitLinklistHead(LinkList *L, int n)
{
	//生成头结点
	(*L) = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;

	//生成新节点
	for (int i = 1; i <= n; i++){
		LinkList newNode = (LinkList)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = (*L)->next;
		(*L)->next = newNode;
	}
	return OK;
}

//创建链表（尾插法）
//操作结果：生成一个长度为n的链表L
Status InitLinklistTail(LinkList *L, int n)
{
	//生成头结点,并让头指针指向头结点，
	(*L) = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	//用一个临时变量取出头指针变量的值（即：头结点地址）
	LinkList temp = (*L);

	//生成新结点
	for (int i = 1; i <= n; i++){
		LinkList newNode = (LinkList)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = NULL;
		temp->next = newNode;
		temp = temp->next;
	}
	return OK;
}

//插入操作
//操作结果：在链表L的第n个结点之后插入一个数据域为elem的结点
Status ListInsert(LinkList *L,int n,ElemType elem)
{
	//临时指针变量temp取得头结点的地址（该地址存放在头指针中）
	LinkList temp = (*L);
	//让temp指向要插入位置的前一个结点
	for (int i = 0; i < n; i++){
		temp = temp->next;
		if (temp == NULL)
		{
			return ERROR;
		}
	}
	//新建一个结点（用newNode指针指向这个结点）
	LinkList newNode = (LinkList)malloc(sizeof(Node));
	newNode->data = elem;
	//插入操作
	newNode->next = temp->next;
	temp->next = newNode;
	return OK;
}

//删除操作
//操作结果：删除链表L中第n个结点
Status ListDelete(LinkList *L, int n)
{
	//临时结点指针取得头结点地址
	LinkList temp = (*L);
	//让temp指向要删除结点的上一个结点
	for (int i = 1; i < n; i++) {
		temp = temp->next;
		if (temp->next == NULL)
		{
			return ERROR;
		}
	}
	//删除操作
	LinkList del = temp->next;
	temp->next = temp->next->next;
	free(del);
	return OK;
}

//读取操作
//操作结果：用e返回L中第n个数据元素的值
Status GetElem(LinkList L, int n, ElemType *e)
{
	//用临时指针取得第一个结点的地址
	LinkList temp = L->next;
	//临时指针始终指向要获取数据元素的那个结点
	for (int i = 1; i < n; i++)
	{
		temp = temp->next;
		if (temp == NULL)
		{
			return ERROR;
		}
	}
	//取得第n个数据元素的值
	*e = temp->data;
	return OK;
}

//整个链表删除
//操作结果：将L重置为空表
Status ClearList(LinkList *L)
{
	//让临时指针指向头结点
	LinkList temp = (*L);

	LinkList del = temp;
	
	while (temp != NULL)
	{
		del = temp;
		temp = temp->next;
		free(del);
	}
	(*L) = NULL;//头指针指向空
	return OK;
}

//打印链表
Status DisplayList(LinkList *L)
{
	//用临时变量取得头结点地址
	LinkList temp = (*L)->next;
	while (temp != NULL)
	{
		printf(" %d", temp->data);
		temp = temp->next;
	}
	printf("\n");

	return OK;
}

int main() {

	//函数状态标志
	int s = 0;

	//函数通过指针变量返回的值
	ElemType e = -1;

	LinkList LH = NULL;	//头指针
	LinkList LT = NULL;	//头指针

	//头差法初始化单链表
	InitLinklistHead(&LH, 5);
	DisplayList(&LH);

	//尾插法初始化单链表
	InitLinklistTail(&LT, 5);
	DisplayList(&LT);

	//第5个结点后添加新节点且其数据域为9
	s = ListInsert(&LT, 5, 9);
	printf(" Sta = %d\n", s);
	DisplayList(&LT);

	//删除第6个结点
	s = ListDelete(&LT, 6);
	printf(" Sta = %d\n", s);
	DisplayList(&LT);

	//读取第3个数据元素
	s = GetElem(LT, 3, &e);
	printf(" Sta = %d\n", s);
	printf(" elem = %d\n", e);

	//单链表整表删除
	s = ClearList(&LT);
	printf(" Sta = %d\n", s);

	return 0;
}
