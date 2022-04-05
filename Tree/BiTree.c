
/************ 二叉树的创建与遍历 **************/

#include <stdio.h>
#include <stdlib.h>

typedef char TElemType;	// 树结点的数据类型，目前暂定为整型

/* 二叉树的二叉链表结点结构定义 */
typedef struct BiTNode {	/*结点结构*/
	TElemType data;	//结点数据
	struct BiTNode *lchild, *rchild;	//左右孩子指针
}BiTNode, *BiTree;

/* 二叉树的前序遍历递归算法 */
void PreOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	printf(" %c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

/* 二叉树的中序遍历递归算法 */
void InOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf(" %c", T->data);
	InOrderTraverse(T->rchild);
}

/* 二叉树的后序遍历递归算法 */
void PostOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf(" %c", T->data);
}

/* 按扩展前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTreePreOrder(BiTree *T) {	
	TElemType ch;
	scanf("%c", &ch);
	if (ch == '#') {
		*T = NULL;
	}
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			exit;
		(*T)->data = ch;	//生成根节点
		CreateBiTreePreOrder(&(*T)->lchild);	//构造左子树
		CreateBiTreePreOrder(&(*T)->rchild);	//构造右子树
	}
}



//主函数
int main()
{
	BiTree T;	//头指针
	
	CreateBiTreePreOrder(&T);

	PreOrderTraverse(T);
	printf("\n");
	InOrderTraverse(T);
	printf("\n");
	PostOrderTraverse(T);
	printf("\n");

	return 0;
}