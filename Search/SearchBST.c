/****************** ���������� *******************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

//�������Ķ���������ṹ����
typedef struct BiTNode {
    int data;           //�������
    struct BiTNode *lchild, *rchild;    //���Һ���ָ��
}BiTNode, *BiTree;

/*�ݹ���Ҷ��������� T ���Ƿ���� key*/
/*ָ��fָ�� T ��˫�ף����ʼ����ֵΪ NULL ���ݹ����ʱ����*/
/*�����ҳɹ�����ָ�� p ָ�������Ԫ�ؽ�㣬 ������ TRUE */
/*����ָ�� p ָ�����·���Ϸ��ʵ����һ����㲢���� FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T) {                           //���Ҳ��ɹ�
        *p = f;
        return FALSE;
    }
    else if (key == T->data) {          //���ҳɹ�
        *p = T;
        return TRUE;
    }else if (key < T->data) {
        SearchBST(T->lchild, key, T, p);//����������������
    }else {
        SearchBST(T->rchild, key, T, p);//����������������
    }
}

/* ������������ T �в����ڹؼ��ֵ��� key ������Ԫ��ʱ��*/
/* ���� key ������ TRUE�����򷵻� FALSE */
Status InsertBST(BiTree *T, int key)
{
    BiTree p,s;
    if ( !SearchBST(*T, key, NULL, &p) )    //���Ҳ��ɹ�
    {
        s = (BiTree)malloc( sizeof(BiTNode) );
        s->data = key;
        s->lchild = NULL;
        s->rchild = NULL;
        if (!p) {
            *T = s;         //���� s Ϊ�µĸ����
        }else if ( key < p->data) {
            p->lchild = s;  //���� s Ϊ����
        }else{
            p->rchild = s;  //���� s Ϊ�Һ���
        }
        return TRUE;
    }else {
        return FALSE;       //�������йؼ�����ͬ�Ľ�㣬���ٲ���
    }
}

/******************************* 
    ɾ�������������: 
        1.Ҷ�ӽ��
        2.�������������
        3.�����������еĽ��
*********************************/

/* �Ӷ�����������ɾ�����p�����ؽ����������������*/
Status Delete(BiTree *p);

/* ������������ T �д��ڹؼ��ֵ��� key ������Ԫ��ʱ����ɾ��������Ԫ�ؽ�� */
/* ������ TRUE�� ���򷵻� FALSE */
Status DeleteBST(BiTree *T, int key) 
{
    if(!*T) {   //�������ڹؼ��ֵ��� key ������Ԫ��
        return FALSE;
    } else {
        if (key == (*T)->data) { //�ҵ��ؼ��ֵ��� key ������Ԫ��
            return Delete(T);
        } else if( key < (*T)->data) {
            return DeleteBST(&(*T)->lchild, key);
        } else {
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

/* �Ӷ�����������ɾ�����p�����ؽ����������������*/
Status Delete(BiTree *p)
{
    BiTree q,s;
    if( (*p)->rchild == NULL) {             //����������ֻ���ؽ�����������
        q = *p; *p = (*p)->lchild; free(q);   
    } else if( (*p)->lchild == NULL) {      //����������ֻ���ؽ�����������
        q = *p; *p = (*p)->rchild; free(q);
    } else {        //������������Ϊ��
        q = *p; s = (*p)->lchild;
        while(s->rchild) {      // ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ����
            q = s; s = s->rchild;
        }       
        (*p)->data = s->data;
        if(q != *p) {
            q->rchild = s->lchild;      //�ؽ�q��������
        } else {
            q->lchild = s->lchild;      //�ؽ�q��������
        }
        free(s);
    }   
    return TRUE;
}

//�������������
void InOrderTraverse(BiTree T) {
    if(T == NULL)
        return;
    InOrderTraverse(T->lchild);
    printf(" %d",T->data);
    InOrderTraverse(T->rchild);
}

//������
int main()
{
    //���ö�������Ĳ�����룬����һ�ö���������
    int i;
    int a[10] = {62,88,58,47,35,73,51,99,37,93};
    BiTree T = NULL;
    for(i = 0; i < 10; i++) {
        InsertBST(&T,a[i]);
    }

    //���������ӡ
    InOrderTraverse(T);
    printf("\n");
    //���� 66
    InsertBST(&T,66);
    //���������ӡ
    InOrderTraverse(T);
    printf("\n");
    //ɾ�� 66
    DeleteBST(&T,51);
    //���������ӡ    
    InOrderTraverse(T);
    printf("\n");
}