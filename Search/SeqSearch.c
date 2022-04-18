/**************** ��̬���� ***************/
/**************** ˳����� ***************/

#include <stdio.h>

/*˳����ң�aΪ���飬nΪҪ���ҵ����鳤�ȣ�keyΪҪ���ҵĹؼ���*/
/************** ʱ�临�Ӷ�: O(n) *****************/
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

/*���ڱ���˳�����*/
/************** ʱ�临�Ӷ�: O(n) *****************/
int Sequential_Search2(int *a, int n, int key)
{
    int i = n; 
    a[0] = key;
    while(a[i] != key) {
        i--;
    }
    return i;
}

/*���ڱ���˳����� 2 */
/************** ʱ�临�Ӷ�: O(n) *****************/
int Sequential_Search3(int *a, int n, int key)
{
    int i = 0;
    a[n] = key;
    while(a[i] != key) {
        i++;
    }
    return i;   //���� n ˵������ʧ�ܣ�����0 ~ n-1 ˵�����ҳɹ�
}
int main() {

    int a[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
    int length = sizeof(a)/sizeof(int);
    
    printf(" search1 = %d\n",Sequential_Search(a,length,7));
    printf(" search2 = %d\n",Sequential_Search2(a,length,8));
    printf(" search3 = %d\n",Sequential_Search3(a,length,1));

    return 0;
}