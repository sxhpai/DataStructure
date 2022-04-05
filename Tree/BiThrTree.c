
/************** 二叉树线索化与其遍历 **************/

#include <stdio.h>
#include <stdlib.h>

typedef char TElemType;	//结点中数据域的类型

//枚举，Link为0，Thread为1
typedef enum {
	Link,
	Thread
}PointerTag; //Link = 0表示指向左右孩子指针
		     //Thread = 1表示指向前驱或后继的线索

//结点结构构造
typedef struct BiThrNode {	//二叉线索存储结点结构
	TElemType data;			//结点数据
	struct BiThrNode *lchild, *rchild;	//左右孩子指针
	PointerTag ltag, rtag;	//左右标志
}BiThrNode,*BiThrTree;

BiThrTree pre = NULL;	//全局变量，始终指向刚刚访问过的结点

//扩展前序遍历格式输入
//创建二叉树
void CreatBiTree(BiThrTree *T) {
	TElemType ch;
	scanf("%c", &ch);
	if (ch == '#') {
		(*T) = NULL;
	}
	else {
		(*T) = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!*T)
			exit;
		(*T)->data = ch;
		(*T)->ltag = Link;
		(*T)->rtag = Link;
		CreatBiTree(&(*T)->lchild);
		CreatBiTree(&(*T)->rchild);
	}
}

//前序遍历二叉树
void PreOrderTraverse(BiThrTree T) {
	if (T == NULL)
		return;
	printf(" %c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//中序遍历二叉树
void InOrderTraverse(BiThrTree T) {
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf(" %c", T->data);
	InOrderTraverse(T->rchild);
}

//线索二叉树的创建
/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p) {
	//如果当前结点存在
	if (p) {
		InThreading(p->lchild);	//递归当前结点的左子树，进行线索化
		//如果当前结点没有左孩子，左标志位设为1，左指针域指向上一结点 pre
		if (!p->lchild) {
			p->ltag = Thread;
			p->lchild = pre;
		}
		//如果 pre 没有右孩子，右标志位设为1，右指针域指向当前结点。
		if (pre && !pre->rchild) {
			pre->rtag = Thread;
			pre->rchild = p;
		}
		pre = p;		//线索化完左子树，让pre指针指向当前结点。
						//保持 pre 指向 p 的前驱
		InThreading(p->rchild);	//递归右子树线索化
	}
}



//中序遍历线索二叉树
void InOrderThraverse_Thr(BiThrTree p)
{
	while (p) {
		//一直找左孩子，最后一个位中序序列的中排第一的
		while (p->ltag == Link) {
			p = p->lchild;
		}
		printf(" %c", p->data);//操作结点数据
		//当结点右标志位为1时，直接找到其后继结点
		while (p->rtag == Thread && p->rchild != NULL) {
			p = p->rchild;
			printf(" %c", p->data);
		}
		//否则，按照中序遍历的规律，找其右子树最左下的结点，也就是继续循环遍历
		p = p->rchild;
	}
}

//T指向头结点，头结点左链lchild指向根节点，头结点右链rchild指向中序遍历的最后一个结点。中序遍历二叉线索表表示的二叉树T
//void InOrderThraverse_Thr(BiThrTree T)
//{
//	BiThrTree p;
//	p = T->lchild;	//p指向根结点
//	while (p) {
//		while (p->ltag == Link)
//			p = p->lchild;
//		printf(" %c", p->data);
//		while (p->rtag == Thread && p->rchild != NULL)
//		{
//			p = p->rchild;
//			printf(" %c", p->data);
//		}
//		p = p->rchild;
//	}
//}

int main()
{
	BiThrTree T;//定义二叉树

	//二叉树扩展前序输入初始化
	CreatBiTree(&T);

	PreOrderTraverse(T);//显示
	printf("\n");
	InOrderTraverse(T);

	//线索化二叉树
	InThreading(T);
	printf("\n");

	//遍历线索二叉树
	InOrderThraverse_Thr(T);

	return 0;
}
