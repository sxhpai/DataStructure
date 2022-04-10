
/***************** �ڽӶ��ر� *********************/

#include <stdio.h>
#include <stdlib.h>

//����ͼ���Ż����ݽṹ

typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100

/***** �ڽӶ��ر� *****/

//�߱���ṹ
typedef struct EdgeNode {
	int ivex;				//ivex �� jvex����ĳ�������������������ڶ�����е��±ꡣ
	int jvex;				
	struct EdgeNode* ilink; //ָ����������ivex����һ����
	struct EdgeNode* jlink;	//ָ����������jvex����һ����
}EdgeNode;

//�������ṹ
typedef struct VertexNode {
	VertexType data;		//�����򣬴洢������Ϣ
	EdgeNode* firstedge;		//ָ��һ���� �����±���ivexֵ��ͬ

}VertexNode, AdjmList[MAXVEX];

//�ڽӶ��ر�
typedef struct {
	AdjmList adjmlist;
	int numVertex, numEdge;
}GraphAdjmList;

//�����ڽӱ�Ľ���
void CreateGraphAdjmList(GraphAdjmList* G)
{
	int i,j,k;
	EdgeNode* e;
	printf("�����������ͱ���:\n");
	scanf("%d,%d", &G->numVertex, &G->numEdge);
	getchar();
	//���������
	printf("����������Ϣ:\n");
	for (i = 0; i < G->numVertex; i++) {
		scanf("%c", &G->adjmlist[i].data);
		getchar();
		G->adjmlist[i].firstedge = NULL;
	}
	//�����߱�
	for (k = 0; k < G->numEdge; k++) {
		printf("������(vi,vj)��i j�����:\n");
		scanf("%d,%d", &i, &j);

		//�����½ڵ�
		e = (EdgeNode*)malloc(sizeof(EdgeNode));

		//ͷ�巨
		e->ivex = i;
		e->ilink = G->adjmlist[i].firstedge;
		G->adjmlist[i].firstedge = e;

		e->jvex = j;
		e->jlink = G->adjmlist[j].firstedge;
		G->adjmlist[j].firstedge = e;
	}
}

//��ӡ
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