
/********************* ͼ�Ĵ洢�ṹ ***********************/
/******************* �ڽӾ�����ڽӱ� *********************/

#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;	//��������
typedef int EdgeType;		//���ϵ�Ȩֵ����
#define MAXVEX 100			//��󶥵���
#define INFINITY 65535		//��65535�������

/* �ڽӾ��� */
typedef struct
{
	VertexType vexs[MAXVEX];			//�����
	EdgeType arc[MAXVEX][MAXVEX];		//�ڽӾ��󣬱߱�
	int numVertexes, numEdges;			//ͼ�е�ǰ�Ķ������ͱ���
}MGraph;

/* �ڽӱ� */

//�߱���ṹ
typedef struct EdgeNode {	
	int adjvex;				//�ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeType weight;		//���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
	struct EdgeNode* next;
}EdgeNode;

//�������ṹ
typedef struct VertexNode {
	VertexType data;		//�����򣬴洢������Ϣ
	EdgeNode* firstedge;	//�߱�ͷָ��
}VertexNode,AdjList[MAXVEX];

//�ڽӱ�
typedef struct {
	AdjList adjList;
	int numVertexs, numEdges;	//ͼ�е�ǰ�������ͱ���
}GraphAdjList;

//������������ͼ���ڽӾ����ʾ
void CreateMGraph(MGraph* G)
{
	int i, j, k, w;
	printf("���붥�����ͱ���:\n");
	scanf("%d %d", &G->numVertexes, &G->numEdges);	//���붥�����ͱ���
	getchar();
	printf("%d,%d", G->numVertexes, G->numEdges);
	printf("�����붥�㣺\n");
	//������ʼ��
	for (i = 0; i < G->numVertexes; i++) {
		scanf("%c", & (G->vexs[i]));
		getchar();
	}
	
	//�ڽӱ��ʼ��
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
	//����numEdges���ߣ������ڽӾ���
	for (k = 0; k < G->numEdges; k++) {
		printf("����ߣ�vi,vj���ϵ��±�i���±�j��Ȩ w:\n");
		scanf("%d,%d,%d", &i, &j, &w);	//����ߣ�vi,vj���ϵ�Ȩw
		getchar();
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];		//��Ϊ������ͼ������Գơ�

	}
}

//��������ͼ���ڽӱ�ṹ
void CreateALGraph(GraphAdjList* G) 
{
	int i, j, k;
	EdgeNode* e;
	printf("�����붥�����ͱ���:\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);	//���붥�����ͱ���
	getchar();
	printf("�����붥����Ϣ��\n");
	//���붥����Ϣ���������
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c", & (G->adjList[i].data));	//���붥����Ϣ	
		getchar();
		G->adjList[i].firstedge = NULL;	//���߱���Ϊ�ձ�
	}

	//�����߱�
	for (k = 0; k < G->numEdges; k++) {
		printf("�����(vi,vj)�ϵĶ�����ţ�\n");
		scanf("%d,%d", &i, &j);		//�����(vi,vj)�ϵĶ������
		getchar();

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//���ɱ߱���
		//����
		e->adjvex = j;	//�ڽ����	
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//���ɱ߱���
		//����
		e->adjvex = i;	//�ڽ����
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

//��������ͼ���ڽӱ�ṹ
void CreateALGraphDir(GraphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("�����붥�����ͱ���:\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);	//���붥�����ͱ���
	getchar();
	printf("�����붥����Ϣ��\n");
	//���붥����Ϣ���������
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c", &(G->adjList[i].data));	//���붥����Ϣ	
		getchar();
		G->adjList[i].firstedge = NULL;	//���߱���Ϊ�ձ�
	}

	//�����߱�
	for (k = 0; k < G->numEdges; k++) {
		printf("�����(vi,vj)�ϵĶ�����ţ�\n");
		scanf("%d,%d", &i, &j);		//�����(vi,vj)�ϵĶ������
		getchar();

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//���ɱ߱���
		//ͷ�巨
		e->adjvex = j;	//�ڽ����	
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
    //����ͼ�ڽӱ���
    CreateALGraph(&G);
	DisplayALGraph(G);

    //����ͼ�ڽӱ���
	// CreateALGraphDir(&G);
	// DisplayALGraph(G);

	return 0;
}