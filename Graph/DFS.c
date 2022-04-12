#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Boolean;        //Boolean是布尔类型，其值是TRUE或FALSE

typedef char VertexType;    //顶点类型
typedef int EdgeType;       //边上的权值类型
#define MAXVEX  100         //顶点的最大个数
#define INFINITY    65535   //用 65535 表示 ∞

Boolean visited[MAXVEX];    //访问标志的数组

//邻接矩阵
typedef struct 
{
    VertexType vexs[MAXVEX];        //顶点数组
    EdgeType arc[MAXVEX][MAXVEX];   //边数组
    int numVertexs,numEdges;        //图中当前的顶点数和边数
}MGraph;

//邻接表

//边表结点
typedef struct EdgeNode{
    int adjvex;
    EdgeType weight;
    struct EdgeNode *next;
}EdgeNode;

//顶点表结点
typedef struct VertexNode{
    VertexType data;
    EdgeNode *firstedge;
}VertexNode,AdjList[MAXVEX];

//邻接表
typedef struct {
    AdjList adjlist;
    int numVertexs,numEdges;
}GraphAdjList;

//无向图邻接矩阵存储结构的创建
void CreateMGraph(MGraph *G) {
    int i,j,k,w;
    printf("请输入图的顶点数和边数：\n");
    scanf("%d,%d",&G->numVertexs,&G->numEdges);
    getchar();
    printf("请输入顶点信息:\n");
    //顶点数组建立
    for(i = 0; i < G->numVertexs; i++) {
        scanf("%c",&G->vexs[i]);
        getchar();
    }
    //边数组建立
    //初始化边数组
    for(i = 0; i < G->numEdges; i++) {
        for(j = 0; j < G->numEdges; j++) {
            if(i == j){
                G->arc[i][j] = 0;
            }else{
                G->arc[i][j] = INFINITY;
            }
        }
    }
    //读入numEdges条边，建立邻接矩阵
    for(k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi,vj)的序号i,j 和权值 w:\n");
        scanf("%d,%d,%d",&i,&j,&w);
        getchar();
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];    //无向图所以对称
    }
}

//无向图邻接表存储结构创建
void CreateALGraph(GraphAdjList *G) { 
    int i,j,k,w;
    EdgeNode *e;
    printf("请输入图的结点数和边数：\n");
    scanf("%d,%d", &G->numVertexs, &G->numEdges);
    getchar();
    //顶点表
    printf("请输入顶点表信息:\n");
    for(i = 0; i < G->numVertexs; i++) {
        scanf("%c", &G->adjlist[i].data);
        getchar();
        G->adjlist[i].firstedge = NULL;
    }
    //边表
    for(k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi,vj)的序号i,j 和权值w:\n");
        scanf("%d,%d,%d", &i, &j, &w);

        e = (EdgeNode *)malloc(sizeof(EdgeNode*));  //申请空间，生成边结点
        e->weight = w;
        e->adjvex = j;  //邻接序号为j
        e->next = G->adjlist[i].firstedge;
        G->adjlist[i].firstedge = e;

        e = (EdgeNode *)malloc(sizeof(EdgeNode*));  //申请空间，生成边结点
        e->weight = w;
        e->adjvex = i;  //邻接序号为i
        e->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = e;
    }
} 

/********** 邻接矩阵的深度优先递归算法 ***************/
void DFS(MGraph G, int i) {
    int j;
    visited[i] = true;
    printf(" %c", G.vexs[i]);     //打印顶点结点，也可以其他操作
    for(j = 0; j < G.numVertexs; j++) {
        if(G.arc[i][j] == 1 && !visited[j]) {
            DFS(G,j);       //对访问的邻接结点递归调用
        }
    }
}
/********* 邻接矩阵深度遍历 **********/
void DFSTraverse(MGraph G)
{
    int i;
    for(i = 0; i < G.numVertexs; i++) {
        visited[i] = false;     //初始所有顶点状态都是未访问过状态
    }
    for(i = 0; i < G.numVertexs; i++) {
        if(!visited[i]) {       //未访问过的顶点调用DFS，若是连通图，只会执行一次
            DFS(G, i);
        }
    }
}
/********** 邻接表的深度优先递归算法 ***************/
void DFS_AL(GraphAdjList GL, int i)         //n个顶点e条边的图 邻接表的深度优先递归算法时间复杂度为：O(n+e)
{
   EdgeNode* temp;
   visited[i] = true;
   printf(" %c", GL.adjlist[i].data);       //打印顶点，也可以其他操作
   temp = GL.adjlist[i].firstedge;
   while (temp)
   {
       if (!visited[temp->adjvex]) {
           DFS_AL(GL, temp->adjvex);  //对为访问的邻接顶点递归调用
       }
       temp = temp->next;
   }
}

/*********** 邻接表的深度遍历操作 ***********/
void DFSTraverse_AL(GraphAdjList GL)
{
   int i;
   for (i = 0; i < GL.numVertexs; i++) {
       visited[i] = false;     //初始化所有顶点状态都是未访问过状态
   }
   for (i = 0; i < GL.numVertexs; i++) {
       if (!visited[i])    //对未访问过的顶点调用DFS，若是连通图，只会执行一次
           DFS_AL(GL, i);
   }
}

//打印无向图的邻接矩阵
void DisplayMGraph(MGraph G) {
    int i,j;
    for(i = 0; i < G.numVertexs; i++) {
        for(j = 0; j < G.numVertexs; j++) {
            printf("%-10d",G.arc[i][j]);
        }
        printf("\n");
    }
}

//打印无向图的邻接表
void DisplayALGraph(GraphAdjList G) {
    int i;
    EdgeNode *temp;
    for(i = 0; i < G.numVertexs; i++) {
        printf(" %c->",G.adjlist[i].data);
        temp = G.adjlist[i].firstedge;
        while(temp) {
            printf(" %d", temp->adjvex);
            temp = temp->next;
        }
        printf("\n");
    }
}
int main(){

    MGraph G;
    CreateMGraph(&G);
    DisplayMGraph(G);  
    DFSTraverse(G);

    GraphAdjList GL;
    CreateALGraph(&GL);
    DisplayALGraph(GL);
    DFSTraverse_AL(GL);

    return 0;
}