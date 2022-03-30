
/*********** 循环队列的顺序存储结构 *********/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1
#define MAXSIZE 10 //队列的最大空间容量

typedef int Status;
typedef int QElemType;

//循环队列的顺序存储结构
typedef struct {
	QElemType data[MAXSIZE];
	int front;		//头指针
	int rear;		//尾指针，若队列不空，指向队列尾元素的下一个位置。
}SqQueue;

//初始化一个空队列
Status InitQueue(SqQueue *Q) {
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//返回Q的元素个数，也就是队列的当前长度
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front) % MAXSIZE;
}

//若队列未满，则插入元素e为Q新的队尾元素
Status EnQueue(SqQueue *Q, QElemType e) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {	//队满判断
		printf("满列");
		return ERROR;
	}
	Q->data[Q->rear] = e;	//将元素e赋值给队尾
	Q->rear = (Q->rear + 1) % MAXSIZE;	//rear指针向后移一个位置，若到最后一个位置则转到数组头部

	return OK;
}

//若队列不空，则删除Q中队头元素，用e返回其值。
Status DeQueue(SqQueue *Q, QElemType *e) {	//队空判断
	if (Q->rear == Q->front) {
		printf("空列");
		return ERROR;
	}
	*e = Q->data[Q->front];		//将对头元素赋给e
	Q->front = (Q->front + 1) % MAXSIZE;	//front指针向后移一个位置，若到最后则转到数组头部

	return OK;
}

void Display(SqQueue Q) {
	int length = QueueLength(Q);
	for (int i = Q.front; i < length; i++)
	{
		printf(" %d", Q.data[Q.front]);
		Q.front = (Q.front + 1) % MAXSIZE;
	}
	printf("\n");
}

int main() {
	int e;
	SqQueue Q;
	//初始化空循环队列
	InitQueue(&Q);

	//入列
	for (int i = 0; i < 6; i++)
	{
		EnQueue(&Q, i);
	}
	Display(Q);

	//出列
	while (Q.front != Q.rear)
	{
		DeQueue(&Q, &e);
		printf(" %d", e);
	}

	return 0;
}
