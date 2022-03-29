 
/******************* 链栈 ******************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define ERROR -1
#define OK 1

typedef int SElemType;
typedef int Status;

//栈结点
typedef struct StackNode {
	SElemType data;
	struct StackNode *next;
}StackNode,*LinkStackPtr;

//链栈
typedef struct LinkStack {
	LinkStackPtr top;
	int count;
}LinkStack;

//压栈
Status Push(LinkStack *S, SElemType e) {
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
Status Pop(LinkStack *S, SElemType *e) {
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

//打印栈内所有数据
void DisplayLinkStack(LinkStack *S) {
	int i;
	LinkStackPtr temp = S->top;
	for (i = 0; i < S->count; i++) {
		printf(" %d", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//主函数
int main() {
	int i;
	SElemType e;

	//初始化一个空栈
	LinkStack S;
	S.top = NULL;
	S.count = 0;

	//压栈
	for (i = 0; i < 21; i++) {
		Push(&S, i);
	}
	DisplayLinkStack(&S);

	//弹栈
	for (i = 0; i < 5; i++) {
		Pop(&S,&e);
		printf(" %d\n", e);//打印弹出的元素
	}
	DisplayLinkStack(&S);

	return 0;
}
