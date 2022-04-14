#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char VertexType;	//顶点数据域类型
typedef int EdgeType;		//边上的权值类型
#define MAXVEX 100			//顶点的最大个数
#define MAXEDGE 100
#define INFINITY 65535		//用65535表示∞

//邻接矩阵
typedef struct {
	VertexType vex[MAXVEX];			//顶点数组
	EdgeType arc[MAXVEX][MAXVEX];	//边数组，邻接矩阵的权重写道边数组中
	int numVertexs, numEdges;		//顶点数和边数
}MGraph;

//边集数组 Edge 结构的定义
typedef struct {
	int begin;
	int end;
	int weight;
}Edge;

//创建无向图的邻接矩阵
void CreateMGraph(MGraph* G) {
	int i,j,k,w;
	printf("请输入顶点和边的数目：\n");
	scanf_s("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();

	printf("请输入顶点信息：\n");
	for (i = 0; i < G->numVertexs; i++) {
		scanf_s("%c", &G->vex[i]);
		getchar();
	}
	//初始化边矩阵
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
	//读入边矩阵信息
	for (k = 0; k < G->numEdges; k++) {
		printf("请输入(vi,vj)的序号i,j和权重:\n");
		scanf_s("%d,%d,%d", &i, &j, &w);
		getchar();
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
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

//普里姆算法生成最小生成树
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		//保存相关顶点下标
	int lowcost[MAXVEX];	//保存相关顶点间边的权值
	lowcost[0] = 0;		//初始化第一个权值为0，即v0加入生成树
						/* lowcost 的值为0，在这里就是此下标的顶点已经加入生成树*/
	adjvex[0] = 0;		//初始化第一个顶点下标为0
	for(i = 1; i < G.numVertexs; i++) {	//循环除了下标为0外的全部顶点
		lowcost[i] = G.arc[0][i];		//将v0顶点与之有边的权值存入数组
		adjvex[i] = 0;					//初始化都为v0的下标,每个元素都是v0的下标
	}
	//
	for(i = 1; i < G.numVertexs; i++) {
		min = INFINITY;		//初始化最小权值为∞
		j = 1; k = 0;
		while(j < G.numVertexs) {	//循环全部顶点,找到与v0相连的最小权值边。
			if(lowcost[j] != 0 && lowcost[j] < min) {
				//如果权值不为0且权值小于min
				min = lowcost[j];		//则将当前权值成为最小值
				k = j;					//将当前最小值的下标存入k
			}
			j++;
		}
		printf(" (%d,%d)",adjvex[k],k);	//打印当前顶点边中权值最小边
		lowcost[k] = 0;	//将当前顶点的权值设为0，表示此顶点已经完成任务
		for(j = 1; j < G.numVertexs; j++) {	//循环所有顶点
			if(lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
				//若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
				lowcost[j] = G.arc[k][j];		//将较小权值存入lowcost
				adjvex[j] = k;				//将下标为k的顶点存入adjvex
			}
		}
	}
}

int Find(int *parent, int f);

//克鲁斯卡尔算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph G)		//生成最小生成树
{
	int i, j, k, p, n, m;
	Edge edges[MAXEDGE];	//定义边集数组
	int parent[MAXVEX];	//定义一数组用来判断边与边是否形成环路

	//将邻接矩阵G转化为边集数组edges并按权由小到大排序
	k = 0;
	Edge e;
	for(i = 0; i < G.numVertexs; i++) {
		for(j = i; j < G.numVertexs; j++) {
			if(G.arc[i][j] > 0 && G.arc[i][j] < INFINITY) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	for(i = 0; i < k; i++) {
		for(j = i+1; j < k; j++) {
			if(edges[j].weight < edges[i].weight) {
				e.begin = edges[i].begin;
				e.end = edges[i].end;
				e.weight = edges[i].weight;

				edges[i].begin = edges[j].begin;
				edges[i].end = edges[j].end;
				edges[i].weight = edges[j].weight;

				edges[j].begin = e.begin;
				edges[j].end = e.end;
				edges[j].weight = e.weight;
			}
		}
	}

	for(i = 0; i < G.numVertexs; i++) {
		parent[i] = 0;	//初始化数组值为 0
	}
	for(i = 0; i < G.numEdges; i++) {	//循环每一条边
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if( n != m) {					//假如 n 与 m 不等，说明此边没有与现有生成树形成环路
			parent[n] = m;				//将此边的结尾顶点放入下标为起点的parent中
										//表示此顶点已经在生成树集合中
			printf("(%d,%d)-%d ",edges[i].begin,edges[i].end,edges[i].weight);
		}
	}
}

//查找连线顶点的尾部下标
int Find(int *parent, int f) {
	while( parent[f]>0 ) {
		f = parent[f];
	}
	return f;
}	

int main() {
	MGraph G;
	CreateMGraph(&G);
	DisplayMGraph(G);

	printf("\n---------------------\n");
	MiniSpanTree_Prim(G);
	printf("\n*********************\n");
	MiniSpanTree_Kruskal(G);

	return 0;
}