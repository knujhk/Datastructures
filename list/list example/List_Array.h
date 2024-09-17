#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int Element;

typedef struct tListNode {
	Element* list;
	int count,size;
} List;

List* CreateList(int size) {
	List* pList = (List*)malloc(sizeof(List));
	if (pList == NULL) {
		printf("allocate mamery error!\n");
		return NULL;
	}

	pList->list = (Element*)malloc(size*sizeof(Element));
	if(pList->list == NULL) {
		printf("allocate mamery error!\n");
		free(pList);
		return NULL;
	}

	pList->count = 0;
	pList->size = size;

	return pList;
}

bool IsEmptyList(List* list) {
	if (!list->count)			// count of list is 0
		return true;
	else
		return false;
}

bool IsFullList(List* list) {
	if (list->count == list->size)
		return true;
	else
		return false;
}

bool _searchList(List* pList, int *place, Element data) {
	int i;

	//�������� ���� ����Ʈ�� data�� �� �ε��� ��ġ
	for (i = 0, *place = 0; i < pList->count; ++i, *place = i) {
		if (pList->list[i] == data) {
			return true;	
		}
		else if (pList->list[i] > data) {
			break;		//�˻���� �� ã�� ���, ������ �߰��Ѵٸ� ���� �ε��� ��ġ ���� �����͵�
						//��� �� ĭ�� �о��ְ� �־�� ��.
		}
	}
	return false;
}

void _addList(List *pList, int place, Element data) {
	int i;

	//�迭�� ������ �߰��ϴ� �����Լ�. �ݺ��� ���� : 'place' �ε����� ������ �߰��ϱ� ���� 
	//�� ĭ�� �ڷ� �б�
	for (i = pList->count; i > place; i--) {
		pList->list[i] = pList->list[i - 1];
	}
	pList->list[place] = data;
	pList->count++;
}

void AddNode(List* pList, Element data) {
	int temp = 0;
	if (IsFullList(pList)) {
		printf("List is full!\n");
		return;
	}

	bool found = _searchList(pList, &temp, data);
	if (!found)
		_addList(pList, temp, data);
}

void _removeList(List* pList, int place) {
	int i;

	if (place >= 0) {
		for (i = place; i < pList->count; i++) {
			pList->list[i] = pList->list[i + 1];
		}
		pList->count--;
	}
}

void RemoveList(List* pList, Element data) {
	int temp;

	if (IsEmptyList(pList)) {
		printf("List is empty!\n");
		return;
	}
	bool found = _searchList(pList, &temp, data);

	if (found) {
		_removeList(pList, temp);
		printf("%d was removed.\n\n", data);
	}
	else {
		printf("List has not %d \n\n", data);
	}
}

Element SearchList(List* pList, Element key) {
	int temp;

	bool found = _searchList(pList, &temp, key);

	if (found)
		printf("My List has %d.\n", key);
	else
		printf("My List does not have %d.\n", key);
}

void DestroyList(List* pList) {
	if (pList->count > 0) {
		free(pList->list);
	}
	free(pList);
}

int Listcount(List* pList) {
	return pList->count;
}
