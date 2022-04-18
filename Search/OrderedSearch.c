
/**************** ��̬���� ***************/
/*************** �������� **************/
#include <stdio.h>

//���ֲ���
//aΪ���飬nΪnҪ���ҵ�������Ч���ȣ���a[1]��ʼ��a[n]�����ĳ��ȣ���keyΪҪ��ѯ�Ĺؼ���
/******************* ʱ�临�Ӷ�: O(logn)****************/
int Binary_Search(int *a, int n, int key) 
{
    int low,high,mid;
    low = 1;            //��������±�Ϊ��¼��λ
    high = n;           //��������±�Ϊ��¼ĩλ

    //��ѯ
    while(low <= high) {
        mid = (low + high)/2;   //����
        if (key < a[mid]) {     //������ֵ����ֵС
            high = mid - 1;     //����±��������λ�±�Сһλ
        }else if (key > a[mid]) {  //������ֵ����ֵ��
            low = mid + 1;      //����±��������λ�±��һλ
        }else {
            return mid;         //�������˵�� mid ��Ϊ���ҵ���λ��
        }
    }
    return 0;
}

//��ֵ���ң����ֲ��ҵ��Ż�
//aΪ���飬nΪnҪ���ҵ�������Ч���ȣ���a[1]��ʼ��a[n]�����ĳ��ȣ���keyΪҪ��ѯ�Ĺؼ���
/******************* ʱ�临�Ӷ�: O(logn)****************/
int Interpolation_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;
    high = n;

    //��ѯ
    while( low <= high ) {
        // mid = (low + high)/2;
        mid = low + (high - low)*(key - a[low])/(a[high] - a[low]);/**** ��ֵ��ʽ****/
        
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

//쳲��������ң����ֲ��ҵ��Ż�
//aΪ���飬nΪnҪ���ҵ�������Ч���ȣ���a[1]��ʼ��a[n]�����ĳ��ȣ���keyΪҪ��ѯ�Ĺؼ���
/******************* ʱ�临�Ӷ�: O(logn)****************/
int F[] = {0,1,1,2,3,5,8,13,21,34,55,89};   //����һ��쳲���������

int Fibonacci_Search(int *a, int n, int key) 
{
    int low, high, mid, i, k;
    low = 1;                        //��������±�Ϊ��¼��λ
    high = n;                       //��������±�Ϊ��¼ĩλ
    k = 0;                  
    while (n > F[k] - 1) {          //���� n λ��쳲��������е�λ��
        k++;
    }
    for ( i = n; i < F[k] - 1; i++) {   //����������ֵ��ȫ
        a[i] = a[n];
    }

    //��ѯ
    while(low <= high) {
        mid = low + F[k - 1] - 1;       //���㵱ǰ�ָ����±�
        if (key < a[mid]) {
            high = mid - 1;     //����±�������ָ��±� mid-1 ��
            k = k - 1;          //쳲����������±��һλ
        }else if (key > a[mid]) {
            low = mid + 1;      //���λ�±�������ָ��� mid=1 ��
            k = k - 2;          //쳲����������±����λ
        }else {
            if (mid <= n) {
                return mid;     //�������˵�� mid ��Ϊ���ҵ���λ��
            }else {
                return n;       //�� mid>n ˵���ǲ�ȫ��ֵ������ n
            }
        }
    }
    return 0;
}

//������
int main()
{
    int a[] = {0,1,2,3,4,5,6,7,8,9,10,11};  //a[0]:��Чֵ; ��Чֵ��a[1]��ʼ��
    int length = sizeof(a)/sizeof(int) - 1; //���ȴ� a[1] ��ʼ
    printf(" length = %d\n",length);

    printf(" Binary_Search = %d\n", Binary_Search(a, length, 7));
    printf(" Interpolation_Search = %d\n", Interpolation_Search(a,length, 8));
    printf(" Fibonacci_Search = %d\n",Fibonacci_Search(a,length, 6));

    return 0;
}