#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct listhead {
	element *data;
	int count, size;
}list;

//��������
list* createlist(int size) {

	list* ptrlist = (list*)malloc(sizeof(list));
	if (ptrlist == NULL)
	{
		printf("failed to create.");
		return NULL;
	}

	ptrlist->data=(element*)calloc(size,sizeof(element));
	if (ptrlist->data == NULL)
	{
		printf("failed to create.");
		free(ptrlist);
		return NULL;
	}

	ptrlist->size = size;
	ptrlist->count = 0;

	return ptrlist;
}
int searchlist(list* list, element key, int* index) {

	int i ;
	
	if (list->count == 0)
	{
		*index = 0;
		return 0;
	}
	for (i = 0; i < list->count; i++)
	{
		if (key == list->data[i])
		{
			*index = i;
			return 1;
		}
		else if (key < list->data[i])
		{
			*index = i;
			return 0;
		}
	}
	*index = i;
	return 0;
}
void addlist(list* list, element item){
	int i, index = 0;
	int searchresult = 0;

	searchresult = searchlist(list, item, &index);

	if (searchresult == 1) 
	{
		printf("�̹� ����Ʈ�� �ִ� �ڷ��Դϴ�.\n");
		return;
	}
	else
	{
		if (list->count == list->size) {
			printf("list is full\n");
		}
		else if (index == list->count){ //���� ����Ʈ ������ ���� �ڿ� �߰�
			list->data[index] = item;
			list->count++;
		}
		else if (index != list->count){	//�߰��� �߰��ϰ� �� ĭ�� �и�����
			for ( i = list->count - 1; i >= index; i--)
				list->data[i + 1] = list->data[i];
			list->data[index] = item;
			list->count++;
		}
		return;
	}
	
}
int deletelist(list* list, element item) {

	int i, index = 0;
	int searchresult = 0;

	searchresult = searchlist(list, item, &index);

	if (searchresult == 1) //����Ʈ���� ������ ����
	{
		if (index == list->count - 1) //���� ����� ������ ������ ���
		{
			list->data[index] = 0;
		}
		else {
			for ( i = index; i < list->count-1; i++)
				list->data[i] = list->data[i + 1];
			list->data[i] = 0; //������ ������ ���� �ʱ�ȭ
		}
		list->count--;
		return 1;
	}
	else if (searchresult == 0) //������ �������� ����Ʈ�� ����
		printf("�ش� �������� ����Ʈ�� �����ϴ�.\n");
	return 0;
}
void printlist(list*list) {
	
	int i = 0;

	printf("The current status of List : ");
	
	for (i = 0; i < list->count; i++) {
		if(i==0)
			printf("%d", list->data[i]);
		else
			printf(", %d", list->data[i]);
	}
	printf("\n");
}
void destroylist(list* list) {
	free(list->data);
	free(list);
}