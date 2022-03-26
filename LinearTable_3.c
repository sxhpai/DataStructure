/**************************************
****************静态链表***************
***************************************/

/*--------------本例说明----------------*/
//将数组下标为0的元素视为备用链表的	   头结点，其data为空，其cur存放第一个备用结点的下标
//将数组下标为1的元素视为存放数据链表的头结点，其data为空，其cur存放第一个存放数据的结点的下标

/*--------------知识点扩充----------------*/
//头结点位置的选取也可以这样
//将结构体数组的第一个元素（即：下标为0的元素），作为备用链表的头结点
//将结构体数组的最后一个元素，作为数据链表的头结点

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1
#define MaxSize 100

typedef int Status;	
typedef int ElemType;

//静态链表结点
typedef struct {
	ElemType data;	//数据
	int cur;	//游标
}component;

//结构体数组初始化为备用链表
void reserveArr(component *array);

//从备用链表为数据链表分配空间
int mallocArr(component *array);

//备用链表回收空，其中array为存储函数数据的数组，k表示未使用结点所在的数组下标
void freeArr(component *array, int k);

//初始化静态链表
int initArr(component *array);

//插入操作
//操作结果：在静态链表array的第n个元素以前插入数据元素e
Status insertArr(component *array, int head, int n, int e);

//删除操作
//操作结果：删除静态链表第n个元素
Status deleteArr(component *array, int head, int n);

//查询操作
//操作结果：在头结点下标为head的链表中，查询数据域为elem的结点在数组中的位置,并返回
int selectElem(component *array, int head, int elem);

//修改操作
//
Status amendElem(component *array, int head, int oldElem, int newElem);

//打印静态链表中数据链表
//输入参数：array为结构数组的首地址，head为静态链表头结点的下标
void displayArr(component *array, int head);

//主函数
int main() {
	component SLL[MaxSize];

	//初始化静态链表
	int head = initArr(SLL);
	displayArr(SLL, head);

	//插入操作
	insertArr(SLL, head, 1, 44);
	displayArr(SLL, head);

	//删除操作
	deleteArr(SLL, head, 1);
	displayArr(SLL, head);

	//查询操作
	int s = selectElem(SLL, head,8);
	printf(" %d\n", s);


	return 0;
}


//结构体数组初始化为备用链表
void reserveArr(component *array) {
	for (int i = 0; i < MaxSize; i++) {
		array[i].data = -1;		//备用链表每个结点的数据都为-1
		array[i].cur = i + 1;	//备用链表每个结点的游标都指向下一个结点
	}
	array[MaxSize - 1].cur = 0;	//备用链表的最后一个结点的游标值为0，表示链表的结束
}

//从备用链表为数据链表分配空间
int mallocArr(component *array) {
	int i = array[0].cur;	//取得备用链表头结点的游标，（即：要分配结点的下标）
	if (array[0].cur) {
		//如果头结点的游标不是0，说明分配成功，备用链表的头结点要指向下一个备用结点
		array[0].cur = array[i].cur;
	}
	return i;	//返回要分配结点的下标
}

//备用链表回收空，其中array为存储函数数据的数组，k表示未使用结点所在的数组下标
void freeArr(component *array, int k) {
	array[k].cur = array[0].cur;
	array[0].cur = k;
}

//初始化静态链表
int initArr(component *array) {
	//1.将数组备用链表化
	reserveArr(array);
	//2.为数据链表的分配头结点
	int head = mallocArr(array);	//为数据链表头结点分配空间并取得下标
	//3.初始化静态链表
	int temp = head;	//临时变量取得头结点的下标
	for (int i = 1; i < 9; i++) {	/*-----第一次循环的动作注释----*/
		int j = mallocArr(array);	//为数据链表的第一个结点分配空间并取得下标
		array[temp].cur = j;		//让头结点指向第一个结点
		array[j].data = i;			//为第一个结点的数据赋值
		temp = j;					//temp取得第一个结点下标，后移
	}
	array[temp].cur = 0;			//将数据链表的最后一个结点的赋值为0，表示数据链表的结束。
	//4.返回头结点的下标
	return head;
}

//插入操作
//操作结果：在静态链表array的第n个元素以前插入数据元素e
Status insertArr(component *array, int head, int n, int e) {
	int temp = head;	//临时变量取得头结点的下标

	//1.找到要插入位置的前一个结点的下标
	for (int i = 1; i < n; i++) {
		temp = array[temp].cur;
	}

	//2.申请新节点
	int newElem = mallocArr(array);	//newElem为新结点的下标
	if (!newElem) {
		printf("分配空间失败");
		return ERROR;
	}
	array[newElem].data = e;

	//3.插入操作
	array[newElem].cur = array[temp].cur;
	array[temp].cur = newElem;

	return OK;
}

//删除操作
//操作结果：删除静态链表第n个元素
Status deleteArr(component *array, int head, int n) {
	int temp = head;	//临时变量取得头结点的下标

	//1.找到要删除元素的上一个结点的下标
	for (int i = 0; i < n; i++) {
		temp = array[temp].cur;
	}

	//2.删除操作
	int del = array[temp].cur;
	array[temp].cur = array[del].cur;
	freeArr(array, del);			//将用不到的结点重新链入备用链表
	return OK;
}

//查询操作
//操作结果：在头结点下标为head的链表中，查询数据域为elem的结点在数组中的位置,并返回
int selectElem(component *array, int head, int elem) {
	int temp = head;
	//0.当游标值为0时，表示链表结束，循环结束
	while (array[temp].cur != 0) {
		if (array[temp].data == elem) {
			return temp;
		}
		temp = array[temp].cur;
	}
	//最后一个元素
	if (array[temp].data == elem) {
		return temp;
	}
	return -1;	//返回-1，表示在链表中没有找到该元素
}

//修改操作
//操作结果将以head为头的静态链表array的数据域为oldElem的数据元素，将其数据域换为newElem
Status amendElem(component *array, int head, int oldElem, int newElem) {
	int temp = head;;
	//0.当游标值为0时，表示链表结束
	while (array[temp].cur != 0) {
		if (array[temp].data == oldElem) {
			array[temp].data = newElem;
			return OK;
		}
		temp = array[temp].cur;
	}
	//最后一个元素
	if (array[temp].data == oldElem) {
		array[temp].data = newElem;
		return OK;
	}
	return ERROR;
}

//打印静态链表中数据链表
//输入参数：array为结构数组的首地址，head为静态链表头结点的下标
void displayArr(component *array, int head) {
	int temp = head;			//从数据链表的头结点开始输出
	//int temp = array[head].cur;	//从数据链表的第一个结点开始输出
	while (array[temp].cur)
	{
		printf(" %d %d,", array[temp].data, array[temp].cur);
		temp = array[temp].cur;
	}
	printf(" %d %d, ", array[temp].data, array[temp].cur);

	printf("\n");
}
