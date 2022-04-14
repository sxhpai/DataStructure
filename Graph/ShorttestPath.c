/***************** 最短路径 ******************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXVEX 100
#define INFINITY 65535
typedef char VertexType;	//顶点数据域类型
typedef int EdgeType;		//边上的权值类型
typedef int Patharc[MAXVEX];          //用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX];   //用于存储到各点最短路径的权值和
typedef int Pathmatrix[MAXVEX][MAXVEX]; //用于存储最短路径
typedef int ShortPathMatrix[MAXVEX][MAXVEX];    //用于存储带权长度

//邻接矩阵
typedef struct {
	VertexType vex[MAXVEX];			//顶点数组
	EdgeType arc[MAXVEX][MAXVEX];	//边数组，邻接矩阵的权重写道边数组中
	int numVertexs, numEdges;		//顶点数和边数
}MGraph;

//创建无向图的邻接矩阵
void CreateMGraph(MGraph* G) {
	int i,j,k,w;
	printf("请输入顶点和边的数目：\n");
	scanf_s("%d,%d", &G->numVertexs, &G->numEdges);
	getchar();

	printf("请输入顶点信息：\n");
	for (i = 0; i < G->numVertexs; i++) {
		scanf_s("%c", &G->vex[i]);
		getchar();
	}
	//初始化边表
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
	//读入边表信息
	for (k = 0; k < G->numEdges; k++) {
		printf("请输入(vi,vj)的序号i,j和权重:\n");
		scanf_s("%d,%d,%d", &i, &j, &w);
		getchar();
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}

/************** 迪杰斯特拉算法 ************/

//P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D) 
{
    int v,w,k,min;
    int final[MAXVEX];  //final[w] = 1表示求得顶点v0至vw的最短路径
    for (v = 0; v < G.numVertexs; v++) {     //初始化数据
        final[v] = 0;           //全部顶点初始化为未知最短路径
        (*D)[v] = G.arc[v0][v]; //将与v0点有连线的顶点加上权值
        (*P)[v] = 0;            //初始化路径数组P为0
    }
    (*D)[v0] = 0;       //v0至v0路径为0
    final[v0] = 1;      //v0至v0不需要求路径
    /*开始主循环，每次求得v0到某个v顶点的最短路径*/
    for (v = 1; v < G.numVertexs; v++) {
        min = INFINITY;         //当前所知离v0顶点的最近距离
        for (w = 0; w < G.numVertexs; w++) { //寻找离v0最近的顶点
            if(!final[w] && (*D)[w] < min) {
                k = w;
                min = (*D)[w];      //w顶点离v0顶点更近
            }
        }
        final[k] = 1;       //将目前找到的最近的顶点置为1
        for (w = 0; w < G.numVertexs; w++) { //修正当前最短路径及距离
            //如果经过v顶点的路径比现在这条路径的长度短的话
            if (!final[w] && (min+G.arc[k][w] < (*D)[w] ) ) {
                //说明找到了更短路径，修改D[w]和P[w]
                (*D)[w] = min + G.arc[k][w];    //修改当前的路径长度
                (*P)[w] = k;
            }
        }
    }
    //显示代码
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

/*********** 佛洛依德算法 **************/
//Floyd算法，求网图G中各顶点v到其余顶点w最短路径 P[v][w] 及带权长度 D[v][w]
void ShorttestPath_Floyd(MGraph G, Pathmatrix *P, ShortPathMatrix *D) 
{
    int v,w,k;
    for (v = 0; v < G.numVertexs; ++v) {     //初始化 D 与 P
        for ( w = 0; w < G.numVertexs; ++w) {
            (*D)[v][w] = G.arc[v][w];       //D[v][w]值即为对应点间的权值
            (*P)[v][w] = w;                 // 
        }
    }
    //主循环
    //k 代表的就是中转顶点的下标
    for (k = 0; k < G.numVertexs; ++k) {
        for (v = 0; v < G.numVertexs; ++v) {
            for (w = 0; w < G.numVertexs; ++w) {
                if ( (*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
                    //如果经过下标为k顶点路径比原两点间路径更短
                    //将当前两点间权值设为更小的一个
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    (*P)[v][w] = (*P)[v][k];        //路径设置经过下标为 k 的顶点
                }
            }
        }
    }
    //最短路径显示代码
    for (v =0; v < G.numVertexs; ++v) {
        for (w = v + 1; w < G.numVertexs; w++) {
            printf("v%d-v%d weight: %d ",v, w, (*D)[v][w]);
            k = (*P)[v][w];                //获得第一个路径顶点下标
            printf(" path: %d",v);      //打印源点
            while(k != w) {
                printf(" -> %d", k);    //打印路径顶点
                k = (*P)[k][w];            //获得下一个路径顶点下标
            }
            printf(" -> %d\n", w);      //打印终点
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