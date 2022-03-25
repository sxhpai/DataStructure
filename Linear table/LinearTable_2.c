
/****************************************************
------------------���Ա���ʽ�洢�ṹ----------------
----------------------��������----------------------
*****************************************************/

//������ 

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1;

typedef int Status;
typedef int ElemType;

//������Ĵ洢�ṹ
typedef struct Node {
	ElemType data;
	struct Node *next;
}Node,* LinkList;

/*-------------------Ϊʲô�β��� LinkList *L ��------------------*/
/*------------------------------------------------------------------
��Ϊ�ڵ������ʼ��֮ǰ
�������������ж���һ��ͷָ�����Ϊ�գ�����ֻ�а����ͷָ������ĵ�ַ���룬
���ǲ��ܷ��ʵ����ͷָ�룬�����ı�ͷָ���ָ��������ǵ�Ŀ�ꣻ
��������ֻ����ͷָ�������ֵ����û���κ�����ġ�

���ǵ��������ʼ��������ֻ�贫��ͷָ�������ֵ������ͷ���ĵ�ַ����
���Ǽ��ɷ��ʵ������������Ϣ��
------------------------------------------------------------------*/

//��������ͷ�巨��
//�������������һ������Ϊn������L
Status InitLinklistHead(LinkList *L, int n)
{
	//����ͷ���
	(*L) = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;

	//�����½ڵ�
	for (int i = 1; i <= n; i++){
		LinkList newNode = (LinkList)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = (*L)->next;
		(*L)->next = newNode;
	}
	return OK;
}

//��������β�巨��
//�������������һ������Ϊn������L
Status InitLinklistTail(LinkList *L, int n)
{
	//����ͷ���,����ͷָ��ָ��ͷ��㣬
	(*L) = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	//��һ����ʱ����ȡ��ͷָ�������ֵ������ͷ����ַ��
	LinkList temp = (*L);

	//�����½��
	for (int i = 1; i <= n; i++){
		LinkList newNode = (LinkList)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = NULL;
		temp->next = newNode;
		temp = temp->next;
	}
	return OK;
}

//�������
//���������������L�ĵ�n�����֮�����һ��������Ϊelem�Ľ��
Status ListInsert(LinkList *L,int n,ElemType elem)
{
	//��ʱָ�����tempȡ��ͷ���ĵ�ַ���õ�ַ�����ͷָ���У�
	LinkList temp = (*L);
	//��tempָ��Ҫ����λ�õ�ǰһ�����
	for (int i = 0; i < n; i++){
		temp = temp->next;
		if (temp == NULL)
		{
			return ERROR;
		}
	}
	//�½�һ����㣨��newNodeָ��ָ�������㣩
	LinkList newNode = (LinkList)malloc(sizeof(Node));
	newNode->data = elem;
	//�������
	newNode->next = temp->next;
	temp->next = newNode;
	return OK;
}

//ɾ������
//���������ɾ������L�е�n�����
Status ListDelete(LinkList *L, int n)
{
	//��ʱ���ָ��ȡ��ͷ����ַ
	LinkList temp = (*L);
	//��tempָ��Ҫɾ��������һ�����
	for (int i = 1; i < n; i++) {
		temp = temp->next;
		if (temp->next == NULL)
		{
			return ERROR;
		}
	}
	//ɾ������
	LinkList del = temp->next;
	temp->next = temp->next->next;
	free(del);
	return OK;
}

//��ȡ����
//�����������e����L�е�n������Ԫ�ص�ֵ
Status GetElem(LinkList L, int n, ElemType *e)
{
	//����ʱָ��ȡ�õ�һ�����ĵ�ַ
	LinkList temp = L->next;
	//��ʱָ��ʼ��ָ��Ҫ��ȡ����Ԫ�ص��Ǹ����
	for (int i = 1; i < n; i++)
	{
		temp = temp->next;
		if (temp == NULL)
		{
			return ERROR;
		}
	}
	//ȡ�õ�n������Ԫ�ص�ֵ
	*e = temp->data;
	return OK;
}

//��������ɾ��
//�����������L����Ϊ�ձ�
Status ClearList(LinkList *L)
{
	//����ʱָ��ָ��ͷ���
	LinkList temp = (*L);

	LinkList del = temp;
	
	while (temp != NULL)
	{
		del = temp;
		temp = temp->next;
		free(del);
	}
	(*L) = NULL;//ͷָ��ָ���
	return OK;
}

//��ӡ����
Status DisplayList(LinkList *L)
{
	//����ʱ����ȡ��ͷ����ַ
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

	//����״̬��־
	int s = 0;

	//����ͨ��ָ��������ص�ֵ
	ElemType e = -1;

	LinkList LH = NULL;	//ͷָ��
	LinkList LT = NULL;	//ͷָ��

	//ͷ���ʼ��������
	InitLinklistHead(&LH, 5);
	DisplayList(&LH);

	//β�巨��ʼ��������
	InitLinklistTail(&LT, 5);
	DisplayList(&LT);

	//��5����������½ڵ�����������Ϊ9
	s = ListInsert(&LT, 5, 9);
	printf(" Sta = %d\n", s);
	DisplayList(&LT);

	//ɾ����6�����
	s = ListDelete(&LT, 6);
	printf(" Sta = %d\n", s);
	DisplayList(&LT);

	//��ȡ��3������Ԫ��
	s = GetElem(LT, 3, &e);
	printf(" Sta = %d\n", s);
	printf(" elem = %d\n", e);

	//����������ɾ��
	s = ClearList(&LT);
	printf(" Sta = %d\n", s);

	return 0;
}
