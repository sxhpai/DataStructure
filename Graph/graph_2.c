
/***************** 邻接多重表 *********************/

#include <stdio.h>
#include <stdlib.h>

//无向图的优化数据结构

typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100

/***** 邻接多重表 *****/

//边表结点结构
typedef struct EdgeNode {
	int ivex;				//ivex 和 jvex是与某条边依附的两个顶点在顶点表中的下标。
	int jvex;				
	struct EdgeNode* ilink; //指向依附顶点ivex的下一条边
	struct EdgeNode* jlink;	//指向依附顶点jvex的下一条边
}EdgeNode;

//顶点表结点结构
typedef struct VertexNode {
	VertexType data;		//顶点域，存储顶点信息
	EdgeNode* firstedge;		//指向一条边 顶点下标与ivex值相同

}VertexNode, AdjmList[MAXVEX];

//邻接多重表
typedef struct {
	AdjmList adjmlist;
	int numVertex, numEdge;
}GraphAdjmList;

//建立无向图的多重邻接表结构
void CreateGraphAdjmList(GraphAdjmList* G)
{
	int i,j,k;
	EdgeNode* e;
	printf("请输入结点数和边数:\n");
	scanf("%d,%d", &G->numVertex, &G->numEdge);
	getchar();
	//建立顶点表
	printf("请输入结点信息:\n");
	for (i = 0; i < G->numVertex; i++) {
		scanf("%c", &G->adjmlist[i].data);
		getchar();
		G->adjmlist[i].firstedge = NULL;
	}
	//建立边表
	for (k = 0; k < G->numEdge; k++) {
		printf("请输入(vi,vj)的i j的序号:\n");
		scanf("%d,%d", &i, &j);

		//申请新节点
		e = (EdgeNode*)malloc(sizeof(EdgeNode));

		//头插法
		e->ivex = i;
		e->ilink = G->adjmlist[i].firstedge;
		G->adjmlist[i].firstedge = e;

		e->jvex = j;
		e->jlink = G->adjmlist[j].firstedge;
		G->adjmlist[j].firstedge = e;
	}
}

//打印无向图的多重邻接表结构
void DisplayGraphAdjmList(GraphAdjmList G)
{
	int i;
	for (i = 0; i < G.numVertex; i++) {
		printf("%c->", G.adjmlist[i].data);
		EdgeNode* temp = G.adjmlist[i].firstedge;
		while (temp) {
			if (temp->ivex == i) {
				printf(" %c", G.adjmlist[temp->jvex].data);
				temp = temp->ilink;
			}
			else {
				printf(" %c", G.adjmlist[temp->ivex].data);
				temp = temp->jlink;
			}		
		}
		printf("\n");
	}
}

int main()
{
	GraphAdjmList G;

	CreateGraphAdjmList(&G);
	DisplayGraphAdjmList(G);

	return 0;
}
