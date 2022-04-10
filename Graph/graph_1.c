/*************** 十字链表 *****************/

#include <stdio.h>
#include <stdlib.h>

//该种数据结构，整合了邻接表和逆邻接表，十分适合有向图

typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100

/***** 十字链表 *****/

//边表结点结构
typedef struct EdgeNode {
	int headvex;				//指向弧起点在顶点表的下标，入
	int tailvex;				//指向弧终点在顶点表的下标，出
	EdgeType weight;			//用于存储权值，对于非网图可以不需要
	struct EdgeNode* headlink;	//指向终点相同的下一条边，入
	struct EdgeNode* taillink;	//指向起点相同的下一条边，出
}EdgeNode;

//顶点表结点结构
typedef struct VertexNode {
	VertexType data;		//顶点域，存储顶点信息
	EdgeNode* firstin;		//表示入边表指针，指向该顶点的入边表的第一个结点，入
	EdgeNode* firstout;		//表示出边表指针，指向该顶点的出边表的第一个结点，出
}VertexNode, CroList[MAXVEX];

//十字链表
typedef struct {
	CroList croList;
	int numVertexs, numEdges;	//图中当前顶点数和边数
}GraphCroList;

void CreateGraphCroList(GraphCroList* G)
{
	int i,j,k;
	EdgeNode* e;
	printf("请输入顶点数和边数：\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();
	printf("请输入顶点信息：\n");
	//读入顶点信息，建立顶点表
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c", &G->croList[i].data);
		getchar();
		G->croList[i].firstin = NULL;
		G->croList[i].firstout = NULL;
	}
	//建立边表
	for (k = 0; k < G->numEdges; k++) {
		printf("请输入边表的<vi,vj>的序号i,j：\n");
		scanf("%d,%d", &i, &j);	//i为边的头，j为边的尾
		getchar();

		//申请新节点
		e = (EdgeNode*)malloc(sizeof(EdgeNode));

		//插入，头插法
		e->headvex = j;	//弧终点
		e->tailvex = i;	//弧起点
		e->taillink = G->croList[i].firstout;	//出
		G->croList[i].firstout = e;
		e->headlink = G->croList[j].firstin;	//入
		G->croList[j].firstin = e;

	}
}

void DisplayGraphCroList(GraphCroList G)
{
	int i;
	printf("\n---------------\n");
	//出
	for (i = 0; i < G.numVertexs; i++) {
		printf("%d - %c ->", i, G.croList[i].data);
		EdgeNode* temp = G.croList[i].firstout;
		while (temp) {
			printf(" %d-%d", temp->tailvex,temp->headvex);
			temp = temp->taillink;
		}
		printf("\n");
	}
	printf("\n---------------\n");
	//入
	for (i = 0; i < G.numVertexs; i++) {
		printf("%d - %c ->", i, G.croList[i].data);
		EdgeNode* temp = G.croList[i].firstin;
		while (temp) {
			printf(" %d-%d", temp->tailvex, temp->headvex);
			temp = temp->headlink;
		}
		printf("\n");
	}
}

int main() {
    
	GraphCroList G;

	CreateGraphCroList(&G);
	DisplayGraphCroList(G);

	return 0;
}