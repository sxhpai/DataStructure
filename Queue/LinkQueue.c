
/********* ���е���ʽ�洢�ṹ *********/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1
#define MAXSIZE 10 //���е����ռ�����

typedef int Status;
typedef int QElemType;

//���ṹ
typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

//���е�����ṹ
typedef struct {
	QueuePtr front;
	QueuePtr rear;
	int count;
}LinkQueue;

//��ʼ������ʽ����
Status InitLinkQueue(LinkQueue *Q) {
	//ͷ���
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if (!temp) {
		printf("�����ڴ�ʧ��");
		return ERROR;
	}
	temp->next = NULL;

	Q->front = temp;	//ͷָ��ָ��ͷ���
	Q->rear = temp;		//βָ��ָ��ͷ���
	Q->count = 0;

	return OK;
}

//����
Status EnQueue(LinkQueue *Q, QElemType e) {
	//�½ڵ�
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if (!temp) {
		printf("�����ڴ�ʧ��");
		return ERROR;
	}
	temp->data = e;
	temp->next = NULL;

	//β����
	Q->rear->next = temp;	//���½ڵ��β������
	Q->rear = temp;		//βָ��ָ���β���
	Q->count++;

	return OK;
}

//����
Status DeQueue(LinkQueue *Q, QElemType *e) {
	if (Q->front == Q->rear) {
		printf("����");
		return ERROR;
	}
	//����
	QueuePtr del = Q->front->next;
	*e = Q->front->next->data;
	Q->front->next = Q->front->next->next;
	//����һ�����������һ����㣬��ͷ�Ƕ�β����ɾ���󣬽�rearָ��ָ��ͷ��㡣��ʱΪ�ն��С�
	if (Q->rear == del) {
		Q->rear = Q->front;
	}

	free(del);	//�ͷſռ�

	Q->count--;

	return OK;
}

//��ӡ�����ڵ�����Ԫ��
void Display(LinkQueue Q) {
	//ȡ��ͷ���
	QueuePtr temp = Q.front->next;

	for (int i = 0; i < Q.count; i++) {
		printf(" %d", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main() {

	QElemType e;
	LinkQueue Q;
	//��ʼ���ն���
	InitLinkQueue(&Q);

	//����
	for (int i = 0; i < 4; i++) {
		EnQueue(&Q, i);
	}
	Display(Q);

	//����
	while (Q.front != Q.rear) {
		DeQueue(&Q, &e);
		printf(" %d", e);
		//printf("sheng:\n");
		//Display(Q);
	}


	return 0;
}
