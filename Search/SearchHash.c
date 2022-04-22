#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12      //����ɢ�б�Ϊ����ĳ���
#define NULLKEY -32768
#define OK 1
#define ERROR 0

typedef int Status;

typedef struct {
    int *elem;      //����Ԫ�ش洢��ַ����̬��������
    int count;      //��ǰ����Ԫ�ظ���
}HashTable;

int m = 0;      //ɢ�б����ȫ�ֱ���

/* ��ʼ��ɢ�б� */
Status InitHashTable( HashTable *H)
{
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = ( int * )malloc( m * sizeof( int ) ); //���� m ��int ��ô��Ĵ洢�ռ�
    for( i = 0; i < m; i++ ) {
        H->elem[i] = NULLKEY;       //�����е�Ԫ�س�ʼ��ΪNULLKEY
    }
    return OK;
}

/* ɢ�к��� */
int Hash(int key)
{
    return key % m; //����������
}

/* ����ؼ��ֽ�ɢ�б� */
void InsertHash( HashTable *H, int key)
{
    int addr = Hash(key);
    while( H->elem[addr] != NULLKEY) {   // �����Ϊ�գ����ͻ
        addr = (addr + 1) % m;          // ���Ŷ�ַ��������̽��
    }    
    H->elem[addr] = key;                // ֱ���п�λ�����ؼ���
}

/* ɢ�б���ҹؼ��� */
Status SearchHash( HashTable H, int key, int *addr)
{
    *addr = Hash(key);                  //��ɢ�е�ַ���ؼ�
    while(H.elem[*addr] != key) {       //���ؼ�����ȡ�õ�ַ�ϵĹؼ��ֲ�ͬ��˵���г�ͻ
        *addr = (*addr + 1) % m;        //���ŵ�ַ������̽��
        if ( H.elem[*addr] == NULLKEY || *addr == Hash(key) ) {
            //���ѭ���ص�ԭ��
            return UNSUCCESS;
        }
    }
    return SUCCESS;
}

//������
int main()
{
    int i,keyadd;
    int a[] = {12,25,37,15,16,29,48,67,56,21,22,47};

    HashTable T;            //����һ����ϣ��
    InitHashTable(&T);      //��ʼ����ϣ��

    for(i = 0; i < 12; i++) {       //���չ�ϣ������������
        InsertHash(&T, a[i]);
    }

    if ( SearchHash(T,37,&keyadd) ){//���ҹ�ϣ���� 37 ��λ�ã�������
        printf(" (%d)\n",keyadd);   //���ɹ��ҵ������ӡ��λ��
    }else{
        printf("UNSUCCESS!\n");     //�����ӡ���ɹ�
    }

    return 0;
}