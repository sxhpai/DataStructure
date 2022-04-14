/***************** ���·�� ******************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXVEX 100
#define INFINITY 65535
typedef char VertexType;	//��������������
typedef int EdgeType;		//���ϵ�Ȩֵ����
typedef int Patharc[MAXVEX];          //���ڴ洢���·���±������
typedef int ShortPathTable[MAXVEX];   //���ڴ洢���������·����Ȩֵ��
typedef int Pathmatrix[MAXVEX][MAXVEX]; //���ڴ洢���·��
typedef int ShortPathMatrix[MAXVEX][MAXVEX];    //���ڴ洢��Ȩ����

//�ڽӾ���
typedef struct {
	VertexType vex[MAXVEX];			//��������
	EdgeType arc[MAXVEX][MAXVEX];	//�����飬�ڽӾ����Ȩ��д����������
	int numVertexs, numEdges;		//�������ͱ���
}MGraph;

//��������ͼ���ڽӾ���
void CreateMGraph(MGraph* G) {
	int i,j,k,w;
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
		printf("������(vi,vj)�����i,j��Ȩ��:\n");
		scanf_s("%d,%d,%d", &i, &j, &w);
		getchar();
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}

/************** �Ͻ�˹�����㷨 ************/

//P[v]��ֵΪǰ�������±꣬D[v]��ʾv0��v�����·�����Ⱥ�
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D) 
{
    int v,w,k,min;
    int final[MAXVEX];  //final[w] = 1��ʾ��ö���v0��vw�����·��
    for (v = 0; v < G.numVertexs; v++) {     //��ʼ������
        final[v] = 0;           //ȫ�������ʼ��Ϊδ֪���·��
        (*D)[v] = G.arc[v0][v]; //����v0�������ߵĶ������Ȩֵ
        (*P)[v] = 0;            //��ʼ��·������PΪ0
    }
    (*D)[v0] = 0;       //v0��v0·��Ϊ0
    final[v0] = 1;      //v0��v0����Ҫ��·��
    /*��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��*/
    for (v = 1; v < G.numVertexs; v++) {
        min = INFINITY;         //��ǰ��֪��v0������������
        for (w = 0; w < G.numVertexs; w++) { //Ѱ����v0����Ķ���
            if(!final[w] && (*D)[w] < min) {
                k = w;
                min = (*D)[w];      //w������v0�������
            }
        }
        final[k] = 1;       //��Ŀǰ�ҵ�������Ķ�����Ϊ1
        for (w = 0; w < G.numVertexs; w++) { //������ǰ���·��������
            //�������v�����·������������·���ĳ��ȶ̵Ļ�
            if (!final[w] && (min+G.arc[k][w] < (*D)[w] ) ) {
                //˵���ҵ��˸���·�����޸�D[w]��P[w]
                (*D)[w] = min + G.arc[k][w];    //�޸ĵ�ǰ��·������
                (*P)[w] = k;
            }
        }
    }
    //��ʾ����
    printf("\n");
    for (w = 0; w < G.numVertexs; w++) {

        printf("v%d-v%d weight: %d ",v0,w,(*D)[w]);
        printf(" path: %d", w);
        k = (*P)[w];
        while(k != v0) {
            printf(" <- %d",k);
            k = (*P)[k];
        }
        printf(" <- %d",v0);
        printf("\n");
    }
    printf("\n");
}

/*********** ���������㷨 **************/
//Floyd�㷨������ͼG�и�����v�����ඥ��w���·�� P[v][w] ����Ȩ���� D[v][w]
void ShorttestPath_Floyd(MGraph G, Pathmatrix *P, ShortPathMatrix *D) 
{
    int v,w,k;
    for (v = 0; v < G.numVertexs; ++v) {     //��ʼ�� D �� P
        for ( w = 0; w < G.numVertexs; ++w) {
            (*D)[v][w] = G.arc[v][w];       //D[v][w]ֵ��Ϊ��Ӧ����Ȩֵ
            (*P)[v][w] = w;                 // 
        }
    }
    //��ѭ��
    //k ����ľ�����ת������±�
    for (k = 0; k < G.numVertexs; ++k) {
        for (v = 0; v < G.numVertexs; ++v) {
            for (w = 0; w < G.numVertexs; ++w) {
                if ( (*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
                    //��������±�Ϊk����·����ԭ�����·������
                    //����ǰ�����Ȩֵ��Ϊ��С��һ��
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    (*P)[v][w] = (*P)[v][k];        //·�����þ����±�Ϊ k �Ķ���
                }
            }
        }
    }
    //���·����ʾ����
    for (v =0; v < G.numVertexs; ++v) {
        for (w = v + 1; w < G.numVertexs; w++) {
            printf("v%d-v%d weight: %d ",v, w, (*D)[v][w]);
            k = (*P)[v][w];                //��õ�һ��·�������±�
            printf(" path: %d",v);      //��ӡԴ��
            while(k != w) {
                printf(" -> %d", k);    //��ӡ·������
                k = (*P)[k][w];            //�����һ��·�������±�
            }
            printf(" -> %d\n", w);      //��ӡ�յ�
        }
        printf("\n");
    }
}



int main() {

    MGraph G;
    Patharc P1;
    ShortPathTable D1;
    Pathmatrix P2;
    ShortPathMatrix D2;

    CreateMGraph(&G);

    printf("\ndijkstra:\n");
    ShortestPath_Dijkstra(G,0,&P1,&D1);
    printf("\nflody:\n");
    ShorttestPath_Floyd(G,&P2,&D2);

    return 0;
}