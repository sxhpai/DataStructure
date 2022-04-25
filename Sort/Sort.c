/************** �߸������㷨 *****************/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAXSIZE 10          // ����Ҫ��������������ֵ���ɸ�����Ҫ�޸�

typedef int Status;

typedef struct {
    int r[MAXSIZE + 1];     // ���ڴ洢Ҫ�������飬r[0]�����ڱ�����ʱ����
    int length;             // ���ڼ�¼˳�����
}SqList;

/* ���� L ������ r ���±�Ϊ i �� j ��ֵ */
void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

//˳����ʼ��
void InitSqList(SqList *L)
{
    int i;
    int temp[11] = {0,9,1,5,8,3,7,4,6,2,10};
    for( i = 1; i <= 10; i++) {
        L->r[i] = temp[i];
    }
    L->length = MAXSIZE;
}

//��ӡ˳���
void PrintSqList(SqList L)
{
    int i;
    for( i = 1; i<=10; i++) {
        printf(" %d",L.r[i]);
    }
    printf("\n");
}
/***************************************************************/
/* ð������������㷨 */
/* ʱ�临�Ӷȣ� O(n^2) */
/***************************************************************/
void BubbleSort0(SqList *L)
{
    int i,j;
    for ( i = 1; i < L->length; i++ ) {
        for( j = i + 1; j <= L->length; j++ ) {
            if( L->r[i] > L->r[j]) {    //��С��������
                swap(L, i, j);
            }
            // if( L->r[i] < L->r[j]) {    //�Ӵ�С����
            //     swap(L, i, j);
            // }
        }
    }
}

/***************************************************************/
/* ð�������㷨 */
/* ʱ�临�Ӷȣ� O(n^2) */
/***************************************************************/
void BubbleSort(SqList *L)
{
    int i, j;
    for(i = 1; i < L->length; i++) {
        for(j = L->length; j > i; j--) {
            if(L->r[j] < L->r[j-1]) { //������ı�ǰ���С���򽻻�
                swap(L, j, j-1);
            }
        }
    }
}

/***************************************************************/
/* ð�������Ż��㷨 */
/* ʱ�临�Ӷȣ� O(n^2) */
/***************************************************************/
void BubbleSort2(SqList *L)
{
    int i,j;
    Status flag = TRUE;     //����ѭ��Ϊ��
    for(i = 1; i < L->length && flag; i++) {
        flag = FALSE;                   //ÿһ�ֳ�ʼ��ΪFALSE
        for(j = L->length; j > i; j--) {
            if(L->r[j] < L->r[j - 1]) { //������ı�ǰ���С���򽻻�
                swap( L, j, j - 1);
                flag = TRUE;            //��������ݽ�������flag��ΪTRUE
                                        /* ��û�����ݽ�����˵���������Ѿ��ź��򣬲���Ҫ����ѭ�� */
            }
        }
    }
}

/***************************************************************/
/* ��ѡ�������㷨 */
/* ʱ�临�Ӷȣ� O(n^2) */
/***************************************************************/
void SelectSort(SqList *L)
{//���ҵ���⣺ð�������������Ż������ǲ������ˣ��Ż�Ϊÿ�ּ�¼��Сֵ�������ֵ�����±꣬��һ��ѭ��������ֻ�ý���һ�ξ��С���
    int i,j,min;
    for (i = 1; i < L->length; i++) {
        min = i;                                //����ǰ�±궨��Ϊ��Сֵ�±�
        for (j = i+1; j <= L->length; j++) {    //ѭ��֮�������
            if (L->r[j] < L->r[min]) {          //�����С�ڵ�ǰ��Сֵ�Ĺؼ���
                min = j;                        //���˹ؼ��ֵ��±긳ֵ�� min
            }
        }           
        if(i != min) {                          //�� min ������ i��˵���ҵ���Сֵ���򽻻����ߵ�ֵ
            swap(L, min, i);
        }
    }
}

/***************************************************************/
/* ֱ�Ӳ��������㷨 */
/* ʱ�临�Ӷȣ� O(n^2) */
/***************************************************************/
void InsertSort(SqList *L)
{
    int i,j;
    for (i = 2; i <= L->length; i++) {  
        if (L->r[i] < L->r[i-1]) {          //�������С��ǰ�棬����Ҫ�� L->r[i] ���뵽�����
            L->r[0] = L->r[i];              //��������ı��浽r[0]
            for(j = i-1; L->r[j] > L->r[0]; j--) {
                L->r[j+1] = L->r[j];        //��¼����
            }
            L->r[j+1] = L->r[0];            //������ȷ��λ��
        }
    }
}

