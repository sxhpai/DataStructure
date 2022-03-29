
/***************** ˳��ջ *******************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define ERROR -1
#define OK 1

typedef int SElemType;
typedef int Status;

//ջ�Ľṹ����
typedef struct {
	SElemType data[MAXSIZE];
	int top;		//����ָ��ջ����ָ�����˼�ǣ�top����������±꣩
}SqStack;

//ѹջ
Status Push(SqStack *S, SElemType e) {
	//�ж��Ƿ���ջ
	if (S->top == MAXSIZE - 1) {
		printf("��ջ");
		return ERROR;
	}
	//ѹ��
	S->top++;
	S->data[S->top] = e;

	return OK;
}

//��ջ
Status Pop(SqStack *S, SElemType *e) {
	//�ж��Ƿ��ջ
	if (S->top == -1) {
		printf("��ջ");
		return ERROR;
	}
	//����
	*e = S->data[S->top];
	S->top--;

	return OK;
}

//��ӡջ��Ԫ��
//��ջ����ջ�����δ�ӡ
void DisplayStack(SqStack *S) {
	int i;
	for (i = (*S).top; i > -1; i--) {
		printf(" %d", (*S).data[i]);
	}
	printf("\n");
}

//������
int main() {
	SElemType e;
	
	//��ջ��ʼ��
	SqStack S;
	S.top = -1;

	//��ջ
	int i;
	for (i = 0; i < 10; i++) {
		Push(&S, i);
	}
	DisplayStack(&S);

	//��ջ
	printf(" ������Ԫ�������ǣ�\n");
	for (i = S.top; i > 0; i--) {
		Pop(&S, &e);
		printf(" %d", e);//��ӡ��ջ��Ԫ��
	}
	printf("\n ջ�л�ʣ��\n");
	DisplayStack(&S);//��ӡջ�л�ʣ��Ԫ��

	//Pop(&S, &e);
	//printf(" e = %d\n", e);
	//Pop(&S, &e);
	//printf(" e = %d\n", e);
	//DisplayStack(&S);

	return 0;
}

