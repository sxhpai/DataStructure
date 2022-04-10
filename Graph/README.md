
### 本目录包含如下内容  

- 邻接矩阵和邻接表的图存储结构（graph_0.c）
- 十字链表的有向图存储结构（graph_1.c）
- 邻接多重表的无向图存储结构（graph_2.c）

### 树的抽象数据类型  

ADT	

- 图（Graph）

Data

- 顶点的有穷非空集合和边的集合。

Operation

- CreateGraph(*G,V,VR)：按照顶点集 V 和边弧集 VR 的定义构造图 G。
- DestroyGraph(*G)：图 G 存在则销毁。
- LocateVex(G,u)：若图 G 中存在顶点 u ,则返回图中的位置。
- GetVex(G,v)：返回图 G 中顶点 v 的值。
- PutVex(G,v,value)：将图 G 中顶点 v 赋值 value。
- FirstAdjVex(G,*v)：返回顶点 v 的一个邻接顶点，若顶点在 G 中无邻接顶点返回空。
- NextAdjVex(G,v,*w)：返回顶点 v 相对于顶点 w 的下一个邻接顶点，若 w 是 v 的最后一个邻接点则返回”空“。
- InsertArc(*G,v,w)：在图中增添弧<v,w>，若 G 是无向图，还需要增添对称弧 <w,v>。
- DeleteArc(*G,v,w)：在图 G 中删除弧<v,w>，若 G 是无向图，则还删除对称弧 <w,v>。
- DFSTraverse(G)：对图 G 中进行深度优先遍历，在遍历过程对每个顶点调用。
- HFSTraverse(G)：对图 G 中进行广度优先遍历，在遍历过程对每个顶点调用。

endADT

## 我的[图](https://sxhpai.github.io/2022/04/09/DS/DS5/)博客
