/****************** �ؼ�·�� *******************/

#include <stdio.h>
#include <stdlib.h>

int *etv;
int *ltv = NULL;     //�¼����緢��ʱ�����ٷ���ʱ������
int *stack2;        //���ڴ洢�������е�ջ
int top2;           //����stakc2��ָ��

//˳��ջԤ����
#define ERROR -1
#define OK 0
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
	int i, j, k, w;
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
		printf("�����(vi,vj)�ϵĶ������ ��Ȩ�أ�\n");
		scanf("%d,%d,%d", &i, &j, &w);		//�����(vi,vj)�ϵĶ������
		getchar();

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//���ɱ߱���
		//ͷ�巨
        e->weight = w;  //Ȩ��
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

//�����������ڹؼ�·������
Status TopologicalSort(GraphAdjList GL) {
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;        //����ջָ���±�
    int count = 0;      //����ͳ���������ĸ���
    int *stack;         /* ��ջ�洢���Ϊ0�Ķ��� */
                        //���γ�ջ������У�����������������
    stack = (int *)malloc(GL.numVertexs * sizeof(int) );    //˳��ջ����ʵ�������飬�и�topָ��ָ��ջ��
    for ( i = 0; i < GL.numVertexs; i++) {
        if(GL.adjList[i].in == 0) {
            stack[++top] = i;       //����Ϊ0�Ķ�����ջ
        } 
    }
    top2 = 0;       //��ʼ��Ϊ0
    etv = (int *)malloc(GL.numVertexs * sizeof(int));       //�¼����緢��ʱ��
    for (i = 0; i < GL.numVertexs; i++) {
        etv[i] = 0; //��ʼ��Ϊ0
    }
    stack2 = (int *)malloc(GL.numVertexs * sizeof(int));    //��ʼ��    
    while(top != 0) {
        gettop = stack[top--];  //��ջ
        printf("%c -> ", GL.adjList[gettop].data);  //��ӡ�˶���
        count++;
        stack2[++top2] = gettop;    //�������Ķ������ѹ���������е�ջ
        for (e = GL.adjList[gettop].firstedge; e; e = e->next) {
            /* �Զ��㻡����� */
            k = e->adjvex;  //�����һ��������±�
            GL.adjList[k].in--; //��k�Ŷ����ڽӵ����ȼ� 1
            if (!GL.adjList[k].in) {
                stack[++top] = k;   //��Ϊ 0 ����ջ���Ա����´�ѭ�����
            }
            if ((etv[gettop] + e->weight > etv[k]))     //�������ʱ�����緢��ʱ�䣨Ҳ����·�������ֵ��
                etv[k] = etv[gettop] + e->weight;
        }
    }

    if (count < GL.numVertexs)  //���countС�ڶ�������˵�����ڻ�
        return ERROR;
    else
        return OK;
}

//��ؼ�·����GLΪ�����������GL�ĸ���ؼ��
void CriticalPath(GraphAdjList GL) {
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte;           //��������緢��ʱ�����ٷ���ʱ�����
    ltv = (int *)malloc(GL.numVertexs * sizeof(int));   //�¼�������ʱ��
    TopologicalSort(GL);    //���������У��������� etv �� stack2 ��ֵ
    // ltv = (int *)malloc(GL.numVertexs * sizeof(int));   //�¼�������ʱ��
    for( i = 0; i < GL.numVertexs; i++) {
        ltv[i] = etv[GL.numVertexs - 1];        //��ʼ��ltv
    }
    while(top2 != 0) {
        gettop = stack2[top2--];        //���������г�ջ������ȳ�
        for(e = GL.adjList[gettop].firstedge; e; e = e->next) {
            //��������¼�����ٷ���ʱ��ltvֵ
            k = e->adjvex;
            if(ltv[k] - e->weight < ltv[gettop]) {  //��������¼�������ʱ��
                ltv[gettop]  = ltv[k] - e->weight;
            }
        }
    }
    printf("\n")
    for(j = 0; j < GL.numVertexs; j++) {        //��ete,lte�͹ؼ��
        for(e = GL.adjList[j].firstedge; e; e = e->next) {
            k = e->adjvex;
            ete = etv[j];               //����緢��ʱ��
            lte = ltv[k] - e->weight;   //���ٷ���ʱ��
            if(ete == lte) {
                printf("<v%c,v%c> legnth: %d , ",GL.adjList[j].data, GL.adjList[k].data, e->weight);
            }
        }
    }
}

int main()
{
    GraphAdjList GL;

    CreateALGraphDir(&GL);
    DisplayALGraph(GL);

    printf("\n");
    CriticalPath(GL);

    return 0;
}