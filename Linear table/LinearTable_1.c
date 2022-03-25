
/****************************************************
------------------���Ա�˳��洢�ṹ----------------
----------------------��������----------------------
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1	
#define OK 1

typedef int Status;		//����״̬����ֵ�Ǻ������״̬����

//˳���ĳ�ʼ���� 
#define Size 5

//�Զ���˳���
typedef struct SqList {
	int *data;		//�洢�ռ����ʼ��ַ,����һ�����Ȳ�ȷ�������� 
	int length;		//��ǰ˳���ĳ���
	int size;		//��ǰ˳���Ĵ洢���� 
}SqList;

//˳����ʼ��
Status InitSqList(SqList *L) {
	//��̬����洢�ռ� ������һ���յ�˳��� 
	L->data = (int *)malloc(Size * sizeof(int));
	if (!L->data) {
		//��������ڴ�ʧ�ܣ�������ʾ��ֱ���˳�����
		printf("��ʼ��ʧ��");
		return ERROR;
	}

	L->length = 0;
	L->size = Size;
}

//˳���������
Status ListInsert(SqList *L, int n, int Elem)
{
	//�жϲ��뱾���Ƿ��������
	if (n < 0 || n > L->length) {
		printf("�����λ�ó���\n");
		return ERROR;
	}

	//���������ʱ��������Ҫ��˳����Ƿ��ж���Ĵ洢�ռ��ṩ�������Ԫ�أ����û�У���Ҫ����
	if (L->length == L->size) {
		L->data = (int *)realloc(L->data, (L->size + 1) * sizeof(int));
		if (!L->data) {
			printf("�洢�ռ����ʧ��\n");
			return ERROR;
		}
		L->size++;
	}

	//�����������Ҫ���Ӳ���λ�ÿ�ʼ�ĺ���Ԫ�أ��������
	for (int i = L->length - 1; i >= n; i--) {
		L->data[i + 1] = L->data[i];
	}
	L->data[n] = Elem;
	L->length++;
	return OK;
}

//˳���ɾ������
Status ListDelete(SqList *L, int n)
{
	//�ж�ɾ�������Ƿ��������
	if (n < 0 || n >= L->length) {
		printf("ɾ����λ�ó���\n");
		return ERROR;
	}
	//ɾ������
	for (int i = n; i < L->length; i++) {
		L->data[i] = L->data[i + 1];
	}
	L->length--;
	return OK;
}

//���ҵ�n��Ԫ�أ������ظ�e
Status GetElem(SqList L, int n, int *e)
{
	if (n < 0 || n > L.length) {
		return ERROR;
	}
	*e = L.data[n];
	return OK;
}

//���Һ�Ԫ��eһ����Ԫ�أ�����λ�÷��ظ�n
Status LocateElem(SqList L, int *n, int e)
{
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == e) {
			*n = i;
			return OK;
		}
	}
	*n = -1;
	return ERROR;
}

//˳�����ʾ
void DisplaySqList(SqList *L) {
	for (int i = 0; i < L->length; i++) {
		printf(" %d", L->data[i]);
	}
	printf("\n");
}


int main() {
	//����һ��˳���
	SqList List;
	int e, n;

	//��ʼ��˳�������ֵ
	InitSqList(&List);
	for (int i = 0; i < List.size; i++) {
		List.data[i] = i + 1;
		List.length++;
	}
	DisplaySqList(&List);

	//�������
	ListInsert(&List, 10, 9);
	DisplaySqList(&List);

	//ɾ������
	ListDelete(&List, 10);
	DisplaySqList(&List);

	//��ѯ����
	GetElem(List, 0, &e);
	printf(" %d\n", e);
	LocateElem(List, &n, 1);
	printf(" %d\n", n);

	return 0;
}
