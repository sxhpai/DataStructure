
/************** ������ȱ��� **************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Boolean;        //Boolean�ǲ������ͣ���ֵ��TRUE��FALSE

typedef char VertexType;    //��������
typedef int EdgeType;       //���ϵ�Ȩֵ����
#define MAXVEX  100         //�����������
#define INFINITY    65535   //�� 65535 ��ʾ ��

Boolean visited[MAXVEX];    //���ʱ�־������

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
typedef struct
{
    VertexType vexs[MAXVEX];        //��������
    EdgeType arc[MAXVEX][MAXVEX];   //������
    int numVertexs, numEdges;        //ͼ�е�ǰ�Ķ������ͱ���
}MGraph;

//�߱���
typedef struct EdgeNode {
    int adjvex;
    EdgeType weight;
    struct EdgeNode* next;
}EdgeNode;

//�������
typedef struct VertexNode {
    VertexType data;
    EdgeNode* firstedge;
}VertexNode, AdjList[MAXVEX];

//�ڽӱ�
typedef struct {
    AdjList adjlist;
    int numVertexs, numEdges;
}GraphAdjList;



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

//����ͼ�ڽӾ���洢�ṹ�Ĵ���
void CreateMGraph(MGraph* G) {
    int i, j, k, w;
    printf("������ͼ�Ķ������ͱ�����\n");
    scanf("%d,%d", &G->numVertexs, &G->numEdges);
    getchar();
    printf("�����붥����Ϣ:\n");
    //�������齨��
    for (i = 0; i < G->numVertexs; i++) {
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    //�����齨��
    //��ʼ��������
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
    //����numEdges���ߣ������ڽӾ���
    for (k = 0; k < G->numEdges; k++) {
        printf("�������(vi,vj)�����i,j ��Ȩֵ w:\n");
        scanf("%d,%d,%d", &i, &j, &w);
        getchar();
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];    //����ͼ���ԶԳ�
    }
}

//����ͼ�ڽӱ�洢�ṹ����
void CreateALGraph(GraphAdjList* G) {
    int i, j, k, w;
    EdgeNode* e;
    printf("������ͼ�Ľ�����ͱ�����\n");
    scanf("%d,%d", &G->numVertexs, &G->numEdges);
    getchar();
    //�����
    printf("�����붥�����Ϣ:\n");
    for (i = 0; i < G->numVertexs; i++) {
        scanf("%c", &G->adjlist[i].data);
        getchar();
        G->adjlist[i].firstedge = NULL;
    }
    //�߱�
    for (k = 0; k < G->numEdges; k++) {
        printf("�������(vi,vj)�����i,j ��Ȩֵw:\n");
        scanf("%d,%d,%d", &i, &j, &w);

        e = (EdgeNode*)malloc(sizeof(EdgeNode));  //����ռ䣬���ɱ߽��
        e->weight = w;
        e->adjvex = j;  //�ڽ����Ϊj
        e->next = G->adjlist[i].firstedge;
        G->adjlist[i].firstedge = e;

        e = (EdgeNode*)malloc(sizeof(EdgeNode));  //����ռ䣬���ɱ߽��
        e->weight = w;
        e->adjvex = i;  //�ڽ����Ϊi
        e->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = e;
    }
}

/*********�ڽӾ���Ĺ�ȱ����㷨*********/
void BFSTraverse(MGraph G)
{
    int i, j;
    LinkQueue Q;
    for (i = 0; i < G.numVertexs; i++) {    
        visited[i] = false; //�����н���ʼ��Ϊδ����״̬
    }
    InitLinkQueue(&Q);      //��ʼ��һ�����õĶ���

    for (i = 0; i < G.numVertexs; i++) {
        if (!visited[i])        //����δ���ʹ��ʹ���
        {
            visited[i] = true;          //���õ�ǰ�����ʹ�
            printf(" %c", G.vexs[i]);   //��ӡ���㣬Ҳ������������
            EnQueue(&Q, i);             //���˶��������
            while (Q.count) {
                DeQueue(&Q, &i);        //������Ԫ�س����У���ֵ��i
                for (j = 0; j < G.numVertexs; j++) {
                    //�ж������������뵱ǰ������ڱ���δ���ʹ�
                    if (G.arc[i][j] == 1 && !visited[j]) {
                        visited[j] = true;      //���ҵ��Ĵ˶�����Ϊ�ѷ���
                        printf("%c", G.vexs[j]);    //��ӡ����
                        EnQueue(&Q, j);             //���ҵ��Ķ��������
                    }
                }
            }
        }
    }
}

/***************** �ڽӱ�Ĺ�ȱ����㷨 *******************/
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
            printf("%c", GL.adjlist[i].data);   //��ӡ���㣬Ҳ������������
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

    //�ڽӾ���
    //MGraph G;

    //CreateMGraph(&G);
    //DisplayMGraph(G);
    //BFSTraverse(G);

    //�ڽӱ�
    GraphAdjList GL;

    CreateALGraph(&GL);
    DisplayALGraph(GL);
    BFSTraverse_AL(GL);

    return 0;
}