#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Boolean;        //Boolean�ǲ������ͣ���ֵ��TRUE��FALSE

typedef char VertexType;    //��������
typedef int EdgeType;       //���ϵ�Ȩֵ����
#define MAXVEX  100         //�����������
#define INFINITY    65535   //�� 65535 ��ʾ ��

Boolean visited[MAXVEX];    //���ʱ�־������

//�ڽӾ���
typedef struct 
{
    VertexType vexs[MAXVEX];        //��������
    EdgeType arc[MAXVEX][MAXVEX];   //������
    int numVertexs,numEdges;        //ͼ�е�ǰ�Ķ������ͱ���
}MGraph;

//�ڽӱ�

//�߱���
typedef struct EdgeNode{
    int adjvex;
    EdgeType weight;
    struct EdgeNode *next;
}EdgeNode;

//�������
typedef struct VertexNode{
    VertexType data;
    EdgeNode *firstedge;
}VertexNode,AdjList[MAXVEX];

//�ڽӱ�
typedef struct {
    AdjList adjlist;
    int numVertexs,numEdges;
}GraphAdjList;

//����ͼ�ڽӾ���洢�ṹ�Ĵ���
void CreateMGraph(MGraph *G) {
    int i,j,k,w;
    printf("������ͼ�Ķ������ͱ�����\n");
    scanf("%d,%d",&G->numVertexs,&G->numEdges);
    getchar();
    printf("�����붥����Ϣ:\n");
    //�������齨��
    for(i = 0; i < G->numVertexs; i++) {
        scanf("%c",&G->vexs[i]);
        getchar();
    }
    //�����齨��
    //��ʼ��������
    for(i = 0; i < G->numEdges; i++) {
        for(j = 0; j < G->numEdges; j++) {
            if(i == j){
                G->arc[i][j] = 0;
            }else{
                G->arc[i][j] = INFINITY;
            }
        }
    }
    //����numEdges���ߣ������ڽӾ���
    for(k = 0; k < G->numEdges; k++) {
        printf("�������(vi,vj)�����i,j ��Ȩֵ w:\n");
        scanf("%d,%d,%d",&i,&j,&w);
        getchar();
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];    //����ͼ���ԶԳ�
    }
}

//����ͼ�ڽӱ�洢�ṹ����
void CreateALGraph(GraphAdjList *G) { 
    int i,j,k,w;
    EdgeNode *e;
    printf("������ͼ�Ľ�����ͱ�����\n");
    scanf("%d,%d", &G->numVertexs, &G->numEdges);
    getchar();
    //�����
    printf("�����붥�����Ϣ:\n");
    for(i = 0; i < G->numVertexs; i++) {
        scanf("%c", &G->adjlist[i].data);
        getchar();
        G->adjlist[i].firstedge = NULL;
    }
    //�߱�
    for(k = 0; k < G->numEdges; k++) {
        printf("�������(vi,vj)�����i,j ��Ȩֵw:\n");
        scanf("%d,%d,%d", &i, &j, &w);

        e = (EdgeNode *)malloc(sizeof(EdgeNode*));  //����ռ䣬���ɱ߽��
        e->weight = w;
        e->adjvex = j;  //�ڽ����Ϊj
        e->next = G->adjlist[i].firstedge;
        G->adjlist[i].firstedge = e;

        e = (EdgeNode *)malloc(sizeof(EdgeNode*));  //����ռ䣬���ɱ߽��
        e->weight = w;
        e->adjvex = i;  //�ڽ����Ϊi
        e->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = e;
    }
} 

/********** �ڽӾ����������ȵݹ��㷨 ***************/
void DFS(MGraph G, int i) {
    int j;
    visited[i] = true;
    printf(" %c", G.vexs[i]);     //��ӡ�����㣬Ҳ������������
    for(j = 0; j < G.numVertexs; j++) {
        if(G.arc[i][j] == 1 && !visited[j]) {
            DFS(G,j);       //�Է��ʵ��ڽӽ��ݹ����
        }
    }
}
/********* �ڽӾ�����ȱ��� **********/
void DFSTraverse(MGraph G)
{
    int i;
    for(i = 0; i < G.numVertexs; i++) {
        visited[i] = false;     //��ʼ���ж���״̬����δ���ʹ�״̬
    }
    for(i = 0; i < G.numVertexs; i++) {
        if(!visited[i]) {       //δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
            DFS(G, i);
        }
    }
}
/********** �ڽӱ��������ȵݹ��㷨 ***************/
void DFS_AL(GraphAdjList GL, int i)         //n������e���ߵ�ͼ �ڽӱ��������ȵݹ��㷨ʱ�临�Ӷ�Ϊ��O(n+e)
{
   EdgeNode* temp;
   visited[i] = true;
   printf(" %c", GL.adjlist[i].data);       //��ӡ���㣬Ҳ������������
   temp = GL.adjlist[i].firstedge;
   while (temp)
   {
       if (!visited[temp->adjvex]) {
           DFS_AL(GL, temp->adjvex);  //��Ϊ���ʵ��ڽӶ���ݹ����
       }
       temp = temp->next;
   }
}

/*********** �ڽӱ����ȱ������� ***********/
void DFSTraverse_AL(GraphAdjList GL)
{
   int i;
   for (i = 0; i < GL.numVertexs; i++) {
       visited[i] = false;     //��ʼ�����ж���״̬����δ���ʹ�״̬
   }
   for (i = 0; i < GL.numVertexs; i++) {
       if (!visited[i])    //��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
           DFS_AL(GL, i);
   }
}

//��ӡ����ͼ���ڽӾ���
void DisplayMGraph(MGraph G) {
    int i,j;
    for(i = 0; i < G.numVertexs; i++) {
        for(j = 0; j < G.numVertexs; j++) {
            printf("%-10d",G.arc[i][j]);
        }
        printf("\n");
    }
}

//��ӡ����ͼ���ڽӱ�
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