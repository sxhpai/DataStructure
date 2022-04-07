//二叉树的创建与遍历
//线索二叉树的创建与遍历

#include <stdio.h>

#define OK 0;
#define ERROR -1;

typedef char TElemType;	//数据域数据类型
typedef int Status;

//二叉树结点结构
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

//枚举
typedef enum{Link, Thread}Tag;

//线索二叉树的结点结构
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode* lchild, * rchild;
	Tag ltag, rtag;
}BiThrNode,* BiThrTree;

//全局变量，用于存储前驱结点
BiThrTree pre = NULL;

//链栈结构
typedef struct StackNode
{
	TElemType data;
	struct StackNode* next;
}StackNode, *LinkStackPtr;
typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
}LinkStack;

//压栈
Status Push(LinkStack* S, TElemType e) {
	//取出头指针变量内的地址
	LinkStackPtr temp = S->top;
	//申请内存初始化
	S->top = (LinkStackPtr)malloc(sizeof(StackNode));
	S->top->data = e;
	S->top->next = temp;
	S->count++;

	return OK;
}

//弹栈
Status Pop(LinkStack* S, TElemType* e) {
	if (S->count == 0) {
		printf("空栈");
		return ERROR;
	}
	//取出头指针指向的地址
	LinkStackPtr temp = S->top;
	//弹出
	*e = S->top->data;
	S->top = S->top->next;
	free(temp);
	S->count--;

	return OK;
}

//二叉树创建
//扩展前序输入
void CreateTree(BiTree* T)
{
	TElemType ch;
	scanf_s("%c", &ch);
	if (ch == '#')
		(*T) = NULL;
	else {
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		if (!(*T))
			return;
		(*T)->data = ch;
		CreateTree(&(*T)->lchild);
		CreateTree(&(*T)->rchild);
	}
}

//前序遍历
void PreOrderTraverse(BiTree T)
{
	if (!T)
		return;
	printf(" %c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//中序遍历
void InOrderTraverse(BiTree T)
{
	if (!T)
		return;
	InOrderTraverse(T->lchild);
	printf(" %c", T->data);
	InOrderTraverse(T->rchild);
}

//后序遍历
void PostOrderTraverse(BiTree T)
{
	if (!T)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf(" %c", T->data);
}

//创建一个普通的二叉树
//扩展前序输入
void CreateThrTree(BiThrTree* T)
{
	TElemType ch;
	scanf_s("%c", &ch);
	if (ch == '#')
		(*T) = NULL;
	else {
		(*T) = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!(*T))
			return;
		(*T)->data = ch;
		(*T)->ltag = Link;	//默认有左孩子，具体有没有线索化的过程中判断
		(*T)->rtag = Link;	//默认有右孩子，线索化的过程中修正没有孩子的指针域
		CreateThrTree(&(*T)->lchild);
		CreateThrTree(&(*T)->rchild);
	}
}

//中序遍历普通二叉树，进行中序线索化
void InThreading(BiThrTree T)
{
	if (T){	//如果 T 结点存在
		InThreading(T->lchild);	//线索化左孩子
		if (!T->lchild) {	//如果没有左孩子
			T->ltag = Thread;
			T->lchild = pre;	//左指针指向前驱
		}
		if (pre && !pre->rchild) {	//如果没有右孩子 且 pre非空
			pre->rtag = Thread;
			pre->rchild = T;	//前驱右指针指向当前结点
		}
		pre = T;
		InThreading(T->rchild);	//线索化右孩子
	}
}

//先序遍历普通二叉树，进行先序线索化
void PreThreading(BiThrTree T)
{
	
	if (T) {	//如果 T 结点存在

		if (!T->lchild) {	//如果没有左孩子
			T->ltag = Thread;
			T->lchild = pre;	//左指针指向前驱
		}
		if (pre && !pre->rchild) {	//如果没有右孩子 且 pre非空
			pre->rtag = Thread;
			pre->rchild = T;	//前驱右指针指向当前结点
		}
		pre = T;
		if (T->ltag != Thread) {
			PreThreading(T->lchild);	//线索化左孩子
		}
		if (T->rtag != Thread) {
			PreThreading(T->rchild);	//线索化右孩子
		}
	}
}

//后序遍历普通二叉树，进行后序线索化
void PostThreading(BiThrTree T)
{
	if (T) {	//如果 T 结点存在
		PostThreading(T->lchild);	//线索化左孩子
		PostThreading(T->rchild);	//线索化右孩子
		if (!T->lchild) {	//如果没有左孩子
			T->ltag = Thread;
			T->lchild = pre;	//左指针指向前驱
		}
		if (pre && !pre->rchild) {	//如果没有右孩子 且 pre非空
			pre->rtag = Thread;
			pre->rchild = T;	//前驱右指针指向当前结点
		}
		pre = T;
	}
}


//中序，线索二叉树创建
void InOrderCreateBiTree_Thr(BiThrTree T)
{
	while (T)	// T 非空
	{
		//找中序遍历的第一个结点，最左边的孩子
		while (T->ltag == Link) {
			T = T->lchild;
		}
		printf(" %c", T->data);
		//通过右指针域的指向直接找后继结点
		while (T->rtag == Thread && T->rchild != NULL) {
			T = T->rchild;
			printf(" %c", T->data);
		}
		//通过中序的规律，找后继结点
		T = T->rchild;
	}
}

//先序，线索二叉树创建
void PreOrderCreateBiTree_Thr(BiThrTree T)
{
	while (T)	// T 非空
	{
		printf(" %c", T->data);
		if (T->ltag == Link) {
			T = T->lchild;
		}
		else {
			T = T->rchild;
		}
	}
}


//后序，线索二叉树创建
void PostOrderCreateBiTree_Thr(BiThrTree T)
{
	//初始化一个空栈
	LinkStack S;
	S.top = NULL;
	S.count = 0;
	TElemType c;
	
	//线索二叉树创建
	while (T) {
		//printf(" %c", T->data);
		Push(&S, T->data);//压栈
		if (T->rtag == Link) {
			T = T->rchild;
		}
		else {
			T = T->lchild;
		}
	}

	//弹栈，目的为了把顺序倒一下
	printf("\n");
	while (S.count) {
		Pop(&S, &c);
		printf(" %c", c);
	}
}



int main()
{
	/* 二叉树 */
	//BiTree T;
	/* 线索二叉树 */
	BiThrTree Thr;

	/* 二叉树的创建与遍历 */
	//CreateTree(&T);

	//PreOrderTraverse(T);
	//printf("\n");
	//InOrderTraverse(T);
	//printf("\n");
	//PostOrderTraverse(T);
	//printf("\n");
	
	//getchar();	//清空输入缓冲区

	/* 线索二叉树的创建与遍历 */
	CreateThrTree(&Thr);

	//PreThreading(Thr);
	//PreOrderCreateBiTree_Thr(Thr);

	//InThreading(Thr);
	//InOrderCreateBiTree_Thr(Thr);

	PostThreading(Thr);
	PostOrderCreateBiTree_Thr(Thr);


	return 0;
}
