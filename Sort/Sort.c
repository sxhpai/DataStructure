/************** 七个排序算法 *****************/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAXSIZE 10          // 用于要排序数组个数最大值，可根据需要修改

typedef int Status;

typedef struct {
    int r[MAXSIZE + 1];     // 用于存储要排序数组，r[0]用作哨兵或临时变量
    int length;             // 用于记录顺序表长度
}SqList;

/* 交换 L 中数组 r 的下标为 i 和 j 的值 */
void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

//顺序表初始化
void InitSqList(SqList *L)
{
    int i;
    int temp[11] = {0,9,1,5,8,3,7,4,6,2,10};
    for( i = 1; i <= 10; i++) {
        L->r[i] = temp[i];
    }
    L->length = MAXSIZE;
}

//打印顺序表
void PrintSqList(SqList L)
{
    int i;
    for( i = 1; i<=10; i++) {
        printf(" %d",L.r[i]);
    }
    printf("\n");
}
/***************************************************************/
/* 冒泡排序初级版算法 */
/* 时间复杂度： O(n^2) */
/***************************************************************/
void BubbleSort0(SqList *L)
{
    int i,j;
    for ( i = 1; i < L->length; i++ ) {
        for( j = i + 1; j <= L->length; j++ ) {
            if( L->r[i] > L->r[j]) {    //从小到大排序
                swap(L, i, j);
            }
            // if( L->r[i] < L->r[j]) {    //从大到小排序
            //     swap(L, i, j);
            // }
        }
    }
}

/***************************************************************/
/* 冒泡排序算法 */
/* 时间复杂度： O(n^2) */
/***************************************************************/
void BubbleSort(SqList *L)
{
    int i, j;
    for(i = 1; i < L->length; i++) {
        for(j = L->length; j > i; j--) {
            if(L->r[j] < L->r[j-1]) { //若后面的比前面的小，则交换
                swap(L, j, j-1);
            }
        }
    }
}

/***************************************************************/
/* 冒泡排序优化算法 */
/* 时间复杂度： O(n^2) */
/***************************************************************/
void BubbleSort2(SqList *L)
{
    int i,j;
    Status flag = TRUE;     //首轮循环为真
    for(i = 1; i < L->length && flag; i++) {
        flag = FALSE;                   //每一轮初始都为FALSE
        for(j = L->length; j > i; j--) {
            if(L->r[j] < L->r[j - 1]) { //若后面的比前面的小，则交换
                swap( L, j, j - 1);
                flag = TRUE;            //如果有数据交换，将flag设为TRUE
                                        /* 若没有数据交换，说明此序列已经排好序，不需要继续循环 */
            }
        }
    }
}

/***************************************************************/
/* 简单选择排序算法 */
/* 时间复杂度： O(n^2) */
/***************************************************************/
void SelectSort(SqList *L)
{//（我的理解：冒泡排序初级版的优化，就是不交换了，优化为每轮记录最小值（或最大值）的下标，这一轮循环结束后，只用交换一次就行。）
    int i,j,min;
    for (i = 1; i < L->length; i++) {
        min = i;                                //将当前下标定义为最小值下标
        for (j = i+1; j <= L->length; j++) {    //循环之后的数据
            if (L->r[j] < L->r[min]) {          //如果有小于当前最小值的关键字
                min = j;                        //将此关键字的下标赋值给 min
            }
        }           
        if(i != min) {                          //若 min 不等于 i，说明找到最小值，则交换两者的值
            swap(L, min, i);
        }
    }
}

/***************************************************************/
/* 直接插入排序算法 */
/* 时间复杂度： O(n^2) */
/***************************************************************/
void InsertSort(SqList *L)
{
    int i,j;
    for (i = 2; i <= L->length; i++) {  
        if (L->r[i] < L->r[i-1]) {          //如果后面小于前面，则需要将 L->r[i] 插入到有序表
            L->r[0] = L->r[i];              //将待插入的保存到r[0]
            for(j = i-1; L->r[j] > L->r[0]; j--) {
                L->r[j+1] = L->r[j];        //记录后移
            }
            L->r[j+1] = L->r[0];            //插入正确的位置
        }
    }
}