/***************************************************************/
/* ϣ�������㷨 */
/* ʱ�临�Ӷȣ� O(n^(3/2)) */
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
                //��Ҫ��L->r[i]��������������
                L->r[0] = L->r[i];                  //�ݴ��� L->r[0]
                for(j = i-increment; j > 0 && L->r[0] < L->r[j]; j -= increment) {
                    L->r[j+increment] = L->r[j];    //��¼���ƣ����Ҳ���λ��
                }
                L->r[j+increment] = L->r[0];        //����
            }
        }
    } while (increment > 1);
}

/***************************************************************/
/* �������㷨 */
/* ʱ�临�Ӷȣ� O(n * logn) */
/***************************************************************/

/* ��֪ L->[s..m] �м�¼�Ĺؼ��ֳ� L->r[s] ֮�������ѵĶ��� */
/* ���������� L->r[s] �Ĺؼ��֣�ʹ L->r[s..m] ��Ϊ һ���󶥶� */
void HeapAdjust(SqList *L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    for (j = 2 * s; j <= m; j *= 2) {           //���Źؼ��ֽϴ�ĺ��ӽ������ɸѡ
        if(j < m && L->r[j] < L->r[j+1]) {
            ++j;                                // j Ϊ�ؼ��ֽϴ�ļ�¼���±�
        }
        if(temp >= L->r[j]) {
            break;                              // rc Ӧ������λ�� s ��
        }   
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

/* �������㷨 */
void HeapSort(SqList *L)
{
    int i;
    for (i = L->length/2; i > 0; i--) { //�� L �е� r ������һ���󶥶�
        HeapAdjust(L,i,L->length);
    }

    for (i = L->length; i > 1; i--) {
        swap(L, 1, i);          //���Ѷ���¼�͵�ǰδ�����������е����һ����¼����
        HeapAdjust(L, 1, i-1);  //�� L->r[1...i-1]���µ���Ϊ�󶥶�
    }
}

/***************************************************************/
/* �鲢�����㷨 */
/* ʱ�临�Ӷȣ� O(n * logn) */
/***************************************************************/

/* �鲢�����㷨�ĵݹ�ʵ�� */
//�������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
void Merge(int SR[], int TR[], int i, int m, int n)     //�鲢����ĺ��Ĵ���
{
    int j,k,l;
    // i Ϊ SR[i..m]���±ꣻ j Ϊ SR[m+1..n]���±�
    j = m + 1;
    for (k = i; i <= m && j <= n; k++) {   //�� SR �м�¼��С����鲢�� TR
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
// �� SR[s..t] �鲢����Ϊ TR1[s..t]
void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE + 1];
    if(s == t) {
        TR1[s] = SR[s];
    }else{
        m = (s+t)/2;    // ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
        MSort(SR, TR2, s, m);   //�ݹ齫SR[s..m]�鲢Ϊ�����TR2[s..m]
        MSort(SR,TR2,m+1,t);     //�ݹ齫SR[m+1..t]�鲢Ϊ����TR2[m+1..t]
        Merge(TR2,TR1,s,m,t);   //��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
    }
}

//�鲢����
void MergeSort(SqList *L)
{
    MSort(L->r, L->r, 1, L->length);
}

/* �鲢�����㷨�ĵ���ʵ�� */

//��SR[]�����ڳ���Ϊ s �������������鲢�� TR[]
void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while ( i <= n-2*s-1) { //s ��ʵ���ǲ���
        Merge(SR, TR, i, i+s-1, i+2*s-1);   //�����鲢
        i = i+2*s;
    }

    if( i < n-s+1) {        //�鲢�����������
        Merge(SR, TR, i, i+s-1, n);
    }else{                  //�����ֻʣ�µ���������
        for(j = i; j <= n; j++) {
            TR[j] = SR[j];
        }
    }
}

// �ǵݹ��㷨�鲢����
void MergeSort2(SqList *L)
{
    int *TR = (int *)malloc(L->length * sizeof(int));   //�������ռ�
    int k = 1;
    while(k < L->length)
    {
        MergePass(L->r, TR, k, L->length);  
        k = 2*k;    //�����г��ȼӱ�
        MergePass(TR, L->r, k, L->length);
        k = 2*k;    //�����г��ȼӱ�
    }
}

/***************************************************************/
/* ���������㷨 */
/* ʱ�临�Ӷȣ� O(n * logn) */
/***************************************************************/

//����˳��� L ���ӱ�ļ�¼��ʹ�����¼��λ��������������λ�� 
//��ʱ����֮ǰ���󣩵ļ�¼������С������
int Partition(SqList *L, int low, int high)
{
    int pivotkey;

    pivotkey = L->r[low];   //���ӱ�ĵ�һ����¼�������¼
    while( low < high ) {   //�ӱ��
        while(low < high && L->r[high] >= pivotkey) {
            high--;
        }
        swap(L, low, high); //���������¼С�ļ�¼�������Ͷ�
        while(low < high && L->r[low] <= pivotkey) {
            low++;
        }
        swap(L, low, high); //�������¼��ļ�¼�������߶�
    }
    return low; //������������λ��
}

/* ��˳��� L �е������� L->r[low..high] ���������� */
void QSort( SqList *L, int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = Partition(L, low, high);        //��L->r[low..high]һ��Ϊ��
                                                //�������ֵpiovt
        QSort(L, low, pivot-1) ;        //�Ե��ӱ�ݹ�����
        QSort(L, pivot+1, high);        //�Ը��ӱ�ݹ�����
    }
}

