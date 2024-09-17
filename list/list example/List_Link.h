#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define  MAX  100		//����Ʈ ������ �ִ� ���� �̸� ����

typedef int Element;

typedef struct node {
	Element data;
	struct node* next;
} ListNode;

typedef struct {
	int count;
	ListNode* head, *pos;
	//pos�� ����Ʈ �������� ���� �� ��带 ����Ű�� ������ ����
}List;

List *CreateList() {
	List* pList = (List*)malloc(sizeof(List));
	if (pList == NULL)
		return NULL;

	pList->head = pList->pos = NULL;
	pList->count = 0;

	return pList;
}

bool IsEmptyList(List* pList) {
	if (!pList->count)
		return true;
	else
		return false;
}

bool IsFullList(List* pList) {
	if (pList->count == MAX)
		return true;
	else
		return false;
}

bool _searchList(List *pList, ListNode **ppPre, ListNode **ppLoc, Element data) {
	for (*ppPre = NULL, *ppLoc = pList->head; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->next) {
		if ((*ppLoc)->data == data)
			return true;
		//�������� ���� ����Ʈ��. 
		else if ((*ppLoc)->data > data)
			break;
	}

	return false;
}

void _addList(List* pList, ListNode* pPre, Element data) {
	if (IsFullList(pList))
		return;
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
	if (pNewNode == NULL)
		return;

	pNewNode->data = data;
	if (pPre == NULL) {	//����Ʈ�� ��忡 �߰��ϴ� ���
		pNewNode->next = pList->head;
		pList->head = pNewNode;
	}
	else {
		pNewNode->next = pPre->next;	//��ũ �߰��� �߰��ϴ� ���
		pPre->next = pNewNode;
	}

	pList->count++;

}
void AddNode(List *pList, Element data) {
	if (IsFullList(pList))
		return;
	//�� ��� �߰��� ��ġ�� �� ����� ���� ��ũ�� ����Ű�� ��������� ����
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);	//��������� ���� �ٲ� �� �ְ�
															//�������� �ּҸ� �Ѱ��ش�.

	if (!found)
		_addList(pList, pPre,data);
}

void _removeList(List* pList, ListNode* pPre, ListNode *pLoc) {
	if (pPre == NULL) {
		pList->head = pLoc->next;
	}
	else
	{
		pPre->next = pLoc->next;
	}

	free(pLoc);
	pList->count--;
}
void RemoveNode(List* pList, Element data) {

	ListNode* pPre = NULL;
	ListNode* pLoc = NULL;

	bool found = _searchList(pList, &pPre, &pLoc, data);

	if (found) {
		_removeList(pList, pPre, pLoc);
		printf("%d was removed.\n\n", data);
	}
	else {
		printf("List has not %d \n\n", data);
	}
}

Element SearchList() {
	return 0;
}

void DestroyList(List *pList) {
	ListNode* pOldNode = NULL, * pNext = NULL;

	for (pOldNode = pList->head; pOldNode != NULL; pOldNode = pNext) {
		pNext = pOldNode->next;
		free(pOldNode);
	}
	free(pList);
}

bool traverseList(List* pList, int place, Element* pOutput) {

	//pos�� ����Ű�� ��� ���� ����� ������ ����(true, false)�� �Լ� ��ȯ������ �Ѱ��ְ�
	//�����ʹ� �Ű����� �����͸� ���� �Ѱ���
	if (place == 0 || pList->pos == NULL)
		pList->pos = pList->head;	//����Ʈ�� ó������ �ȴ� ���
	
	else
		pList->pos = pList->pos->next;

	if (pList->pos != NULL) {
		*pOutput = pList->pos->data;
		return true;
	}
	else {
		*pOutput = 0;
		return false;
	}
}

int Listcount(List *pList) {
	return pList->count;
}