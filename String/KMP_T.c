/********************* KMP�㷨 ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//�����Ӵ� str �� next����
void get_next(char *str, int *next) {

	int i = 1;	
	int j = 0;	
	next[1] = 0;
	while (i < str[0]) {
		if (j == 0 || str[i] == str[j]) {	//str[i] ��ʾ��׺�ĵ����ַ�
			i++;							//str[j] ��ʾǰ׺�ĵ����ַ�
			j++;
			next[i] = j;
		}
		else {
			j = next[j];	//jֵ����
		}
	}
}

//�����Ӵ� str �� nextval����
void get_nextval(char *str, int *nextval) {
	int i = 1;
	int j = 0;
	nextval[1] = 0;
	while (i < str[0]) {	//�˴�str[0]����str����Ч����
		if (j == 0 || str[i] == str[j]) {	//str[i]��ʾ��׺�ĵ����ַ�
			i++;							//str[j]��ʾǰ׺�ĵ����ַ�
			j++;
			if (str[i] != str[j]) {		//����ǰ�ַ���ǰ׺�ַ���ͬ
				nextval[i] = j;			//��ǰ��jΪnextval��iλ�õ�ֵ
			}
			else {
				nextval[i] = nextval[j];//����ǰ׺�ַ���ͬ����ǰ׺�ַ���nextvalֵ���Ƹ�nextval��iλ�õ�ֵ
			}
		}
		else {	
			j = nextval[j];	//���ַ�����ͬ��jֵ����
		}
	}
}

/******************** KMP�㷨 **********************/
/*************************************************** 
���㷨�Ĺؼ����ڣ������Ѿ�����ƥ�������Ч��Ϣ��
����iָ�벻���ݣ�ͨ���޸�jָ�룬��ģʽ���������ƶ�����Ч��λ�á�
*****************************************************/
//�����Ӵ�substr ������mainstr�е�pos���ַ�֮���λ�á����������򷵻� 0��
int Index_KMP(char *mainstr, char *substr, int pos)
{
	int i = pos;	//i �����ĵ�ǰλ���±�ֵ
	int j = 1;		//j �Ӵ��ĵ�ǰλ���±�ֵ
	int next[255];	/* ����һ��next���� */
	/****** next �� nextval ���ַ��� *******/
	get_next(substr, next);
	//get_nextval(substr, next);

	while (i <= mainstr[0] && j <= substr[0]) {	//iС�ڵ����������ȣ�jС�ڵ���ģʽ������ʱ��
												//ѭ������
		//ֻ�е��Ӵ�����λ �� ���Ӵ��������ĵ����ַ�ƥ��ɹ�ʱ��iֵ�Ż���ơ�
		if (j == 0 || mainstr[i] == substr[j]) {
			i++;
			j++;
		}
		else {//ָ��������¿�ʼƥ��
			j = next[j];	//j�˻غ��ʵ�λ��,iֵ����
		}
	}
	if (j > substr[0]) {
		return i - substr[0];
	}
	return 0;
}

int main() {

	//next nextval ������
	//int next[255] = {0};
	//int nextval[255] = {0};

	//char str[] = "0ababaaaba";
	//str[0] = strlen(str) - 1;
	//get_next(str, next);
	//get_nextval(str, nextval);


	//KMP �㷨������
	char str1[] = "0aaaaaaaaaaaaaab";
	char str2[] = "0aaab";
	str1[0] = strlen(str1) - 1;
	str2[0] = strlen(str2) - 1;

	int num = Index_KMP(str1, str2, 1);
	printf(" num = %d\n", num);

	return 0;
}
