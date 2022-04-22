#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12      //定义散列表长为数组的长度
#define NULLKEY -32768
#define OK 1
#define ERROR 0

typedef int Status;

typedef struct {
    int *elem;      //数据元素存储基址，动态分配数组
    int count;      //当前数据元素个数
}HashTable;

int m = 0;      //散列表表长，全局变量

/* 初始化散列表 */
Status InitHashTable( HashTable *H)
{
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = ( int * )malloc( m * sizeof( int ) ); //申请 m 个int 那么大的存储空间
    for( i = 0; i < m; i++ ) {
        H->elem[i] = NULLKEY;       //将所有的元素初始化为NULLKEY
    }
    return OK;
}

/* 散列函数 */
int Hash(int key)
{
    return key % m; //除留余数法
}

/* 插入关键字进散列表 */
void InsertHash( HashTable *H, int key)
{
    int addr = Hash(key);
    while( H->elem[addr] != NULLKEY) {   // 如果不为空，则冲突
        addr = (addr + 1) % m;          // 开放定址法的线性探测
    }    
    H->elem[addr] = key;                // 直到有空位后插入关键字
}

/* 散列表查找关键字 */
Status SearchHash( HashTable H, int key, int *addr)
{
    *addr = Hash(key);                  //求散列地址，关键
    while(H.elem[*addr] != key) {       //若关键字与取得地址上的关键字不同，说明有冲突
        *addr = (*addr + 1) % m;        //开放地址法线性探测
        if ( H.elem[*addr] == NULLKEY || *addr == Hash(key) ) {
            //如果循环回到原点
            return UNSUCCESS;
        }
    }
    return SUCCESS;
}

//主函数
int main()
{
    int i,keyadd;
    int a[] = {12,25,37,15,16,29,48,67,56,21,22,47};

    HashTable T;            //定义一个哈希表
    InitHashTable(&T);      //初始化哈希表

    for(i = 0; i < 12; i++) {       //按照哈希表规则插入数据
        InsertHash(&T, a[i]);
    }

    if ( SearchHash(T,37,&keyadd) ){//查找哈希表中 37 的位置，并返回
        printf(" (%d)\n",keyadd);   //若成功找到，则打印其位置
    }else{
        printf("UNSUCCESS!\n");     //否则打印不成功
    }

    return 0;
}