/****************** 二叉排序树 *******************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

//二叉树的二叉链表结点结构定义
typedef struct BiTNode {
    int data;           //结点数据
    struct BiTNode *lchild, *rchild;    //左右孩子指针
}BiTNode, *BiTree;

/*递归查找二叉排序树 T 中是否存在 key*/
/*指针f指向 T 的双亲，其初始调用值为 NULL ，递归调用时有用*/
/*若查找成功，则指针 p 指向该数据元素结点， 并返回 TRUE */
/*否则指针 p 指向查找路径上访问的最后一个结点并返回 FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T) {                           //查找不成功
        *p = f;
        return FALSE;
    }
    else if (key == T->data) {          //查找成功
        *p = T;
        return TRUE;
    }else if (key < T->data) {
        SearchBST(T->lchild, key, T, p);//在左子树继续查找
    }else {
        SearchBST(T->rchild, key, T, p);//在右子树继续查找
    }
}

/* 当二叉排序树 T 中不存在关键字等于 key 的数据元素时，*/
/* 插入 key 并返回 TRUE，否则返回 FALSE */
Status InsertBST(BiTree *T, int key)
{
    BiTree p,s;
    if ( !SearchBST(*T, key, NULL, &p) )    //查找不成功
    {
        s = (BiTree)malloc( sizeof(BiTNode) );
        s->data = key;
        s->lchild = NULL;
        s->rchild = NULL;
        if (!p) {
            *T = s;         //插入 s 为新的根结点
        }else if ( key < p->data) {
            p->lchild = s;  //插入 s 为左孩子
        }else{
            p->rchild = s;  //插入 s 为右孩子
        }
        return TRUE;
    }else {
        return FALSE;       //树中已有关键字相同的结点，不再插入
    }
}

/******************************* 
    删除结点的三种情况: 
        1.叶子结点
        2.仅有左或右子树
        3.左右子树都有的结点
*********************************/

/* 从二叉排序树中删除结点p，并重接它的左或右子树。*/
Status Delete(BiTree *p);

/* 若二叉排序树 T 中存在关键字等于 key 的数据元素时，则删除该数据元素结点 */
/* 并返回 TRUE； 否则返回 FALSE */
Status DeleteBST(BiTree *T, int key) 
{
    if(!*T) {   //若不存在关键字等于 key 的数据元素
        return FALSE;
    } else {
        if (key == (*T)->data) { //找到关键字等于 key 的数据元素
            return Delete(T);
        } else if( key < (*T)->data) {
            return DeleteBST(&(*T)->lchild, key);
        } else {
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树。*/
Status Delete(BiTree *p)
{
    BiTree q,s;
    if( (*p)->rchild == NULL) {             //右子树空则只需重接它的左子树
        q = *p; *p = (*p)->lchild; free(q);   
    } else if( (*p)->lchild == NULL) {      //左子树空则只需重接它的右子树
        q = *p; *p = (*p)->rchild; free(q);
    } else {        //左右子树均不为空
        q = *p; s = (*p)->lchild;
        while(s->rchild) {      // 转左，然后向右到尽头（找待删结点的前驱）
            q = s; s = s->rchild;
        }       
        (*p)->data = s->data;
        if(q != *p) {
            q->rchild = s->lchild;      //重接q的右子树
        } else {
            q->lchild = s->lchild;      //重接q的左子树
        }
        free(s);
    }   
    return TRUE;
}

//二叉树中序遍历
void InOrderTraverse(BiTree T) {
    if(T == NULL)
        return;
    InOrderTraverse(T->lchild);
    printf(" %d",T->data);
    InOrderTraverse(T->rchild);
}

//主函数
int main()
{
    //利用二叉排序的插入代码，构建一棵二叉排序树
    int i;
    int a[10] = {62,88,58,47,35,73,51,99,37,93};
    BiTree T = NULL;
    for(i = 0; i < 10; i++) {
        InsertBST(&T,a[i]);
    }

    //中序遍历打印
    InOrderTraverse(T);
    printf("\n");
    //插入 66
    InsertBST(&T,66);
    //中序遍历打印
    InOrderTraverse(T);
    printf("\n");
    //删除 66
    DeleteBST(&T,51);
    //中序遍历打印    
    InOrderTraverse(T);
    printf("\n");
}