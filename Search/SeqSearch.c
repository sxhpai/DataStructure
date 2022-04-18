/**************** 静态查找 ***************/
/**************** 顺序查找 ***************/

#include <stdio.h>

/*顺序查找，a为数组，n为要查找的数组长度，key为要查找的关键字*/
/************** 时间复杂度: O(n) *****************/
int Sequential_Search(int *a, int n, int key)
{
    int i;
    for(i = 1; i < n; i++) {
        if(a[i] == key) {
            return i;
        }
    }
    return 0;
}

/*有哨兵的顺序查找*/
/************** 时间复杂度: O(n) *****************/
int Sequential_Search2(int *a, int n, int key)
{
    int i = n; 
    a[0] = key;
    while(a[i] != key) {
        i--;
    }
    return i;
}

/*有哨兵的顺序查找 2 */
/************** 时间复杂度: O(n) *****************/
int Sequential_Search3(int *a, int n, int key)
{
    int i = 0;
    a[n] = key;
    while(a[i] != key) {
        i++;
    }
    return i;   //返回 n 说明查找失败，返回0 ~ n-1 说明查找成功
}
int main() {

    int a[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
    int length = sizeof(a)/sizeof(int);
    
    printf(" search1 = %d\n",Sequential_Search(a,length,7));
    printf(" search2 = %d\n",Sequential_Search2(a,length,8));
    printf(" search3 = %d\n",Sequential_Search3(a,length,1));

    return 0;
}