/***************************************************************/
/* 希尔排序算法 */
/* 时间复杂度： O(n^(3/2)) */
/***************************************************************/
void ShellSort(SqList *L) 
{
    int i,j;
    int increment = L->length;
    do
    {
        increment = increment/3 + 1;
        for(i = increment + 1; i <= L->length; i++) {
            if (L->r[i] < L->r[i-increment]) {
                //需要将L->r[i]插入有序增量表
                L->r[0] = L->r[i];                  //暂存在 L->r[0]
                for(j = i-increment; j > 0 && L->r[0] < L->r[j]; j -= increment) {
                    L->r[j+increment] = L->r[j];    //记录后移，查找插入位置
                }
                L->r[j+increment] = L->r[0];        //插入
            }
        }
    } while (increment > 1);
}

/***************************************************************/
/* 堆排序算法 */
/* 时间复杂度： O(n * logn) */
/***************************************************************/

/* 已知 L->[s..m] 中记录的关键字除 L->r[s] 之外均满足堆的定义 */
/* 本函数调整 L->r[s] 的关键字，使 L->r[s..m] 成为 一个大顶堆 */
void HeapAdjust(SqList *L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    for (j = 2 * s; j <= m; j *= 2) {           //沿着关键字较大的孩子结点向下筛选
        if(j < m && L->r[j] < L->r[j+1]) {
            ++j;                                // j 为关键字较大的记录的下标
        }
        if(temp >= L->r[j]) {
            break;                              // rc 应插入在位置 s 上
        }   
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

/* 堆排序算法 */
void HeapSort(SqList *L)
{
    int i;
    for (i = L->length/2; i > 0; i--) { //把 L 中的 r 构建成一个大顶堆
        HeapAdjust(L,i,L->length);
    }

    for (i = L->length; i > 1; i--) {
        swap(L, 1, i);          //将堆顶记录和当前未经排序子序列的最后一个记录交换
        HeapAdjust(L, 1, i-1);  //将 L->r[1...i-1]重新调整为大顶堆
    }
}

/***************************************************************/
/* 归并排序算法 */
/* 时间复杂度： O(n * logn) */
/***************************************************************/

/* 归并排序算法的递归实现 */
//将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
void Merge(int SR[], int TR[], int i, int m, int n)     //归并排序的核心代码
{
    int j,k,l;
    // i 为 SR[i..m]的下标； j 为 SR[m+1..n]的下标
    j = m + 1;
    for (k = i; i <= m && j <= n; k++) {   //将 SR 中记录由小到大归并入 TR
        if(SR[i] < SR[j]) {
            TR[k] = SR[i++];
        }else{
            TR[k] = SR[j++];
        }
    }
    if(i <= m) {
        for(l = 0; l <= m - i; l++) {
            TR[k+l] = SR[i+l];
        }
    }
    if(j <= n) {
        for(l = 0; l <= n - j; l++) {
            TR[k+l] = SR[j+l];
        }
    }
}
// 将 SR[s..t] 归并排序为 TR1[s..t]
void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE + 1];
    if(s == t) {
        TR1[s] = SR[s];
    }else{
        m = (s+t)/2;    // 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
        MSort(SR, TR2, s, m);   //递归将SR[s..m]归并为有序的TR2[s..m]
        MSort(SR,TR2,m+1,t);     //递归将SR[m+1..t]归并为有序TR2[m+1..t]
        Merge(TR2,TR1,s,m,t);   //将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
    }
}

//归并排序
void MergeSort(SqList *L)
{
    MSort(L->r, L->r, 1, L->length);
}

/* 归并排序算法的迭代实现 */

//将SR[]中相邻长度为 s 的子序列两两归并到 TR[]
void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while ( i <= n-2*s-1) { //s 其实就是步长
        Merge(SR, TR, i, i+s-1, i+2*s-1);   //两两归并
        i = i+2*s;
    }

    if( i < n-s+1) {        //归并最后两个序列
        Merge(SR, TR, i, i+s-1, n);
    }else{                  //若最后只剩下单个子序列
        for(j = i; j <= n; j++) {
            TR[j] = SR[j];
        }
    }
}

// 非递归算法归并排序
void MergeSort2(SqList *L)
{
    int *TR = (int *)malloc(L->length * sizeof(int));   //申请额外空间
    int k = 1;
    while(k < L->length)
    {
        MergePass(L->r, TR, k, L->length);  
        k = 2*k;    //子序列长度加倍
        MergePass(TR, L->r, k, L->length);
        k = 2*k;    //子序列长度加倍
    }
}

/***************************************************************/
/* 快速排序算法 */
/* 时间复杂度： O(n * logn) */
/***************************************************************/

