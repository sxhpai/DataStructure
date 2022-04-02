
/***************** KMPģʽƥ���㷨 ******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//��ģʽ�� str �� next ����
//str Ϊ�ַ���ָ�룬strLenΪ�ַ������ȣ�next���顣
void get_next(char *str, int *next)
{
	next[1] = 0;
	int i = 1; 
	int j = 0;
	while (i < str[0]) {	// �˴�str[0]��ʾ��str����Ч���ȣ�����������str[0]�ĳ��ȣ�
		if (j == 0 || str[i] == str[j]) {	//str[i]��ʾ��׺�ĵ����ַ�
			++i;							//str[j]��ʾǰ׺�ĵ����ַ�
			++j;
			next[i] = j;
		}
		else {
			j = next[j];	//���ַ�����ͬ���� j ����
		}
	}
}

//��ģʽ�� str �� next ���������ֵ������ nextval ����
//str Ϊ�ַ���ָ�룬strLenΪ�ַ������ȣ�nextval���顣
void get_nextval(char *str, int *nextval)
{
	nextval[1] = 0;
	int i = 1;
	int j = 0;
	while (i < str[0]) {	// �˴�str[0]��ʾ��str����Ч���ȣ�����������str[0]�ĳ��ȣ�
		if (j == 0 || str[i] == str[j]) {		//str[i]��ʾ��׺�ĵ����ַ�
			i++;								//str[j]��ʾǰ׺�ĵ����ַ�
			j++;
			if (str[i] != str[j]) {
				nextval[i] = j;
			}
			else {
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}
}

//�����Ӵ�subStr������S�е�pos���ַ�֮����׸�λ���±ꡣ���������򷵻� 0��
//subStr�ǿգ���1<=pos<=Strlength(mainStr)��
int Index_KMP(char *mainStr, char *subStr, int pos) {
	int i = pos;	//i����������ǰλ�õ��±�ֵ
	int j = 1;		//j�����Ӵ���ǰλ�õ��±�ֵ
	int next[255];	//����һ��next����
	get_next(subStr, next);	//���next����
	while (i <= mainStr[0] && j <= subStr[0]) {//mainStr[0]������Ч���ȣ�subStr[0]�Ӵ�����Ч���ȡ�
		if (j == 0 || mainStr[i] == subStr[j]) {
			i++;
			j++;
		}
		else {//ָ��������¿�ʼƥ��
			//j = 1;
			j = next[j];	//j�˻غ��ʵ�λ�ã�iֵ����
		}
	}

	if (j > subStr[0]) {	//j �����Ӵ��ĳ��ȣ�˵��ƥ��ɹ�
		return i - subStr[0];	//������±�
	}
	return 0;
}

//������
int main()
{
	//char str[] = "0ababaaaba";//�ַ�����0λ��Ч���ӵ�1λ��ʼ����0λӦ�����Դ洢�ַ����ĳ��ȡ�
	//str[0] = strlen(str) - 1;//���ַ�������Ч���ȣ�������str[0]��char ���͵����ݴ洢 -128 �� 127 ����û���⡣
	////���������㹻��������
	//int next[15] = {0};
	//int nextval[15] = { 0 };
	
	//���ģʽ�� str �� next ����� nextval ����
	//get_next(str, next);
	//get_nextval(str, nextval);

	char str1[] = "0sunssxingasdfsxinghui";
	char str2[] = "0xing";
	str1[0] = strlen(str1) - 1;
	str2[0] = strlen(str2) - 1;

	int g = Index_KMP(str1, str2,9);
	printf("** %d **\n", g);

	return 0;
}
