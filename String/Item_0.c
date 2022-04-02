
/***************** �ַ�����ϵͳ ****************/
/*
�������ַ����ı� ��abcabc�� �м���Ƿ����ַ� ��a�� ʱ��
�ַ�����ϵͳӦ�������û����ַ��洢���ı��е�λ�ã��� 1 ��4��
ͬʱѯ���û��Ƿ����е��ַ� ��a�� �滻������ָ���ַ���
�����û�ָ���ַ� ��a�� ȫ��ת�����ַ� ��d����
ϵͳӦ���滻����ַ��� ��dbcdbc�� �������û���
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//get_nextval ����
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

//KMP�㷨
int Index_KMP(char *mainstr, char *substr, int pos)
{
	int i = pos;	//i �����ĵ�ǰλ���±�ֵ
	int j = 1;		//j �Ӵ��ĵ�ǰλ���±�ֵ
	int next[255];	

	get_nextval(substr, next);

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

//�滻
//��str1�е��Ӵ�str2�滻Ϊstr3,��str2��str����һ��
void replaceString(char *str1, char *str2, char *str3) {
	int pos = 1;
	int res = -1;
	int i, j = 0;
	while (res != 0) {
		res = Index_KMP(str1, str2, pos);
		if (res != 0) {
			for (i = res, j = 1; j <= str3[0]; i++ ,j++) {
				str1[i] = str3[j];
			}
		}
		//printf(" %d", res);
		pos = res + 1;
	}
}

//��ѯ
void Index(char *str1, char *str2) {
	int pos = 1;
	int res = -1;
	int num = 0;
	while (res != 0) {
		res = Index_KMP(str1, str2, pos);
		if (res != 0) {
			//printf(" %d", res);
			num++;
		}
		pos = res + 1;
	}
	printf("ϵͳ��⵽���ַ���ԭ�ַ����г���%d��,��ʼλ�������ǣ�\n", num);
	pos = 1;
	res = -1;
	while (res != 0) {
		res = Index_KMP(str1, str2, pos);
		if (res != 0) {
			printf(" %d", res);
		}
		pos = res + 1;
	}
	printf("\n");
}



//������
int main() {

	char str1[255] = "0aaabb";
	char str2[255] = "0a";
	char str3[255] = "0d";

	char judge;
	//str1[0] = strlen(str1) - 1;
	//str2[0] = strlen(str2) - 1;
	printf("������ԭ�ַ�����\n");
	scanf_s("%s",&str1[1], 254);
	getchar();//��ջ�����
	str1[0] = strlen(str1) - 1;
	//printf("%s\n", &str1[1]);
	//printf("%d\n", str1[0]);

	printf("������Ҫ���ҵ��ַ�����\n");
	scanf_s("%s", &str2[1], 254);
	getchar();//��ջ�����
	str2[0] = strlen(str2) - 1;
	//printf("%s\n", &str2[1]);
	//printf("%d\n", str2[0]);
	Index(str1, str2);

	printf("�Ƿ������ַ��滻��(Y/N)\n");
	scanf_s("%c", &judge);
	getchar();//��ջ�����
	if (judge == 'Y') {
		printf("������Ҫ�滻���ַ���\n");
		scanf_s("%s", &str3[1], 254);
		getchar();//��ջ�����
		str3[0] = strlen(str3) - 1;
		//printf("%s\n", &str2[1]);
		//printf("%d\n", str2[0]);

		replaceString(str1, str2, str3);
		printf("�滻������ַ����ǣ�\n");
		printf("%s\n", &str1[1]);
	}
	else{
		return 0;
	}
	
	return 0;
}
