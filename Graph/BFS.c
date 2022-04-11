
/************** 广度优先遍历 **************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Boolean;        //Boolean是布尔类型，其值是TRUE或FALSE

typedef char VertexType;    //顶点类型
typedef int EdgeType;       //边上的权值类型
#define MAXVEX  100         //顶点的最大个数
#define INFINITY    65535   //用 65535 表示 ∞

Boolean visited[MAXVEX];    //访问标志的数组

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
typedef struct
{
    VertexType vexs[MAXVEX];        //顶点数组
    EdgeType arc[MAXVEX][MAXVEX];   //边数组
    int numVertexs, numEdges;        //图中当前的顶点数和边数
}MGraph;

//边表结点
typedef struct EdgeNode {
    int adjvex;
    EdgeType weight;
    struct EdgeNode* next;
}EdgeNode;

//顶点表结点
typedef struct VertexNode {
    VertexType data;
    EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

//邻接表
typedef struct {
    AdjList adjlist;
    int numVertexs, numEdges;
}GraphAdjList;



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

//无向图邻接矩阵存储结构的创建
void CreateMGraph(MGraph* G) {
    int i, j, k, w;
    printf("请输入图的顶点数和边数：\n");
    scanf("%d,%d", &G->numVertexs, &G->numEdges);
    getchar();
    printf("请输入顶点信息:\n");
    //顶点数组建立
    for (i = 0; i < G->numVertexs; i++) {
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    //边数组建立
    //初始化边数组
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
    //读入numEdges条边，建立邻接矩阵
    for (k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi,vj)的序号i,j 和权值 w:\n");
        scanf("%d,%d,%d", &i, &j, &w);
        getchar();
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];    //无向图所以对称
    }
}

//无向图邻接表存储结构创建
void CreateALGraph(GraphAdjList* G) {
    int i, j, k, w;
    EdgeNode* e;
    printf("请输入图的结点数和边数：\n");
    scanf("%d,%d", &G->numVertexs, &G->numEdges);
    getchar();
    //顶点表
    printf("请输入顶点表信息:\n");
    for (i = 0; i < G->numVertexs; i++) {
        scanf("%c", &G->adjlist[i].data);
        getchar();
        G->adjlist[i].firstedge = NULL;
    }
    //边表
    for (k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi,vj)的序号i,j 和权值w:\n");
        scanf("%d,%d,%d", &i, &j, &w);

        e = (EdgeNode*)malloc(sizeof(EdgeNode));  //申请空间，生成边结点
        e->weight = w;
        e->adjvex = j;  //邻接序号为j
        e->next = G->adjlist[i].firstedge;
        G->adjlist[i].firstedge = e;

        e = (EdgeNode*)malloc(sizeof(EdgeNode));  //申请空间，生成边结点
        e->weight = w;
        e->adjvex = i;  //邻接序号为i
        e->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = e;
    }
}

/*********邻接矩阵的广度遍历算法*********/
void BFSTraverse(MGraph G)
{
    int i, j;
    LinkQueue Q;
    for (i = 0; i < G.numVertexs; i++) {    
        visited[i] = false; //将所有结点初始化为未访问状态
    }
    InitLinkQueue(&Q);      //初始化一辅助用的队列

    for (i = 0; i < G.numVertexs; i++) {
        if (!visited[i])        //若是未访问过就处理
        {
            visited[i] = true;          //设置当前结点访问过
            printf(" %c", G.vexs[i]);   //打印顶点，也可以其他操作
            EnQueue(&Q, i);             //将此顶点入队列
            while (Q.count) {
                DeQueue(&Q, &i);        //将队中元素出队列，赋值给i
                for (j = 0; j < G.numVertexs; j++) {
                    //判断其他顶点若与当前顶点存在边且未访问过
                    if (G.arc[i][j] == 1 && !visited[j]) {
                        visited[j] = true;      //将找到的此顶点标记为已访问
                        printf("%c", G.vexs[j]);    //打印顶点
                        EnQueue(&Q, j);             //将找到的顶点入队列
                    }
                }
            }
        }
    }
}

/***************** 邻接表的广度遍历算法 *******************/
void BFSTraverse_AL(GraphAdjList GL) {
    int i;
    EdgeNode* temp;
    LinkQueue Q;
    for (i = 0; i < GL.numVertexs; i++) {
        visited[i] = false;
    }
    InitLinkQueue(&Q);
    for (i = 0; i < GL.numVertexs; i++) {
        if (!visited[i]) {
            visited[i] = true;
            printf("%c", GL.adjlist[i].data);   //打印顶点，也可以其他操作
            EnQueue(&Q, i);
            while (Q.count) {
                DeQueue(&Q, &i);
                temp = GL.adjlist[i].firstedge;
                while (temp) {
                    if (!visited[temp->adjvex]) {
                        visited[temp->adjvex] = true;
                        printf("%c", GL.adjlist[temp->adjvex].data);
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
void DisplayALGraph(GraphAdjList G) {
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

    //邻接矩阵
    //MGraph G;

    //CreateMGraph(&G);
    //DisplayMGraph(G);
    //BFSTraverse(G);

    //邻接表
    GraphAdjList GL;

    CreateALGraph(&GL);
    DisplayALGraph(GL);
    BFSTraverse_AL(GL);

    return 0;
}