/****************** 关键路径 *******************/

#include <stdio.h>
#include <stdlib.h>

int *etv;
int *ltv = NULL;     //事件最早发生时间和最迟发生时间数组
int *stack2;        //用于存储拓扑序列的栈
int top2;           //用于stakc2的指针

//顺序栈预定义
#define ERROR -1
#define OK 0
typedef int Status;

//邻接表预定义
#define MAXVEX 100			//最大顶点数
#define INFINITY 65535		//用65535来代表∞
typedef char VertexType;	//顶点类型
typedef int EdgeType;		//边上的权值类型

//边表结点结构
typedef struct EdgeNode {	
	int adjvex;				//邻接点域，存储该顶点对应的下标
	EdgeType weight;		//用于存储权值，对于非网图可以不需要
	struct EdgeNode* next;
}EdgeNode;

//顶点表结点结构
typedef struct VertexNode {
    int in;             //入度信息
	VertexType data;		//顶点域，存储顶点信息
	EdgeNode* firstedge;	//边表头指针
}VertexNode,AdjList[MAXVEX];

//邻接表
typedef struct {
	AdjList adjList;
	int numVertexs, numEdges;	//图中当前顶点数和边数
}GraphAdjList;

//建立有向图的邻接表结构
void CreateALGraphDir(GraphAdjList* G)
{
	int i, j, k, w;
	EdgeNode* e;
	printf("请输入顶点数和边数:\n");
	scanf("%d,%d", &G->numVertexs, &G->numEdges);	//输入顶点数和边数
	getchar();
	printf("请输入顶点信息 和入度信息:\n");
	//读入顶点信息建立顶点表
	for (i = 0; i < G->numVertexs; i++) {
		scanf("%c,%d", &(G->adjList[i].data),&(G->adjList[i].in));	//输入顶点信息和入度信息
		getchar();
		G->adjList[i].firstedge = NULL;	//将边表置为空表
	}
	//建立边表
	for (k = 0; k < G->numEdges; k++) {
		printf("输入边(vi,vj)上的顶点序号 和权重：\n");
		scanf("%d,%d,%d", &i, &j, &w);		//输入边(vi,vj)上的顶点序号
		getchar();

		e = (EdgeNode*)malloc(sizeof(EdgeNode));	//生成边表结点
		//头插法
        e->weight = w;  //权重
		e->adjvex = j;	//邻接序号	
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;
	}
}

//打印邻接表
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

//拓扑排序，用于关键路径计算
Status TopologicalSort(GraphAdjList GL) {
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;        //用于栈指针下标
    int count = 0;      //用于统计输出顶点的个数
    int *stack;         /* 建栈存储入度为0的顶点 */
                        //依次出栈后的序列，就是拓扑排序序列
    stack = (int *)malloc(GL.numVertexs * sizeof(int) );    //顺序栈，其实就是数组，有个top指针指向栈顶
    for ( i = 0; i < GL.numVertexs; i++) {
        if(GL.adjList[i].in == 0) {
            stack[++top] = i;       //将度为0的顶点入栈
        } 
    }
    top2 = 0;       //初始化为0
    etv = (int *)malloc(GL.numVertexs * sizeof(int));       //事件最早发生时间
    for (i = 0; i < GL.numVertexs; i++) {
        etv[i] = 0; //初始化为0
    }
    stack2 = (int *)malloc(GL.numVertexs * sizeof(int));    //初始化    
    while(top != 0) {
        gettop = stack[top--];  //出栈
        printf("%c -> ", GL.adjList[gettop].data);  //打印此顶点
        count++;
        stack2[++top2] = gettop;    //将弹出的顶点序号压入拓扑序列的栈
        for (e = GL.adjList[gettop].firstedge; e; e = e->next) {
            /* 对顶点弧表遍历 */
            k = e->adjvex;  //获得下一个顶点的下标
            GL.adjList[k].in--; //将k号顶点邻接点的入度减 1
            if (!GL.adjList[k].in) {
                stack[++top] = k;   //若为 0 则入栈，以便于下次循环输出
            }
            if ((etv[gettop] + e->weight > etv[k]))     //求各定点时间最早发生时间（也就是路径的最大值）
                etv[k] = etv[gettop] + e->weight;
        }
    }

    if (count < GL.numVertexs)  //如果count小于顶点数，说明存在环
        return ERROR;
    else
        return OK;
}

//求关键路径，GL为有向网，输出GL的各项关键活动
void CriticalPath(GraphAdjList GL) {
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte;           //声明活动最早发生时间和最迟发生时间变量
    ltv = (int *)malloc(GL.numVertexs * sizeof(int));   //事件最晚发生时间
    TopologicalSort(GL);    //求拓扑序列，计算数组 etv 和 stack2 的值
    // ltv = (int *)malloc(GL.numVertexs * sizeof(int));   //事件最晚发生时间
    for( i = 0; i < GL.numVertexs; i++) {
        ltv[i] = etv[GL.numVertexs - 1];        //初始化ltv
    }
    while(top2 != 0) {
        gettop = stack2[top2--];        //将拓扑序列出栈，后进先出
        for(e = GL.adjList[gettop].firstedge; e; e = e->next) {
            //求各顶点事件的最迟发生时间ltv值
            k = e->adjvex;
            if(ltv[k] - e->weight < ltv[gettop]) {  //求各顶点事件最晚发生时间
                ltv[gettop]  = ltv[k] - e->weight;
            }
        }
    }
    printf("\n")
    for(j = 0; j < GL.numVertexs; j++) {        //求ete,lte和关键活动
        for(e = GL.adjList[j].firstedge; e; e = e->next) {
            k = e->adjvex;
            ete = etv[j];               //活动最早发生时间
            lte = ltv[k] - e->weight;   //活动最迟发生时间
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