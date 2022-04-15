
/*************** 邻接矩阵和邻接表 ******************/
/********** 深度优先遍历 和 广度优先遍历 ***********/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char VertexType;	//顶点数据域类型
typedef int EdgeType;		//边上的权值类型
typedef int Boolen;
#define MAXVEX 100			//顶点的最大个数
#define INFINITY 65535		//用65535表示∞

Boolen Visited[MAXVEX];

#define ERROR -1
#define OK 1
#define MAXSIZE 10 //队列的最大空间容量

typedef int Status;
typedef int QElemType;

//结点结构
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

//队列的链表结构
typedef struct {
	QueuePtr front;
	QueuePtr rear;
	int count;
}LinkQueue;

//邻接矩阵
typedef struct {
	VertexType vex[MAXVEX];			//顶点数组
	EdgeType arc[MAXVEX][MAXVEX];	//边数组，邻接矩阵的权重写道边数组中
	int numVertexs, numEdges;		//顶点数和边数
}MGraph;

//边结点
typedef struct EdgeNode {
	int adjvex;		//邻接结点存的顶点的序号
	EdgeType weight;		//邻接表的权重写在边结点中
	struct EdgeNode* next;	//下一个邻接结点
}EdgeNode;

//顶点
typedef struct VertexNode{
	VertexType data;		//顶点数据
	EdgeNode* firstedge;	//指向第一条边
}VertexNode,AdjList[MAXVEX];

//邻接表
typedef struct {
	AdjList adjlist;		//建立顶点表
	int numVertexs, numEdges;
}ALGraph;


