
/*************** �ڽӾ�����ڽӱ� ******************/
/********** ������ȱ��� �� ������ȱ��� ***********/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char VertexType;	//��������������
typedef int EdgeType;		//���ϵ�Ȩֵ����
typedef int Boolen;
#define MAXVEX 100			//�����������
#define INFINITY 65535		//��65535��ʾ��

Boolen Visited[MAXVEX];

#define ERROR -1
#define OK 1
#define MAXSIZE 10 //���е����ռ�����

typedef int Status;
typedef int QElemType;

//���ṹ
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

//���е�����ṹ
typedef struct {
	QueuePtr front;
	QueuePtr rear;
	int count;
}LinkQueue;

//�ڽӾ���
typedef struct {
	VertexType vex[MAXVEX];			//��������
	EdgeType arc[MAXVEX][MAXVEX];	//�����飬�ڽӾ����Ȩ��д����������
	int numVertexs, numEdges;		//�������ͱ���
}MGraph;

//�߽��
typedef struct EdgeNode {
	int adjvex;		//�ڽӽ���Ķ�������
	EdgeType weight;		//�ڽӱ��Ȩ��д�ڱ߽����
	struct EdgeNode* next;	//��һ���ڽӽ��
}EdgeNode;

//����
typedef struct VertexNode{
	VertexType data;		//��������
	EdgeNode* firstedge;	//ָ���һ����
}VertexNode,AdjList[MAXVEX];

//�ڽӱ�
typedef struct {
	AdjList adjlist;		//���������
	int numVertexs, numEdges;
}ALGraph;


//��ʼ������ʽ����
Status InitLinkQueue(LinkQueue* Q) {
	//ͷ���
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if (!temp) {
		printf("�����ڴ�ʧ��");
		return ERROR;
	}
	temp->next = NULL;

	Q->front = temp;	//ͷָ��ָ��ͷ���
	Q->rear = temp;		//βָ��ָ��ͷ���
	Q->count = 0;

	return OK;
}

//����
Status EnQueue(LinkQueue* Q, QElemType e) {
	//�½ڵ�
	QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
	if (!temp) {
		printf("�����ڴ�ʧ��");
		return ERROR;
	}
	temp->data = e;
	temp->next = NULL;

	//β����
	Q->rear->next = temp;	//���½ڵ��β������
	Q->rear = temp;		//βָ��ָ���β���
	Q->count++;

	return OK;
}

//����
Status DeQueue(LinkQueue* Q, QElemType* e) {
	if (Q->front == Q->rear) {
		printf("����");
		return ERROR;
	}
	//����
	QueuePtr del = Q->front->next;
	*e = Q->front->next->data;
	Q->front->next = Q->front->next->next;
	//����һ�����������һ����㣬��ͷ�Ƕ�β����ɾ���󣬽�rearָ��ָ��ͷ��㡣��ʱΪ�ն��С�
	if (Q->rear == del) {
		Q->rear = Q->front;
	}

	free(del);	//�ͷſռ�

	Q->count--;

	return OK;
}

//��������ͼ���ڽӾ���
void CreateMGraph(MGraph* G) {
	int i,j,k;
	printf("�����붥��ͱߵ���Ŀ��\n");
	scanf_s("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();

	printf("�����붥����Ϣ��\n");
	for (i = 0; i < G->numVertexs; i++) {
		scanf_s("%c", &G->vex[i]);
		getchar();
	}
	//��ʼ���߱�
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
	//����߱���Ϣ
	for (k = 0; k < G->numEdges; k++) {
		printf("������(vi,vj)�����i,j��\n");
		scanf_s("%d,%d", &i, &j);
		getchar();
		G->arc[i][j] = 1;
		G->arc[j][i] = G->arc[i][j];
	}
}

//��������ͼ���ڽӱ�
void CreateALGraph(ALGraph* G) {
	int i, j, k;
	EdgeNode* e;
	printf("������ͼ�Ľ�����ͱ�����\n");
	scanf_s("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();
	//�����
	printf("�����붥�����Ϣ:\n");
	for (i = 0; i < G->numVertexs; i++) {
		scanf_s("%c", &G->adjlist[i].data);
		getchar();
		G->adjlist[i].firstedge = NULL;
	}
	//�߱�
	for (k = 0; k < G->numEdges; k++) {
		printf("�������(vi,vj)�����i,j:\n");
		scanf_s("%d,%d", &i, &j);

		e = (EdgeNode*)malloc(sizeof(EdgeNode));  //����ռ䣬���ɱ߽��
		e->weight = 1;		//ȨֵĬ�϶���1
		e->adjvex = j;  //�ڽ����Ϊj
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;

		e = (EdgeNode*)malloc(sizeof(EdgeNode));  //����ռ䣬���ɱ߽��
		e->weight = 1;
		e->adjvex = i;  //�ڽ����Ϊi
		e->next = G->adjlist[j].firstedge;
		G->adjlist[j].firstedge = e;
	}
}

/***************** ������ȱ����㷨 *****************/

//�ڽӾ���������ȵݹ��㷨
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
//�ڽӾ���������ȱ����㷨
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
//�ڽӱ�������ȵݹ��㷨
void DFS_AL(ALGraph GL, int i)         //n������e���ߵ�ͼ �ڽӱ��������ȵݹ��㷨ʱ�临�Ӷ�Ϊ��O(n+e)
{
    EdgeNode* temp;
    Visited[i] = true;
    printf(" %c", GL.adjlist[i].data);       //��ӡ���㣬Ҳ������������
    temp = GL.adjlist[i].firstedge;
    while (temp)
    {
        if (!Visited[temp->adjvex]) {
            DFS_AL(GL, temp->adjvex);  //��Ϊ���ʵ��ڽӶ���ݹ����
        }
        temp = temp->next;
    }
}

//�ڽӱ�������ȱ����㷨
void DFSTraverse_AL(ALGraph GL)
{
    int i;
    for (i = 0; i < GL.numVertexs; i++) {
        Visited[i] = false;     //��ʼ�����ж���״̬����δ���ʹ�״̬
    }
    for (i = 0; i < GL.numVertexs; i++) {
        if (!Visited[i])    //��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
            DFS_AL(GL, i);
    }
}

/***************** ������ȱ����㷨 ********************/

//�ڽӾ��������ȱ���
void BFSTraverse_M(MGraph G) {
	int i, j;
	LinkQueue Q;
	//��ʼ��
	for (i = 0; i < G.numVertexs; i++) {	
		Visited[i] = false;
	}
	InitLinkQueue(&Q);

	for (i = 0; i < G.numVertexs; i++) {	//����ÿһ�����
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

//�ڽӱ������ȱ���
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
            printf("%c", GL.adjlist[i].data);   //��ӡ���㣬Ҳ������������
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

//��ӡ����ͼ���ڽӾ���
void DisplayMGraph(MGraph G) {
	int i, j;
	for (i = 0; i < G.numVertexs; i++) {
		for (j = 0; j < G.numVertexs; j++) {
			printf("%-10d", G.arc[i][j]);
		}
		printf("\n");
	}
}

//��ӡ����ͼ���ڽӱ�
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