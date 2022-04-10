
/********************* 图的存储结构 ***********************/
/******************* 邻接矩阵和邻接表 *********************/

#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;	//顶点类型
typedef int EdgeType;		//边上的权值类型
#define MAXVEX 100			//最大顶点数
#define INFINITY 65535		//用65535来代表∞

/* 邻接矩阵 */
typedef struct
{
	VertexType vexs[MAXVEX];			//顶点表
	EdgeType arc[MAXVEX][MAXVEX];		//邻接矩阵，边表
	int numVertexes, numEdges;			//图中当前的顶点数和边数
}MGraph;

/* 邻接表 */

//边表结点结构
typedef struct EdgeNode {	
	int adjvex;				//邻接点域，存储该顶点对应的下标
	EdgeType weight;		//用于存储权值，对于非网图可以不需要
	struct EdgeNode* next;
}EdgeNode;

//顶点表结点结构
typedef struct VertexNode {
	VertexType data;		//顶点域，存储顶点信息
	EdgeNode* firstedge;	//边表头指针
}VertexNode,AdjList[MAXVEX];

//邻接表
typedef struct {
	AdjList adjList;
	int numVertexs, numEdges;	//图中当前顶点数和边数
}GraphAdjList;

//建立无向网络图的邻接矩阵表示
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("输入顶点数和边数:\n");
	scanf("%d %d", &G->numVertexes, &G->numEdges);	//输入顶点数和边数
	getchar();
	printf("%d,%d", G->numVertexes, G->numEdges);
	printf("请输入顶点：\n");
	//顶点表初始化
	for (i = 0; i < G->numVertexes; i++) {
		scanf("%c", & (G->vexs[i]));
		getchar();
	}
	
	//邻接表初始化
	for (i = 0; i < G->numVertexes; i++) {
		for (j = 0; j < G->numVertexes; j++) {
			if (i == j) {
				G->arc[i][j] = 0;
			}
			else
			{
				G->arc[i][j] = INFINITY;
			}
		}
	}
	//读入numEdges条边，建立邻接矩阵
	for (k = 0; k < G->numEdges; k++) {
		printf("输入边（vi,vj）上的下标i，下标j和权 w:\n");
		scanf("%d,%d,%d", &i, &j, &w);	//输入边（vi,vj）上的权w
		getchar();
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];		//因为是无向图，矩阵对称。

	}
}

//建立无向图的邻接表结构
void CreateALGraph(GraphAdjList* G) 
{
	int i, j, k;
	EdgeNode* e;
	printf("请输入顶点数和边数:\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);	//输入顶点数和边数
	getchar();
	printf("请输入顶点信息：\n");
	//读入顶点信息建立顶点表
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c", & (G->adjList[i].data));	//输入顶点信息	
		getchar();
		G->adjList[i].firstedge = NULL;	//将边表置为空表
	}

	//建立边表
	for (k = 0; k < G->numEdges; k++) {
		printf("输入边(vi,vj)上的顶点序号：\n");
		scanf("%d,%d", &i, &j);		//输入边(vi,vj)上的顶点序号
		getchar();

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//生成边表结点
		//插入
		e->adjvex = j;	//邻接序号	
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//生成边表结点
		//插入
		e->adjvex = i;	//邻接序号
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

//建立有向图的邻接表结构
void CreateALGraphDir(GraphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("请输入顶点数和边数:\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);	//输入顶点数和边数
	getchar();
	printf("请输入顶点信息：\n");
	//读入顶点信息建立顶点表
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c", &(G->adjList[i].data));	//输入顶点信息	
		getchar();
		G->adjList[i].firstedge = NULL;	//将边表置为空表
	}

	//建立边表
	for (k = 0; k < G->numEdges; k++) {
		printf("输入边(vi,vj)上的顶点序号：\n");
		scanf("%d,%d", &i, &j);		//输入边(vi,vj)上的顶点序号
		getchar();

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//生成边表结点
		//头插法
		e->adjvex = j;	//邻接序号	
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;
	}
}

void DisplayALGraph(GraphAdjList G)
{
	int i;
	EdgeNode* e;
	for (i = 0; i < G.numVertexs; i++) {
		printf("%d: %c ->",i, G.adjList[i].data);
		e = G.adjList[i].firstedge;
		while (e) {
			printf(" %d", e->adjvex);
			e = e->next;
		}
		printf("\n");
	}
}

void DisplayMGraph(MGraph G)
{
	int i, j;
	for (i = 0; i < G.numVertexes; i++) {
		printf(" %c", G.vexs[i]);
	}
	printf("\n\n");
	for (i = 0; i < G.numVertexes; i++) {
		for (j = 0; j < G.numVertexes; j++) {
			printf(" %-10d", G.arc[i][j]);
		}
		printf("\n");
	}
}


int main() {

	//MGraph G;

	//CreateMGraph(&G);
	//DisplayMGraph(G);

	GraphAdjList G;
    //无向图邻接表建立
    CreateALGraph(&G);
	DisplayALGraph(G);

    //有向图邻接表建立
	// CreateALGraphDir(&G);
	// DisplayALGraph(G);

	return 0;
}