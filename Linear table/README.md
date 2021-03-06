
### 本目录包含如下内容  

- 顺序表的创建、插入、删除、查询等操作的代码 （即：LinearTable_1.c）
- 单链表的创建、插入、删除、查询等操作的代码 （即：LinearTable_2.c) 
- 静态链表的创建、插入、删除等操作的代码（即：LinearTable_3.c）  
- 双向链表的创建、插入、删除操作等代码（即：LinearTable_4.c)

### 线性表的抽象数据类型

> ADT  
> 
> - 线性表（List）  
> 
> Data  
> 
> - 线性表的数据对象集合为$\{a_1,a_2,a_3,...,a_n\}$，每个数据元素的类型为DataType。其中，除第一个元素$a_1$外，每个元素有且只有一个直接前驱元素，除最后一个元素$a_n$外，每个元素有且只有一个直接后继元素。数据元素之间的关系是一对一的关系。  
> 
> Operation  
> 
> - InitList(*L):         初始化，建立一个空的线性表L
> - ListEmpty(L):         若线性表为空，返回true，否则返回false。
> - ClearList(*L):        清空线性表。
> - GetElem(L,i,*e):      将线性表L中的第i个元素返回给e。
> - LocateElem(L,e):      在线性表中查找与给定值e相同的元素，如果查找成功，返回该元素在表中的序号表示成功；否则，返回-1表示失败。
> - ListInsert(*L,i,e):   在线性的表的第i个位置插入新元素e。
> - ListDelete(*L,i,*e):  删除线性表L中第i个位置元素，并用e返回其值。
> - ListLength(L):        返回线性表L的元素个数。  
> 
> endADT  

## 我的[线性表](https://sxhpai.github.io/2022/03/26/DS/DS1/)博客
