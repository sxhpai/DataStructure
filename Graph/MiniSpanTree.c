#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char VertexType;	//��������������
typedef int EdgeType;		//���ϵ�Ȩֵ����
#define MAXVEX 100			//�����������
#define MAXEDGE 100
#define INFINITY 65535		//��65535��ʾ��

//�ڽӾ���
typedef struct {
	VertexType vex[MAXVEX];			//��������
	EdgeType arc[MAXVEX][MAXVEX];	//�����飬�ڽӾ����Ȩ��д����������
	int numVertexs, numEdges;		//�������ͱ���
}MGraph;

//�߼����� Edge �ṹ�Ķ���
typedef struct {
	int begin;
	int end;
	int weight;
}Edge;

//����ķ�㷨������С������
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		//������ض����±�
	int lowcost[MAXVEX];	//������ض����ߵ�Ȩֵ
	lowcost[0] = 0;		//��ʼ����һ��ȨֵΪ0����v0����������
						/* lowcost ��ֵΪ0����������Ǵ��±�Ķ����Ѿ�����������*/
	adjvex[0] = 0;		//��ʼ����һ�������±�Ϊ0
	for(i = 1; i < G.numVertexs; i++) {	//ѭ�������±�Ϊ0���ȫ������
		lowcost[i] = G.arc[0][i];		//��v0������֮�бߵ�Ȩֵ��������
		adjvex[i] = 0;					//��ʼ����Ϊv0���±�,ÿ��Ԫ�ض���v0���±�
	}
	//
	for(i = 1; i < G.numVertexs; i++) {
		min = INFINITY;		//��ʼ����СȨֵΪ��
		j = 1; k = 0;
		while(j < G.numVertexs) {	//ѭ��ȫ������,�ҵ���v0��������СȨֵ�ߡ�
			if(lowcost[j] != 0 && lowcost[j] < min) {
				//���Ȩֵ��Ϊ0��ȨֵС��min
				min = lowcost[j];		//�򽫵�ǰȨֵ��Ϊ��Сֵ
				k = j;					//����ǰ��Сֵ���±����k
			}
			j++;
		}
		printf(" (%d,%d)",adjvex[k],k);	//��ӡ��ǰ�������Ȩֵ��С��
		lowcost[k] = 0;	//����ǰ�����Ȩֵ��Ϊ0����ʾ�˶����Ѿ��������
		for(j = 1; j < G.numVertexs; j++) {	//ѭ�����ж���
			if(lowcost[j] != 0 && G.arc[k][j] < lowcost[j]) {
				//���±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ
				lowcost[j] = G.arc[k][j];		//����СȨֵ����lowcost
				adjvex[j] = k;				//���±�Ϊk�Ķ������adjvex
			}
		}
	}
}

//��³˹�����㷨������С������
void MiniSpanTree_Kruskal(MGraph G)		//������С������
{
	int i, j, k, p, n, m;
	Edge edges[MAXEDGE];	//����߼�����
	int parent[MAXVEX];	//����һ���������жϱ�����Ƿ��γɻ�·

	//���ڽӾ���Gת��Ϊ�߼�����edges����Ȩ��С��������
	k = 0;
	Edge e;
	for(i = 0; i < G.numVertexs; i++) {
		for(j = 0; j < G.numVertexs; j++) {
			if(G.arc[i][j] > 0 && G.arc[i][j] < INFINITY) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	for(i = 0; i < k; i++) {
		for(j = i+1; j < k; j++) {
			if(edges[j].weight < edges[i].weight) {
				e.begin = edges[i].begin;
				e.end = edges[i].end;
				e.weight = edges[i].weight;

				edges[i].begin = edges[j].begin;
				edges[i].end = edges[j].end;
				edges[i].weight = edges[j].weight;

				edges[j].begin = e.begin;
				edges[j].end = e.end;
				edges[j].weight = e.weight;
			}
		}
	}

	for(i = 0; i < G.numVertexs; i++) {
		parent[i] = 0;	//��ʼ������ֵΪ 0
	}
	for(i = 0; i < G.numEdges; i++) {	//ѭ��ÿһ����
		n = Find(parent,edges[i].begin);
		m = Find(parent,edges[i].end);
		if( n != m) {
			parent[n] = m;
			printf("(%d,%d) %d",edges[i].begin,edges[i].end,edges[i].weight);
		}
	}

}

//�������߶����β���±�
int Find(int *parent, int f) {
	while( parent[f]>0 ) {
		f = parent[f];
	}
	return f;
}	
