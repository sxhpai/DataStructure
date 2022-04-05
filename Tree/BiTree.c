
/************ �������Ĵ�������� **************/

#include <stdio.h>
#include <stdlib.h>

typedef char TElemType;	// �������������ͣ�Ŀǰ�ݶ�Ϊ����

/* �������Ķ���������ṹ���� */
typedef struct BiTNode {	/*���ṹ*/
	TElemType data;	//�������
	struct BiTNode *lchild, *rchild;	//���Һ���ָ��
}BiTNode, *BiTree;

/* ��������ǰ������ݹ��㷨 */
void PreOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	printf(" %c", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

/* ����������������ݹ��㷨 */
void InOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf(" %c", T->data);
	InOrderTraverse(T->rchild);
}

/* �������ĺ�������ݹ��㷨 */
void PostOrderTraverse(BiTree T) {
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf(" %c", T->data);
}

/* ����չǰ������������н���ֵ��һ���ַ��� */
/* #��ʾ������������������ʾ������T�� */
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
		(*T)->data = ch;	//���ɸ��ڵ�
		CreateBiTreePreOrder(&(*T)->lchild);	//����������
		CreateBiTreePreOrder(&(*T)->rchild);	//����������
	}
}



//������
int main()
{
	BiTree T;	//ͷָ��
	
	CreateBiTreePreOrder(&T);

	PreOrderTraverse(T);
	printf("\n");
	InOrderTraverse(T);
	printf("\n");
	PostOrderTraverse(T);
	printf("\n");

	return 0;
}