#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define  MAX  100		//리스트 원소의 최대 갯수 미리 지정

typedef int Element;

typedef struct node {
	Element data;
	struct node* next;
} ListNode;

typedef struct {
	int count;
	ListNode* head, *pos;
	//pos는 리스트 아이템을 훑을 때 노드를 가리키는 포인터 변수
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
		//오름차순 정렬 리스트임. 
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
	if (pPre == NULL) {	//리스트의 헤드에 추가하는 경우
		pNewNode->next = pList->head;
		pList->head = pNewNode;
	}
	else {
		pNewNode->next = pPre->next;	//링크 중간에 추가하는 경우
		pPre->next = pNewNode;
	}

	pList->count++;

}
void AddNode(List *pList, Element data) {
	if (IsFullList(pList))
		return;
	//새 노드 추가할 위치와 그 노드의 이전 링크를 가리키는 노드포인터 선언
	ListNode* pPre = NULL, * pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);	//노드포인터 값을 바꿀 수 있게
															//포인터의 주소를 넘겨준다.

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

	//pos가 가리키는 노드 다음 노드의 아이템 유무(true, false)를 함수 반환값으로 넘겨주고
	//데이터는 매개변수 포인터를 통해 넘겨줌
	if (place == 0 || pList->pos == NULL)
		pList->pos = pList->head;	//리스트의 처음부터 훑는 경우
	
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