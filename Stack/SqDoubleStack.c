
/******************* ��ջ����ռ� *****************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define ERROR -1
#define OK 1

typedef int SElemType;
typedef int Status;

//��ջ����ռ�ṹ
typedef struct {
	SElemType data[MAXSIZE];
	int top1;	//ջ1ջ��ָ��
	int top2;	//ջ2ջ��ָ��
}SqDoubleStack;

//ѹջ
Status Push(SqDoubleStack *S, SElemType e, int stackNumber) {
	if (S->top1 + 1 == S->top2) {
		printf("ջ��\n");
		return ERROR;
	}
	if (stackNumber == 1) {
		S->top1++;
		S->data[S->top1] = e;
	}
	else if (stackNumber == 2) {
		S->top2--;
		S->data[S->top2] = e;
	}
	else{
		return ERROR;
	}
	return OK;
}

//��ջ
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber) {
	if (stackNumber == 1) {
		if (S->top1 == -1) {
			printf("1��ջ\n");
			return ERROR;
		}
		else {
			*e = S->data[S->top1];
			S->top1--;
		}
	}
	else if (stackNumber == 2) {
		if (S->top2 == MAXSIZE) {
			printf("2��ջ\n");
			return ERROR;
		}
		else {
			*e = S->data[S->top2];
			S->top2++;
		}
	}
	else {
		return ERROR;
	}
	return OK;
}

//��������Ԫ��ȫ�����
void DisplaySqDoubleStack(SqDoubleStack *S) {
	int i;
	for (i = 0; i < MAXSIZE; i++) {
		printf(" %d", S->data[i]);
	}
	printf("\n");
}

//������
int main() {
	SElemType e;
	int i;

	//�����ջ��ʼ��
	SqDoubleStack S;
	S.top1 = -1;
	S.top2 = MAXSIZE;
	/*Ϊ�˷�����������Ը������ʼ��������*/
	for (i = 0; i < MAXSIZE; i++) {
		S.data[i] = -2;
	}
	DisplaySqDoubleStack(&S);

	//��ջ
	for (i = 0; i < 3; i++) {
		Push(&S, i, 1);
	}
	DisplaySqDoubleStack(&S);

	for (i = 0; i < 3; i++) {
		Push(&S, i, 2);
	}
	DisplaySqDoubleStack(&S);

	Pop(&S, &e, 1);
	printf(" e = %d\n", e);
	Pop(&S, &e, 1);
	printf(" e = %d\n", e);

	Pop(&S, &e, 2);
	printf(" e = %d\n", e);
	Pop(&S, &e, 2);
	printf(" e = %d\n", e);
	Pop(&S, &e, 2);
	printf(" e = %d\n", e);

	return 0;
}

