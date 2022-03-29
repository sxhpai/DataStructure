
/******************* 两栈共享空间 *****************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define ERROR -1
#define OK 1

typedef int SElemType;
typedef int Status;

//两栈共享空间结构
typedef struct {
	SElemType data[MAXSIZE];
	int top1;	//栈1栈顶指针
	int top2;	//栈2栈顶指针
}SqDoubleStack;

//压栈
Status Push(SqDoubleStack *S, SElemType e, int stackNumber) {
	if (S->top1 + 1 == S->top2) {
		printf("栈满\n");
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

//弹栈
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber) {
	if (stackNumber == 1) {
		if (S->top1 == -1) {
			printf("1空栈\n");
			return ERROR;
		}
		else {
			*e = S->data[S->top1];
			S->top1--;
		}
	}
	else if (stackNumber == 2) {
		if (S->top2 == MAXSIZE) {
			printf("2空栈\n");
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

//将数组中元素全部输出
void DisplaySqDoubleStack(SqDoubleStack *S) {
	int i;
	for (i = 0; i < MAXSIZE; i++) {
		printf(" %d", S->data[i]);
	}
	printf("\n");
}

//主函数
int main() {
	SElemType e;
	int i;

	//共享空栈初始化
	SqDoubleStack S;
	S.top1 = -1;
	S.top2 = MAXSIZE;
	/*为了方便输出，所以给数组初始化了以下*/
	for (i = 0; i < MAXSIZE; i++) {
		S.data[i] = -2;
	}
	DisplaySqDoubleStack(&S);

	//入栈
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

