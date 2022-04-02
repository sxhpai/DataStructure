/********************** �������ص�д�� ****************************/
/******************** ���ص�ģʽƥ���㷨 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********* д��һ *********/
//�ַ�����ĵ�0λ���ڴ洢�ô��ĳ���
int IndexDa(char *mainstr, char * substr, int pos) {
	int i = pos;	//i ��������mainstr�ĵ�ǰ�±�ֵ��
					//pos��ʾ��������posλ�ÿ�ʼƥ��
	int j = 1;		//j �����Ӵ�substr�ĵ�ǰ���±�ֵ��
	while (i <= mainstr[0] && j <= substr[0]) {//��iС�ڵ��������ĳ��� �� jС�ڵ����Ӵ��ĳ��� �����
		if (mainstr[i] == substr[j]) {	//����ĸ��������
			i++;
			j++;
		}
		else {
			//i �˻ص��ϴ�ƥ����λ����һλ
			i = i - j + 2;// ��������д����i = 1 + (i-j) + 1;
			//j �˻ص��Ӵ�����λ
			j = 1;
		}
	}

	if (j > substr[0]) {
		return i - substr[0];	//�����Ӵ��������е��±�ֵ���͵ڼ���Ԫ��һ����
	}
	return 0;
}

/********* д���� *********/
//�ַ�����ĳ�����Ҫ�������뺯��
int IndexYan(char *mainstr, int mainlen, char *substr, int sublen) {
	int i = 0;
	int j = 0;
	while (i < mainlen && j < sublen) {
		if (mainstr[i] == substr[j]) {
			i++;
			j++;
		}
		else
		{
			//i �˻ص��ϴ�ƥ����λ����һλ
			i = i - j + 1;
			//j �˻ص��Ӵ�����λ
			j = 0;
		}
	}

	if (j == sublen) {
		return i - sublen;	//�����Ӵ��������е��±�ֵ
	}
	return 0;
}


int main() {

	//�����ݽṹ��д��
	char str1[] = "0sunxinghuixinghui";
	char str2[] = "0xing";
	str1[0] = strlen(str1) - 1;
	str2[0] = strlen(str2) - 1;
	int num1 = IndexDa(str1, str2,11);
	printf(" %d\n", num1);

	//�ϳ�����д��
	char str3[] = "sunsunxinghui";
	char str4[] = "xing";
	int num2 = IndexYan(str3, strlen(str3), str4, strlen(str4));
	printf(" %d\n", num2);

	return 0;
}
