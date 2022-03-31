
/******************** ���Ŀ����洢��ʽ C���Գ��� ********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LinkNum 3	//ȫ�����������нڵ�洢���ݵĸ���
#define ERROR -1
#define OK 1

typedef int Status;


typedef struct Link {
	char a[LinkNum];	//������ɴ��LinkNum������
	struct Link *next;	//ָ����
}Link, *LinkString;

Status InitLink(LinkString *LinkStr, char *str);
void Display(LinkString LinkStr);

int main() {
	LinkString L;

	InitLink(&L, "sunxinghui");

	Display(L);

	return 0;
}

//*LinkStrΪͷָ�룬strΪ�洢���ַ���
Status InitLink(LinkString *LinkStr, char *str) {
	int length = strlen(str);
	//�����ַ����ĳ��ȣ������������ʹ�ýڵ�ĸ���
	int num = length / LinkNum;
	if (length % LinkNum != 0) {
		num++;
	}

	//��������ʼ����Ԫ�ڵ�
	LinkString temp = (LinkString)malloc(sizeof(Link));
	temp->next = NULL;
	(*LinkStr) = temp;	//ͷָ��ָ����Ԫ�ڵ�

	//��ʼ������
	for (int i = 0; i < num; i++) {
		int j = 0;
		for (; j < LinkNum; j++) {
			if (i * LinkNum + j < length) {
				temp->a[j] = str[i * LinkNum + j];
			}
			else {
				temp->a[j] = '#';
			}

		}
		if (i * LinkNum + j < length) {
			LinkString newlink = (LinkString)malloc(sizeof(Link));
			newlink->next = NULL;
			temp->next = newlink;
			temp = newlink;
		}
	}
	return OK;
}

//���������
void Display(LinkString LinkStr) {
	LinkString temp = LinkStr;
	while (temp) {
		for (int i = 0; i < LinkNum; i++) {
			printf("%c", temp->a[i]);
		}
		temp = temp->next;
	}
}

