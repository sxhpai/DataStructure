/***************** ���ص�ģʽƥ���㷨 ******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LinkNum 3	//ȫ�����������нڵ�洢���ݵĸ���
#define ERROR -1
#define OK 1

typedef int Status;

//�����Ӵ�subString������mainSring�е�pos���ַ�֮���λ�á����������򷵻�ֵΪ0�� 
int Index(char * mainString, int mainLen ,char *subString, int subLen) {
	int i = 0,j = 0;
	//����ѭ�����ֿ��ܣ�i=mainLen˵���Ѿ�������������j=subLen˵���Ӵ��������
	while (i < mainLen && j < subLen) {
		if (mainString[i] == subString[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	//�ж�ƥ���Ƿ�ɹ�
	if (j == subLen) {
		return i - j + 1;	//���������ĵڼ���λ��
		//return i - j;		//�����������±�
	}
	//ƥ��ʧ�ܷ���0
	return 0;
}

int main() {

	char str1[] = "I am a dog!";
	char str2[] = "dog";

	int num = Index(str1, strlen(str1), str2, strlen(str2));

	printf("Index = %d", num);

	return 0;
}
