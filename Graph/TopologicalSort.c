/***************** �������� ********************/

#include <stdio.h>
#include <stdlib.h>

//˳��ջԤ����
#define ERROR -1
#define OK 1
typedef int Status;

//�ڽӱ�Ԥ����
#define MAXVEX 100			//��󶥵���
#define INFINITY 65535		//��65535�������
typedef char VertexType;	//��������
typedef int EdgeType;		//���ϵ�Ȩֵ����

//�߱���ṹ
typedef struct EdgeNode {	
	int adjvex;				//�ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeType weight;		//���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
	struct EdgeNode* next;
}EdgeNode;

//�������ṹ
typedef struct VertexNode {
    int in;             //�����Ϣ
	VertexType data;		//�����򣬴洢������Ϣ
	EdgeNode* firstedge;	//�߱�ͷָ��
}VertexNode,AdjList[MAXVEX];

//�ڽӱ�
typedef struct {
	AdjList adjList;
	int numVertexs, numEdges;	//ͼ�е�ǰ�������ͱ���
}GraphAdjList;

//��������ͼ���ڽӱ�ṹ
void CreateALGraphDir(GraphAdjList* G)
{
	int i, j, k;
	EdgeNode* e;
	printf("�����붥�����ͱ���:\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);	//���붥�����ͱ���
	getchar();
	printf("�����붥����Ϣ �������Ϣ:\n");
	//���붥����Ϣ���������
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c,%d", &(G->adjList[i].data),&(G->adjList[i].in));	//���붥����Ϣ�������Ϣ
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

//��ӡ�ڽӱ�
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

//����������GL�޻�·������������������в�����OK�����л�·����ERROR
Status TopologicalSort(GraphAdjList GL) {
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;        //����ջָ���±�
    int count = 0;      //����ͳ���������ĸ���
    int *stack;         //��ջ�洢���Ϊ0�Ķ���
    stack = (int *)malloc(GL.numVertexs * sizeof(int) );    //˳��ջ����ʵ�������飬�и�topָ��ָ��ջ��
    for ( i = 0; i < GL.numVertexs; i++) {
        if(GL.adjList[i].in == 0) {
            stack[++top] = i;       //����Ϊ0�Ķ�����ջ
        } 
    }

    while(top != 0) {
        gettop = stack[top--];  //��ջ
        printf("%c -> ", GL.adjList[gettop].data);  //��ӡ�˶���
        count++;
        for (e = GL.adjList[gettop].firstedge; e; e = e->next) {
            /* �Զ��㻡����� */
            k = e->adjvex;  //�����һ��������±�
            GL.adjList[k].in--; //��k�Ŷ����ڽӵ����ȼ� 1
            if (!GL.adjList[k].in) {
                stack[++top] = k;   //��Ϊ 0 ����ջ���Ա����´�ѭ�����
            }
        }
    }

    if (count < GL.numVertexs)  //���countС�ڶ�������˵�����ڻ�
        return ERROR;
    else
        return OK;
}

int main() {

    GraphAdjList G;

    CreateALGraphDir(&G);
    DisplayALGraph(G);

    TopologicalSort(G);

    return 0;
}