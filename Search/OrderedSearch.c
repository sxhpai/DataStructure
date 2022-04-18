
/**************** 静态查找 ***************/
/*************** 有序表查找 **************/
#include <stdio.h>

//二分查找
//a为数组，n为n要查找的数组有效长度（从a[1]开始到a[n]结束的长度），key为要查询的关键字
/******************* 时间复杂度: O(logn)****************/
int Binary_Search(int *a, int n, int key) 
{
    int low,high,mid;
    low = 1;            //定义最低下标为记录首位
    high = n;           //定义最高下标为记录末位

    //查询
    while(low <= high) {
        mid = (low + high)/2;   //二分
        if (key < a[mid]) {     //若查找值比中值小
            high = mid - 1;     //最高下标调整到中位下标小一位
        }else if (key > a[mid]) {  //若查找值比中值大
            low = mid + 1;      //最低下标调整到中位下标大一位
        }else {
            return mid;         //若相等则说明 mid 即为查找到的位置
        }
    }
    return 0;
}

//插值查找，二分查找的优化
//a为数组，n为n要查找的数组有效长度（从a[1]开始到a[n]结束的长度），key为要查询的关键字
/******************* 时间复杂度: O(logn)****************/
int Interpolation_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;
    high = n;

    //查询
    while( low <= high ) {
        // mid = (low + high)/2;
        mid = low + (high - low)*(key - a[low])/(a[high] - a[low]);/**** 插值公式****/
        
        if(key < a[mid]) {
            high = mid - 1;
        }else if (key > a[mid]) {
            low = mid + 1;
        }else {
            return mid;
        }
    }
    return 0;
}

//斐波那契查找，二分查找的优化
//a为数组，n为n要查找的数组有效长度（从a[1]开始到a[n]结束的长度），key为要查询的关键字
/******************* 时间复杂度: O(logn)****************/
int F[] = {0,1,1,2,3,5,8,13,21,34,55,89};   //定义一个斐波那契数列

int Fibonacci_Search(int *a, int n, int key) 
{
    int low, high, mid, i, k;
    low = 1;                        //定义最低下标为记录首位
    high = n;                       //定义最高下标为记录末位
    k = 0;                  
    while (n > F[k] - 1) {          //计算 n 位于斐波那契数列的位置
        k++;
    }
    for ( i = n; i < F[k] - 1; i++) {   //将不满的数值补全
        a[i] = a[n];
    }

    //查询
    while(low <= high) {
        mid = low + F[k - 1] - 1;       //计算当前分隔的下标
        if (key < a[mid]) {
            high = mid - 1;     //最高下标调整到分隔下标 mid-1 处
            k = k - 1;          //斐波那契数列下标减一位
        }else if (key > a[mid]) {
            low = mid + 1;      //最低位下标调整到分隔下 mid=1 处
            k = k - 2;          //斐波那契数列下标减两位
        }else {
            if (mid <= n) {
                return mid;     //若相等则说明 mid 即为查找到的位置
            }else {
                return n;       //若 mid>n 说明是补全数值，返回 n
            }
        }
    }
    return 0;
}

//主函数
int main()
{
    int a[] = {0,1,2,3,4,5,6,7,8,9,10,11};  //a[0]:无效值; 有效值从a[1]开始。
    int length = sizeof(a)/sizeof(int) - 1; //长度从 a[1] 开始
    printf(" length = %d\n",length);

    printf(" Binary_Search = %d\n", Binary_Search(a, length, 7));
    printf(" Interpolation_Search = %d\n", Interpolation_Search(a,length, 8));
    printf(" Fibonacci_Search = %d\n",Fibonacci_Search(a,length, 6));

    return 0;
}