#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//线性表单链表存储结构
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;

typedef struct Node* LinkList;//定义LinkList

void CreatListHead(LinkList *L, int n)
{
	LinkList p;
	int i;
	//srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = i + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

void DisplayList(LinkList *L)
{
	LinkList p = (*L)->next;

	while(p != NULL)
	{
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	LinkList L = NULL;

	CreatListHead(&L, 5);

	DisplayList(&L);

	return 0;
}