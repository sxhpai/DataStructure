/*************** ʮ������ *****************/

#include <stdio.h>
#include <stdlib.h>

//�������ݽṹ���������ڽӱ�����ڽӱ�ʮ���ʺ�����ͼ

typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100

/***** ʮ������ *****/

//�߱���ṹ
typedef struct EdgeNode {
	int headvex;				//ָ������ڶ������±꣬��
	int tailvex;				//ָ���յ��ڶ������±꣬��
	EdgeType weight;			//���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
	struct EdgeNode* headlink;	//ָ���յ���ͬ����һ���ߣ���
	struct EdgeNode* taillink;	//ָ�������ͬ����һ���ߣ���
}EdgeNode;

//�������ṹ
typedef struct VertexNode {
	VertexType data;		//�����򣬴洢������Ϣ
	EdgeNode* firstin;		//��ʾ��߱�ָ�룬ָ��ö������߱�ĵ�һ����㣬��
	EdgeNode* firstout;		//��ʾ���߱�ָ�룬ָ��ö���ĳ��߱�ĵ�һ����㣬��
}VertexNode, CroList[MAXVEX];

//ʮ������
typedef struct {
	CroList croList;
	int numVertexs, numEdges;	//ͼ�е�ǰ�������ͱ���
}GraphCroList;

void CreateGraphCroList(GraphCroList* G)
{
	int i,j,k;
	EdgeNode* e;
	printf("�����붥�����ͱ�����\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();
	printf("�����붥����Ϣ��\n");
	//���붥����Ϣ�����������
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c", &G->croList[i].data);
		getchar();
		G->croList[i].firstin = NULL;
		G->croList[i].firstout = NULL;
	}
	//�����߱�
	for (k = 0; k < G->numEdges; k++) {
		printf("������߱��<vi,vj>�����i,j��\n");
		scanf("%d,%d", &i, &j);	//iΪ�ߵ�ͷ��jΪ�ߵ�β
		getchar();

		//�����½ڵ�
		e = (EdgeNode*)malloc(sizeof(EdgeNode));

		//���룬ͷ�巨
		e->headvex = j;	//���յ�
		e->tailvex = i;	//�����
		e->taillink = G->croList[i].firstout;	//��
		G->croList[i].firstout = e;
		e->headlink = G->croList[j].firstin;	//��
		G->croList[j].firstin = e;

	}
}

void DisplayGraphCroList(GraphCroList G)
{
	int i;
	printf("\n---------------\n");
	//��
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
	//��
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