//交换顺序表 L 中子表的记录，使枢轴记录到位，并返回其所在位置 
//此时在它之前（后）的记录均不大（小）于它
int Partition(SqList *L, int low, int high)
{
    int pivotkey;

    pivotkey = L->r[low];   //用子表的第一个记录作枢轴记录
    while( low < high ) {   //从表的
        while(low < high && L->r[high] >= pivotkey) {
            high--;
        }
        swap(L, low, high); //将比枢轴记录小的记录交换到低端
        while(low < high && L->r[low] <= pivotkey) {
            low++;
        }
        swap(L, low, high); //将枢轴记录大的记录交换到高端
    }
    return low; //返回枢轴所在位置
}

/* 对顺序表 L 中的子序列 L->r[low..high] 作快速排序 */
void QSort( SqList *L, int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = Partition(L, low, high);        //将L->r[low..high]一分为二
                                                //算出枢轴值piovt
        QSort(L, low, pivot-1) ;        //对低子表递归排序
        QSort(L, pivot+1, high);        //对高子表递归排序
    }
}

/* 优化的快速排序算法 */

//快速排序算法优化
int Partition1(SqList *L, int low, int high)
{
    int pivotkey;

    //优化枢轴的选取 三数取中，此段代码为优化部分
    int m = low + (high - low) / 2; //计算数组中间的元素的下标
    if(L->r[low] > L->r[high])
        swap(L,low,high);
    if(L->r[m] > L->r[high])
        swap(L,high,m);
    if(L->r[m] > L->r[low])
        swap(L,m,low);
    //此时L.row[low]已经成为整个序列左中右三个关键字的中间值

    pivotkey = L->r[low];   //用子表的第一个记录作枢轴记录

    L->r[0] = pivotkey;     //将枢轴关键字备份到L->r[0]

    while( low < high ) {   //从表的
        while(low < high && L->r[high] >= pivotkey) {
            high--;
        }
        L->r[low] = L->r[high]; //采用替换而不是交换的方式，将比枢轴记录小的记录交换到低端
        while(low < high && L->r[low] <= pivotkey) {
            low++;
        }
        L->r[high] = L->r[low]; //采用替换而不是交换的方式，将枢轴记录大的记录交换到高端
    }
    L->r[low] = L->r[0];    //将枢轴数值替换回L.r[low]
    return low; //返回枢轴所在位置
}

#define MAX_LENGTH_INSERT_SORT 7    //数组长度阀值
// 对顺序表 L 中的子序列 L.r[low..high]作快速排序 
void QSort1( SqList *L, int low, int high)
{
    int pivot;
    if( (high-low)>MAX_LENGTH_INSERT_SORT) {        //当 high - low 大于常数时用快速排序
        while(low < high)
        {
            pivot = Partition1(L, low, high);        //将L->r[low..high]一分为二
                                                    //算出枢轴值piovt
            QSort(L, low, pivot-1) ;        //对低子表递归排序
            QSort(L, pivot+1, high);        //对高子表递归排序
            low = pivot +1;
        }
    } else {   // 当high - low 小于等于常数时用直接插入排序
        InsertSort(L);
    }
}

// 快速排序算法
void QuickSort(SqList *L) 
{
    QSort(L, 1, L->length);
}

int main()
{
    SqList L;

    //初始化
    InitSqList(&L);
    PrintSqList(L);

    //冒泡排序初级
    // printf("初级冒泡排序结果:\n");
    // BubbleSort(&L);
    // PrintSqList(L);

    //冒泡排序
    printf("冒泡排序结果:\n");
    BubbleSort(&L);
    PrintSqList(L);

    //冒泡排序优化
    // printf("优化冒泡排序结果:\n");
    // BubbleSort2(&L);
    // PrintSqList(L);

    //简单选择排序
    printf("简单选择排序结果:\n");
    SelectSort(&L);
    PrintSqList(L);

    //直接插入排序
    printf("直接插入排序结果:\n");
    InsertSort(&L);
    PrintSqList(L);
    
    //希尔排序
    printf("希尔排序结果:\n");
    ShellSort(&L);
    PrintSqList(L);

    //堆排序
    printf("堆排序结果:\n");
    HeapSort(&L);
    PrintSqList(L);

    //递归归并排序
    printf("递归归并排序结果:\n");
    MergeSort(&L);
    PrintSqList(L);

    //迭代归并排序
    printf("迭代归并排序序结果:\n");
    MergeSort2(&L);
    PrintSqList(L);

    //快速排序
    printf("快速排序结果:\n");
    QuickSort(&L);
    PrintSqList(L);

    return 0;
}