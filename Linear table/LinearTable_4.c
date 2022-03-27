
/*************** ˫������Ĵ������������ **********************/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1

typedef int Status;

//˫������Ľṹs
typedef struct Node {
	struct Node * prior;
	int data;		//�������Ͷ�Ĭ�϶���Ϊ int
	struct Node * next;
}Node, *DLinkList;

//��ʼ��˫������
Status initDlinklist(DLinkList *L) {

	//1.��Ԫ���
	(*L) = (DLinkList)malloc(sizeof(Node));	//ͷָ��ָ����Ԫ��㣨��������ʱָ�룩
	(*L)->prior = NULL;
	(*L)->next = NULL;
	(*L)->data = 1;

	//��ʱ���ָ�����ȡ����Ԫ����ַ
	DLinkList temp = (*L);

	//2.���ݽ��
	for (int i = 2; i < 7; i++) {
		DLinkList newNode = (DLinkList)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = NULL;
		//β�巨
		newNode->prior = temp;
		temp->next = newNode;

		//����
		temp = temp->next;
	}
	return OK;
}

//�������
//���������������L�еĵ�n��λ��֮ǰ����������Ԫ��elem
Status insertDlinklist(DLinkList *L, int n, int elem) {
	if (n == 1) {//���뵽�����ͷ��Ҫ���⿼��
		//1.�����½ڵ�
		DLinkList newNode = (DLinkList)malloc(sizeof(Node));
		newNode->data = elem;

		//2.����(��ʱ*LΪָ����Ԫ����ָ��,����ֵ��Ϊ��Ԫ���ĵ�ַ)
		newNode->next = (*L);
		newNode->prior = NULL;
		(*L)->prior = newNode;
		(*L) = newNode;
		return OK;
	}
	else {
		DLinkList temp = (*L);	//ȡ����Ԫ���ĵ�ַ��ͷָ���д�ŵľ�����Ԫ���ĵ�ַ��

		//1.�ҵ�Ҫ����λ�õ�ǰһ�����
		for (int i = 1; i < n-1; i++) {
			temp = temp->next;
		}

		//2.�����½ڵ�
		DLinkList newNode = (DLinkList)malloc(sizeof(Node));
		newNode->data = elem;

		//3.����(���һ����㵥������)
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

//ɾ������
//���������ɾ������L��n��Ԫ��
Status deleteDlinklist(DLinkList *L, int n) {
	if (n == 1)
	{
		DLinkList del = (*L);
		(*L)->next->prior = NULL;
		(*L) = (*L)->next;
		free(del);
	}
	else {
		//ȡ����Ԫ���ĵ�ַ
		DLinkList temp = (*L);
		//�ҵ�Ҫɾ������ǰһ��λ��
		for (int i = 1; i < n - 1; i++) {
			temp = temp->next;
		}
		if (temp->next->next != NULL) {
			//ɾ��
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

//��ӡ˫������
Status displayDlinklist(DLinkList *L) {
	//��ʱ����ȡ��ͷ����ַ
	DLinkList temp = (*L);

	while (temp) {		
		printf(" %d", temp->data);
		temp = temp->next;
	}

	printf("\n");
	return OK;
}

//������
//����ʱ��Ӧ�������Ĳ���ֵ��������û���ж������Ƿ����
int main() {

	DLinkList D = NULL;
	
	//��ʼ�����
	initDlinklist(&D);
	displayDlinklist(&D);

	//�������
	insertDlinklist(&D,7,0);
	displayDlinklist(&D);

	//ɾ������
	deleteDlinklist(&D, 7);
	displayDlinklist(&D);

	return 0;
}
