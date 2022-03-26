/**************************************
****************��̬����***************
***************************************/

/*--------------����˵��----------------*/
//�������±�Ϊ0��Ԫ����Ϊ���������	   ͷ��㣬��dataΪ�գ���cur��ŵ�һ�����ý����±�
//�������±�Ϊ1��Ԫ����Ϊ������������ͷ��㣬��dataΪ�գ���cur��ŵ�һ��������ݵĽ����±�

/*--------------֪ʶ������----------------*/
//ͷ���λ�õ�ѡȡҲ��������
//���ṹ������ĵ�һ��Ԫ�أ������±�Ϊ0��Ԫ�أ�����Ϊ���������ͷ���
//���ṹ����������һ��Ԫ�أ���Ϊ���������ͷ���

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define OK 1
#define MaxSize 100

typedef int Status;	
typedef int ElemType;

//��̬������
typedef struct {
	ElemType data;	//����
	int cur;	//�α�
}component;

//�ṹ�������ʼ��Ϊ��������
void reserveArr(component *array);

//�ӱ�������Ϊ�����������ռ�
int mallocArr(component *array);

//����������տգ�����arrayΪ�洢�������ݵ����飬k��ʾδʹ�ý�����ڵ������±�
void freeArr(component *array, int k);

//��ʼ����̬����
int initArr(component *array);

//�������
//����������ھ�̬����array�ĵ�n��Ԫ����ǰ��������Ԫ��e
Status insertArr(component *array, int head, int n, int e);

//ɾ������
//���������ɾ����̬�����n��Ԫ��
Status deleteArr(component *array, int head, int n);

//��ѯ����
//�����������ͷ����±�Ϊhead�������У���ѯ������Ϊelem�Ľ���������е�λ��,������
int selectElem(component *array, int head, int elem);

//�޸Ĳ���
//
Status amendElem(component *array, int head, int oldElem, int newElem);

//��ӡ��̬��������������
//���������arrayΪ�ṹ������׵�ַ��headΪ��̬����ͷ�����±�
void displayArr(component *array, int head);

//������
int main() {
	component SLL[MaxSize];

	//��ʼ����̬����
	int head = initArr(SLL);
	displayArr(SLL, head);

	//�������
	insertArr(SLL, head, 1, 44);
	displayArr(SLL, head);

	//ɾ������
	deleteArr(SLL, head, 1);
	displayArr(SLL, head);

	//��ѯ����
	int s = selectElem(SLL, head,8);
	printf(" %d\n", s);


	return 0;
}


//�ṹ�������ʼ��Ϊ��������
void reserveArr(component *array) {
	for (int i = 0; i < MaxSize; i++) {
		array[i].data = -1;		//��������ÿ���������ݶ�Ϊ-1
		array[i].cur = i + 1;	//��������ÿ�������α궼ָ����һ�����
	}
	array[MaxSize - 1].cur = 0;	//������������һ�������α�ֵΪ0����ʾ����Ľ���
}

//�ӱ�������Ϊ�����������ռ�
int mallocArr(component *array) {
	int i = array[0].cur;	//ȡ�ñ�������ͷ�����α꣬������Ҫ��������±꣩
	if (array[0].cur) {
		//���ͷ�����α겻��0��˵������ɹ������������ͷ���Ҫָ����һ�����ý��
		array[0].cur = array[i].cur;
	}
	return i;	//����Ҫ��������±�
}

//����������տգ�����arrayΪ�洢�������ݵ����飬k��ʾδʹ�ý�����ڵ������±�
void freeArr(component *array, int k) {
	array[k].cur = array[0].cur;
	array[0].cur = k;
}

//��ʼ����̬����
int initArr(component *array) {
	//1.�����鱸������
	reserveArr(array);
	//2.Ϊ��������ķ���ͷ���
	int head = mallocArr(array);	//Ϊ��������ͷ������ռ䲢ȡ���±�
	//3.��ʼ����̬����
	int temp = head;	//��ʱ����ȡ��ͷ�����±�
	for (int i = 1; i < 9; i++) {	/*-----��һ��ѭ���Ķ���ע��----*/
		int j = mallocArr(array);	//Ϊ��������ĵ�һ��������ռ䲢ȡ���±�
		array[temp].cur = j;		//��ͷ���ָ���һ�����
		array[j].data = i;			//Ϊ��һ���������ݸ�ֵ
		temp = j;					//tempȡ�õ�һ������±꣬����
	}
	array[temp].cur = 0;			//��������������һ�����ĸ�ֵΪ0����ʾ��������Ľ�����
	//4.����ͷ�����±�
	return head;
}

//�������
//����������ھ�̬����array�ĵ�n��Ԫ����ǰ��������Ԫ��e
Status insertArr(component *array, int head, int n, int e) {
	int temp = head;	//��ʱ����ȡ��ͷ�����±�

	//1.�ҵ�Ҫ����λ�õ�ǰһ�������±�
	for (int i = 1; i < n; i++) {
		temp = array[temp].cur;
	}

	//2.�����½ڵ�
	int newElem = mallocArr(array);	//newElemΪ�½����±�
	if (!newElem) {
		printf("����ռ�ʧ��");
		return ERROR;
	}
	array[newElem].data = e;

	//3.�������
	array[newElem].cur = array[temp].cur;
	array[temp].cur = newElem;

	return OK;
}

//ɾ������
//���������ɾ����̬�����n��Ԫ��
Status deleteArr(component *array, int head, int n) {
	int temp = head;	//��ʱ����ȡ��ͷ�����±�

	//1.�ҵ�Ҫɾ��Ԫ�ص���һ�������±�
	for (int i = 0; i < n; i++) {
		temp = array[temp].cur;
	}

	//2.ɾ������
	int del = array[temp].cur;
	array[temp].cur = array[del].cur;
	freeArr(array, del);			//���ò����Ľ���������뱸������
	return OK;
}

//��ѯ����
//�����������ͷ����±�Ϊhead�������У���ѯ������Ϊelem�Ľ���������е�λ��,������
int selectElem(component *array, int head, int elem) {
	int temp = head;
	//0.���α�ֵΪ0ʱ����ʾ���������ѭ������
	while (array[temp].cur != 0) {
		if (array[temp].data == elem) {
			return temp;
		}
		temp = array[temp].cur;
	}
	//���һ��Ԫ��
	if (array[temp].data == elem) {
		return temp;
	}
	return -1;	//����-1����ʾ��������û���ҵ���Ԫ��
}

//�޸Ĳ���
//�����������headΪͷ�ľ�̬����array��������ΪoldElem������Ԫ�أ�����������ΪnewElem
Status amendElem(component *array, int head, int oldElem, int newElem) {
	int temp = head;;
	//0.���α�ֵΪ0ʱ����ʾ�������
	while (array[temp].cur != 0) {
		if (array[temp].data == oldElem) {
			array[temp].data = newElem;
			return OK;
		}
		temp = array[temp].cur;
	}
	//���һ��Ԫ��
	if (array[temp].data == oldElem) {
		array[temp].data = newElem;
		return OK;
	}
	return ERROR;
}

//��ӡ��̬��������������
//���������arrayΪ�ṹ������׵�ַ��headΪ��̬����ͷ�����±�
void displayArr(component *array, int head) {
	int temp = head;			//�����������ͷ��㿪ʼ���
	//int temp = array[head].cur;	//����������ĵ�һ����㿪ʼ���
	while (array[temp].cur)
	{
		printf(" %d %d,", array[temp].data, array[temp].cur);
		temp = array[temp].cur;
	}
	printf(" %d %d, ", array[temp].data, array[temp].cur);

	printf("\n");
}
