
/****************************************************
------------------线性表顺序存储结构----------------
----------------------基本操作----------------------
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1	
#define OK 1

typedef int Status;		//函数状态，其值是函数结果状态代码

//顺序表的初始容量 
#define Size 5

//自定义顺序表
typedef struct SqList {
	int *data;		//存储空间的起始地址,声明一个长度不确定的数组 
	int length;		//当前顺序表的长度
	int size;		//当前顺序表的存储容量 
}SqList;

//顺序表初始化
Status InitSqList(SqList *L) {
	//动态申请存储空间 ，构造一个空的顺序表 
	L->data = (int *)malloc(Size * sizeof(int));
	if (!L->data) {
		//如果申请内存失败，作出提示并直接退出程序
		printf("初始化失败");
		return ERROR;
	}

	L->length = 0;
	L->size = Size;
}

//顺序表插入操作
Status ListInsert(SqList *L, int n, int Elem)
{
	//判断插入本身是否存在问题
	if (n < 0 || n > L->length) {
		printf("插入的位置出错\n");
		return ERROR;
	}

	//做插入操作时，首先需要看顺序表是否有多余的存储空间提供给插入的元素，如果没有，需要申请
	if (L->length == L->size) {
		L->data = (int *)realloc(L->data, (L->size + 1) * sizeof(int));
		if (!L->data) {
			printf("存储空间分配失败\n");
			return ERROR;
		}
		L->size++;
	}

	//插入操作，需要将从插入位置开始的后续元素，逐个后移
	for (int i = L->length - 1; i >= n; i--) {
		L->data[i + 1] = L->data[i];
	}
	L->data[n] = Elem;
	L->length++;
	return OK;
}

//顺序表删除操作
Status ListDelete(SqList *L, int n)
{
	//判断删除本身是否存在问题
	if (n < 0 || n >= L->length) {
		printf("删除的位置出错\n");
		return ERROR;
	}
	//删除操作
	for (int i = n; i < L->length; i++) {
		L->data[i] = L->data[i + 1];
	}
	L->length--;
	return OK;
}

//查找第n个元素，并返回给e
Status GetElem(SqList L, int n, int *e)
{
	if (n < 0 || n > L.length) {
		return ERROR;
	}
	*e = L.data[n];
	return OK;
}

//查找和元素e一样的元素，并将位置返回给n
Status LocateElem(SqList L, int *n, int e)
{
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == e) {
			*n = i;
			return OK;
		}
	}
	*n = -1;
	return ERROR;
}

//顺序表显示
void DisplaySqList(SqList *L) {
	for (int i = 0; i < L->length; i++) {
		printf(" %d", L->data[i]);
	}
	printf("\n");
}


int main() {
	//定义一个顺序表
	SqList List;
	int e, n;

	//初始化顺序表并赋初值
	InitSqList(&List);
	for (int i = 0; i < List.size; i++) {
		List.data[i] = i + 1;
		List.length++;
	}
	DisplaySqList(&List);

	//插入操作
	ListInsert(&List, 10, 9);
	DisplaySqList(&List);

	//删除操纵
	ListDelete(&List, 10);
	DisplaySqList(&List);

	//查询操作
	GetElem(List, 0, &e);
	printf(" %d\n", e);
	LocateElem(List, &n, 1);
	printf(" %d\n", n);

	return 0;
}