//初始化空链式队列
Status InitLinkQueue(LinkQueue* Q) {
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
Status EnQueue(LinkQueue* Q, QElemType e) {
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
Status DeQueue(LinkQueue* Q, QElemType* e) {
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

//创建无向图的邻接矩阵
void CreateMGraph(MGraph* G) {
	int i,j,k;
	printf("请输入顶点和边的数目：\n");
	scanf_s("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();

	printf("请输入顶点信息：\n");
	for (i = 0; i < G->numVertexs; i++) {
		scanf_s("%c", &G->vex[i]);
		getchar();
	}
	//初始化边表
	for (i = 0; i < G->numEdges; i++) {
		for (j = 0; j < G->numEdges; j++) {
			if (i == j) {
				G->arc[i][j] = 0;
			}
			else {
				G->arc[i][j] = INFINITY;
			}
		}
	}
	//读入边表信息
	for (k = 0; k < G->numEdges; k++) {
		printf("请输入(vi,vj)的序号i,j：\n");
		scanf_s("%d,%d", &i, &j);
		getchar();
		G->arc[i][j] = 1;
		G->arc[j][i] = G->arc[i][j];
	}
}

//创建无向图的邻接表
void CreateALGraph(ALGraph* G) {
	int i, j, k;
	EdgeNode* e;
	printf("请输入图的结点数和边数：\n");
	scanf_s("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();
	//顶点表
	printf("请输入顶点表信息:\n");
	for (i = 0; i < G->numVertexs; i++) {
		scanf_s("%c", &G->adjlist[i].data);
		getchar();
		G->adjlist[i].firstedge = NULL;
	}
	//边表
	for (k = 0; k < G->numEdges; k++) {
		printf("请输入边(vi,vj)的序号i,j:\n");
		scanf_s("%d,%d", &i, &j);

		e = (EdgeNode*)malloc(sizeof(EdgeNode));  //申请空间，生成边结点
		e->weight = 1;		//权值默认都是1
		e->adjvex = j;  //邻接序号为j
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;

		e = (EdgeNode*)malloc(sizeof(EdgeNode));  //申请空间，生成边结点
		e->weight = 1;
		e->adjvex = i;  //邻接序号为i
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
}

/***************** 深度优先遍历算法 *****************/

//邻接矩阵深度优先递归算法
void DFS_M(MGraph G, int i) {
	int j;
	Visited[i] = true;
	printf("%c", G.vex[i]);
	for (j = 0; j < G.numVertexs; j++) {
		if (G.arc[i][j] == 1 && !Visited[j]) {
			DFS_M(G, j);
		}
	}
}
//邻接矩阵深度优先遍历算法
void DFSTraverse_M(MGraph G) {
	int i;
	for (i = 0; i < G.numVertexs; i++) {
		Visited[i] = false;
	}
	for (i = 0; i < G.numVertexs; i++) {
		if (!Visited[i]) {
			DFS_M(G, i);
		}
	}
}
//邻接表深度优先递归算法
void DFS_AL(ALGraph GL, int i)         //n个顶点e条边的图 邻接表的深度优先递归算法时间复杂度为：O(n+e)
{
    EdgeNode* temp;
    Visited[i] = true;
    printf(" %c", GL.adjlist[i].data);       //打印顶点，也可以其他操作
    temp = GL.adjlist[i].firstedge;
    while (temp)
    {
        if (!Visited[temp->adjvex]) {
            DFS_AL(GL, temp->adjvex);  //对为访问的邻接顶点递归调用
        }
        temp = temp->next;
    }
}

//邻接表深度优先遍历算法
void DFSTraverse_AL(ALGraph GL)
{
    int i;
    for (i = 0; i < GL.numVertexs; i++) {
        Visited[i] = false;     //初始化所有顶点状态都是未访问过状态
    }
    for (i = 0; i < GL.numVertexs; i++) {
        if (!Visited[i])    //对未访问过的顶点调用DFS，若是连通图，只会执行一次
            DFS_AL(GL, i);
    }
}

/***************** 广度优先遍历算法 ********************/

//邻接矩阵广度优先遍历
void BFSTraverse_M(MGraph G) {
	int i, j;
	LinkQueue Q;
	//初始化
	for (i = 0; i < G.numVertexs; i++) {	
		Visited[i] = false;
	}
	InitLinkQueue(&Q);

	for (i = 0; i < G.numVertexs; i++) {	//遍历每一个结点
		if (!Visited[i]) {
			Visited[i] = true;
			printf(" %c", G.vex[i]);
			EnQueue(&Q, i);
			while (Q.count) {
				DeQueue(&Q, &i);
				for (j = 0; j < G.numVertexs; j++) {
					if (G.arc[i][j] == 1 && !Visited[j]) {
						Visited[j] = true;
						printf(" %c", G.vex[j]);
						EnQueue(&Q, j);
					}
				}
			}
		}
	}
}

//邻接表广度优先遍历
void BFSTraverse_AL(ALGraph GL) {
    int i;
    EdgeNode* temp;
    LinkQueue Q;
    for (i = 0; i < GL.numVertexs; i++) {
        Visited[i] = false;
    }
    InitLinkQueue(&Q);
    for (i = 0; i < GL.numVertexs; i++) {
        if (!Visited[i]) {
			Visited[i] = true;
            printf("%c", GL.adjlist[i].data);   //打印顶点，也可以其他操作
            EnQueue(&Q, i);
            while (Q.count) {
                DeQueue(&Q, &i);
                temp = GL.adjlist[i].firstedge;
                while (temp) {
                    if (!Visited[temp->adjvex]) {
						Visited[temp->adjvex] = true;
                        printf(" %c", GL.adjlist[temp->adjvex].data);
                        EnQueue(&Q, temp->adjvex);
                    }
                    temp = temp->next;
                }
            }
        }
    }
}

//打印无向图的邻接矩阵
void DisplayMGraph(MGraph G) {
	int i, j;
	for (i = 0; i < G.numVertexs; i++) {
		for (j = 0; j < G.numVertexs; j++) {
			printf("%-10d", G.arc[i][j]);
		}
		printf("\n");
	}
}

//打印无向图的邻接表
void DisplayALGraph(ALGraph G) {
	int i;
	EdgeNode* temp;
	for (i = 0; i < G.numVertexs; i++) {
		printf(" %c->", G.adjlist[i].data);
		temp = G.adjlist[i].firstedge;
		while (temp) {
			printf(" %d", temp->adjvex);
			temp = temp->next;
		}
		printf("\n");
	}
}


int main() {
	
	//MGraph G;
	//CreateMGraph(&G);
	//DisplayMGraph(G);
	//DFSTraverse_M(G);
	//printf("\n");
	//BFSTraverse_M(G);

	ALGraph G;
	CreateALGraph(&G);
	DisplayALGraph(G);
	DFSTraverse_AL(G);
	printf("\n");
	BFSTraverse_AL(G);

	return 0;
}