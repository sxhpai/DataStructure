
/********* 队列的链式存储结构 *********/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1
#define MAXSIZE 10 //队列的最大空间容量

typedef int Status;
typedef int QElemType;

//结点结构
typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

//队列的链表结构
typedef struct {
	QueuePtr front;
	QueuePtr rear;
	int count;
}LinkQueue;

//初始化空链式队列
Status InitLinkQueue(LinkQueue *Q) {
	//头结点
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if (!temp) {
		printf("分配内存失败");
		return ERROR;
	}
	temp->next = NULL;

	Q->front = temp;	//头指针指向头结点
	Q->rear = temp;		//尾指针指向头结点
	Q->count = 0;

	return OK;
}

//入列
Status EnQueue(LinkQueue *Q, QElemType e) {
	//新节点
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if (!temp) {
		printf("分配内存失败");
		return ERROR;
	}
	temp->data = e;
	temp->next = NULL;

	//尾入列
	Q->rear->next = temp;	//将新节点从尾部插入
	Q->rear = temp;		//尾指针指向队尾结点
	Q->count++;

	return OK;
}

//出列
Status DeQueue(LinkQueue *Q, QElemType *e) {
	if (Q->front == Q->rear) {
		printf("空列");
		return ERROR;
	}
	//出列
	QueuePtr del = Q->front->next;
	*e = Q->front->next->data;
	Q->front->next = Q->front->next->next;
	//若第一个结点就是最后一个结点，队头是队尾，则删除后，将rear指针指向头结点。此时为空队列。
	if (Q->rear == del) {
		Q->rear = Q->front;
	}

	free(del);	//释放空间

	Q->count--;

	return OK;
}

//打印队列内的所有元素
void Display(LinkQueue Q) {
	//取出头结点
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
	//初始化空队列
	InitLinkQueue(&Q);

	//入列
	for (int i = 0; i < 4; i++) {
		EnQueue(&Q, i);
	}
	Display(Q);

	//出列
	while (Q.front != Q.rear) {
		DeQueue(&Q, &e);
		printf(" %d", e);
		//printf("sheng:\n");
		//Display(Q);
	}


	return 0;
}
