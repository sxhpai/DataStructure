 
/******************* ��ջ ******************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define ERROR -1
#define OK 1

typedef int SElemType;
typedef int Status;

//ջ���
typedef struct StackNode {
	SElemType data;
	struct StackNode *next;
}StackNode,*LinkStackPtr;

//��ջ
typedef struct LinkStack {
	LinkStackPtr top;
	int count;
}LinkStack;

//ѹջ
Status Push(LinkStack *S, SElemType e) {
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
Status Pop(LinkStack *S, SElemType *e) {
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

//��ӡջ����������
void DisplayLinkStack(LinkStack *S) {
	int i;
	LinkStackPtr temp = S->top;
	for (i = 0; i < S->count; i++) {
		printf(" %d", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//������
int main() {
	int i;
	SElemType e;

	//��ʼ��һ����ջ
	LinkStack S;
	S.top = NULL;
	S.count = 0;

	//ѹջ
	for (i = 0; i < 21; i++) {
		Push(&S, i);
	}
	DisplayLinkStack(&S);

	//��ջ
	for (i = 0; i < 5; i++) {
		Pop(&S,&e);
		printf(" %d\n", e);//��ӡ������Ԫ��
	}
	DisplayLinkStack(&S);

	return 0;
}
