
/***************** 顺序栈 *******************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define ERROR -1
#define OK 1

typedef int SElemType;
typedef int Status;

//栈的结构定义
typedef struct {
	SElemType data[MAXSIZE];
	int top;		//用于指向栈顶（指向的意思是：top代表数组的下标）
}SqStack;

//压栈
Status Push(SqStack *S, SElemType e) {
	//判断是否满栈
	if (S->top == MAXSIZE - 1) {
		printf("满栈");
		return ERROR;
	}
	//压入
	S->top++;
	S->data[S->top] = e;

	return OK;
}

//弹栈
Status Pop(SqStack *S, SElemType *e) {
	//判断是否空栈
	if (S->top == -1) {
		printf("空栈");
		return ERROR;
	}
	//弹出
	*e = S->data[S->top];
	S->top--;

	return OK;
}

//打印栈中元素
//从栈顶到栈底依次打印
void DisplayStack(SqStack *S) {
	int i;
	for (i = (*S).top; i > -1; i--) {
		printf(" %d", (*S).data[i]);
	}
	printf("\n");
}

//主函数
int main() {
	SElemType e;
	
	//空栈初始化
	SqStack S;
	S.top = -1;

	//入栈
	int i;
	for (i = 0; i < 10; i++) {
		Push(&S, i);
	}
	DisplayStack(&S);

	//出栈
	printf(" 弹出的元素依次是：\n");
	for (i = S.top; i > 0; i--) {
		Pop(&S, &e);
		printf(" %d", e);//打印出栈的元素
	}
	printf("\n 栈中还剩：\n");
	DisplayStack(&S);//打印栈中还剩的元素

	//Pop(&S, &e);
	//printf(" e = %d\n", e);
	//Pop(&S, &e);
	//printf(" e = %d\n", e);
	//DisplayStack(&S);

	return 0;
}
