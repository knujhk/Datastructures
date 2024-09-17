#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct listnode {
	element data;
	struct listnode* next;

}listnode;

typedef struct list {
	listnode* head, *pos;
	int count;
}list;

listnode* pre, * loc;

	//��������
list* createlist() 
{
	list* ptrlist = (list*)malloc(sizeof(list));
	if (ptrlist == NULL)
	{
		printf("failed to create.");
		return NULL;
	}
	
	ptrlist->count = 0;
	ptrlist->head = NULL;

	return ptrlist;
}
int searchlist(list* list, element key)
{
	if (list->count == 0)
		return 0;
	for  (pre = NULL,loc = list->head; loc != NULL; pre = loc, loc = loc->next)
	{
		if (loc->data == key)
			return 1;
		else if (loc->data > key)
			break;	//not found, ��� �����Ͱ� ����Ʈ �߰��� ���� ��
	}
	return 0; //not found
}
void addlist(list* list, element item)
{
	//listnode* pre, * loc;
	int searchresult = searchlist(list, item);

	if (searchresult == 1) {
		return;
	}
	else { // searchlist = 0
		listnode* pnewnode = (listnode*)malloc(sizeof(listnode));
		if (pnewnode == NULL)
		{
			printf("failed to create\n");
			return;
		}
		pnewnode->next = NULL;
		pnewnode->data = item;
		if (pre == NULL) //��忡 �߰��ϴ� ���
		{
			pnewnode->next = list->head;
			list->head = pnewnode;
		}
		else	//����Ʈ �߰� or ���� �߰��ϴ� ���
		{
			pnewnode->next = pre->next;
			pre->next = pnewnode;
		}
		list->count++;
	}

	return;
}
int deletelist(list* list, element item) 
{
	int searchresult = searchlist(list, item);

	if (searchresult == 0) {
		return 0;
	}
	else {
		if (loc == list->head) //��� ��带 �����ϴ� ���
			list->head = loc->next;
		else
			pre->next = loc->next;
		free(loc);
		list->count--;
	}
	return 1;
}
void printlist(list* list) 
{
	listnode* cur;
	
	printf("The current status of List : ");
	if (list->count == 0) {
		printf("\n");
		return;
	}
		
	printf("%d", list->head->data);
	for (cur = list->head->next; cur != NULL; cur = cur->next)
		printf(", %d", cur->data);
	printf("\n");
}
void destroylist(list* list) 
{
	listnode* cur, * next;

	if (list->count == 0)
		free(list);
	else {
		for (cur = list->head; cur != NULL; cur = next)
		{
			next = cur->next;
			free(cur);
		}
	}
}