/* �Ż��Ŀ��������㷨 */

//���������㷨�Ż�
int Partition1(SqList *L, int low, int high)
{
    int pivotkey;

    //�Ż������ѡȡ ����ȡ�У��˶δ���Ϊ�Ż�����
    int m = low + (high - low) / 2; //���������м��Ԫ�ص��±�
    if(L->r[low] > L->r[high])
        swap(L,low,high);
    if(L->r[m] > L->r[high])
        swap(L,high,m);
    if(L->r[m] > L->r[low])
        swap(L,m,low);
    //��ʱL.row[low]�Ѿ���Ϊ�������������������ؼ��ֵ��м�ֵ

    pivotkey = L->r[low];   //���ӱ�ĵ�һ����¼�������¼

    L->r[0] = pivotkey;     //������ؼ��ֱ��ݵ�L->r[0]

    while( low < high ) {   //�ӱ��
        while(low < high && L->r[high] >= pivotkey) {
            high--;
        }
        L->r[low] = L->r[high]; //�����滻�����ǽ����ķ�ʽ�����������¼С�ļ�¼�������Ͷ�
        while(low < high && L->r[low] <= pivotkey) {
            low++;
        }
        L->r[high] = L->r[low]; //�����滻�����ǽ����ķ�ʽ���������¼��ļ�¼�������߶�
    }
    L->r[low] = L->r[0];    //��������ֵ�滻��L.r[low]
    return low; //������������λ��
}

#define MAX_LENGTH_INSERT_SORT 7    //���鳤�ȷ�ֵ
// ��˳��� L �е������� L.r[low..high]���������� 
void QSort1( SqList *L, int low, int high)
{
    int pivot;
    if( (high-low)>MAX_LENGTH_INSERT_SORT) {        //�� high - low ���ڳ���ʱ�ÿ�������
        while(low < high)
        {
            pivot = Partition1(L, low, high);        //��L->r[low..high]һ��Ϊ��
                                                    //�������ֵpiovt
            QSort(L, low, pivot-1) ;        //�Ե��ӱ�ݹ�����
            QSort(L, pivot+1, high);        //�Ը��ӱ�ݹ�����
            low = pivot +1;
        }
    } else {   // ��high - low С�ڵ��ڳ���ʱ��ֱ�Ӳ�������
        InsertSort(L);
    }
}

// ���������㷨
void QuickSort(SqList *L) 
{
    QSort(L, 1, L->length);
}

int main()
{
    SqList L;

    //��ʼ��
    InitSqList(&L);
    PrintSqList(L);

    //ð���������
    // printf("����ð��������:\n");
    // BubbleSort(&L);
    // PrintSqList(L);

    //ð������
    printf("ð��������:\n");
    BubbleSort(&L);
    PrintSqList(L);

    //ð�������Ż�
    // printf("�Ż�ð��������:\n");
    // BubbleSort2(&L);
    // PrintSqList(L);

    //��ѡ������
    printf("��ѡ��������:\n");
    SelectSort(&L);
    PrintSqList(L);

    //ֱ�Ӳ�������
    printf("ֱ�Ӳ���������:\n");
    InsertSort(&L);
    PrintSqList(L);
    
    //ϣ������
    printf("ϣ��������:\n");
    ShellSort(&L);
    PrintSqList(L);

    //������
    printf("��������:\n");
    HeapSort(&L);
    PrintSqList(L);

    //�ݹ�鲢����
    printf("�ݹ�鲢������:\n");
    MergeSort(&L);
    PrintSqList(L);

    //�����鲢����
    printf("�����鲢��������:\n");
    MergeSort2(&L);
    PrintSqList(L);

    //��������
    printf("����������:\n");
    QuickSort(&L);
    PrintSqList(L);

    return 0;
}