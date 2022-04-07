//�������Ĵ��������
//�����������Ĵ��������

#include <stdio.h>

#define OK 0;
#define ERROR -1;

typedef char TElemType;	//��������������
typedef int Status;

//���������ṹ
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

//ö��
typedef enum{Link, Thread}Tag;

//�����������Ľ��ṹ
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode* lchild, * rchild;
	Tag ltag, rtag;
}BiThrNode,* BiThrTree;

//ȫ�ֱ��������ڴ洢ǰ�����
BiThrTree pre = NULL;

//��ջ�ṹ
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

//ѹջ
Status Push(LinkStack* S, TElemType e) {
	//ȡ��ͷָ������ڵĵ�ַ
	LinkStackPtr temp = S->top;
	//�����ڴ��ʼ��
	S->top = (LinkStackPtr)malloc(sizeof(StackNode));
	S->top->data = e;
	S->top->next = temp;
	S->count++;

	return OK;
}

//��ջ
Status Pop(LinkStack* S, TElemType* e) {
	if (S->count == 0) {
		printf("��ջ");
		return ERROR;
	}
	//ȡ��ͷָ��ָ��ĵ�ַ
	LinkStackPtr temp = S->top;
	//����
	*e = S->top->data;
	S->top = S->top->next;
	free(temp);
	S->count--;

	return OK;
}

//����������
//��չǰ������
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

//ǰ�����
void PreOrderTraverse(BiTree T)
{
	if (!T)
		return;
	printf(" %c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//�������
void InOrderTraverse(BiTree T)
{
	if (!T)
		return;
	InOrderTraverse(T->lchild);
	printf(" %c", T->data);
	InOrderTraverse(T->rchild);
}

//�������
void PostOrderTraverse(BiTree T)
{
	if (!T)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf(" %c", T->data);
}

//����һ����ͨ�Ķ�����
//��չǰ������
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
		(*T)->ltag = Link;	//Ĭ�������ӣ�������û���������Ĺ������ж�
		(*T)->rtag = Link;	//Ĭ�����Һ��ӣ��������Ĺ���������û�к��ӵ�ָ����
		CreateThrTree(&(*T)->lchild);
		CreateThrTree(&(*T)->rchild);
	}
}

//���������ͨ����������������������
void InThreading(BiThrTree T)
{
	if (T){	//��� T ������
		InThreading(T->lchild);	//����������
		if (!T->lchild) {	//���û������
			T->ltag = Thread;
			T->lchild = pre;	//��ָ��ָ��ǰ��
		}
		if (pre && !pre->rchild) {	//���û���Һ��� �� pre�ǿ�
			pre->rtag = Thread;
			pre->rchild = T;	//ǰ����ָ��ָ��ǰ���
		}
		pre = T;
		InThreading(T->rchild);	//�������Һ���
	}
}

//���������ͨ����������������������
void PreThreading(BiThrTree T)
{
	
	if (T) {	//��� T ������

		if (!T->lchild) {	//���û������
			T->ltag = Thread;
			T->lchild = pre;	//��ָ��ָ��ǰ��
		}
		if (pre && !pre->rchild) {	//���û���Һ��� �� pre�ǿ�
			pre->rtag = Thread;
			pre->rchild = T;	//ǰ����ָ��ָ��ǰ���
		}
		pre = T;
		if (T->ltag != Thread) {
			PreThreading(T->lchild);	//����������
		}
		if (T->rtag != Thread) {
			PreThreading(T->rchild);	//�������Һ���
		}
	}
}

//���������ͨ�����������к���������
void PostThreading(BiThrTree T)
{
	if (T) {	//��� T ������
		PostThreading(T->lchild);	//����������
		PostThreading(T->rchild);	//�������Һ���
		if (!T->lchild) {	//���û������
			T->ltag = Thread;
			T->lchild = pre;	//��ָ��ָ��ǰ��
		}
		if (pre && !pre->rchild) {	//���û���Һ��� �� pre�ǿ�
			pre->rtag = Thread;
			pre->rchild = T;	//ǰ����ָ��ָ��ǰ���
		}
		pre = T;
	}
}


//������������������
void InOrderCreateBiTree_Thr(BiThrTree T)
{
	while (T)	// T �ǿ�
	{
		//����������ĵ�һ����㣬����ߵĺ���
		while (T->ltag == Link) {
			T = T->lchild;
		}
		printf(" %c", T->data);
		//ͨ����ָ�����ָ��ֱ���Һ�̽��
		while (T->rtag == Thread && T->rchild != NULL) {
			T = T->rchild;
			printf(" %c", T->data);
		}
		//ͨ������Ĺ��ɣ��Һ�̽��
		T = T->rchild;
	}
}

//������������������
void PreOrderCreateBiTree_Thr(BiThrTree T)
{
	while (T)	// T �ǿ�
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


//������������������
void PostOrderCreateBiTree_Thr(BiThrTree T)
{
	//��ʼ��һ����ջ
	LinkStack S;
	S.top = NULL;
	S.count = 0;
	TElemType c;
	
	//��������������
	while (T) {
		//printf(" %c", T->data);
		Push(&S, T->data);//ѹջ
		if (T->rtag == Link) {
			T = T->rchild;
		}
		else {
			T = T->lchild;
		}
	}

	//��ջ��Ŀ��Ϊ�˰�˳��һ��
	printf("\n");
	while (S.count) {
		Pop(&S, &c);
		printf(" %c", c);
	}
}



int main()
{
	/* ������ */
	//BiTree T;
	/* ���������� */
	BiThrTree Thr;

	/* �������Ĵ�������� */
	//CreateTree(&T);

	//PreOrderTraverse(T);
	//printf("\n");
	//InOrderTraverse(T);
	//printf("\n");
	//PostOrderTraverse(T);
	//printf("\n");
	
	//getchar();	//������뻺����

	/* �����������Ĵ�������� */
	CreateThrTree(&Thr);

	//PreThreading(Thr);
	//PreOrderCreateBiTree_Thr(Thr);

	//InThreading(Thr);
	//InOrderCreateBiTree_Thr(Thr);

	PostThreading(Thr);
	PostOrderCreateBiTree_Thr(Thr);


	return 0;
}
