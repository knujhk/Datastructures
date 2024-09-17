#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementL;

typedef struct tStackNode {
	ElementL data;
	struct tStackNode* next;
}StackNode;

typedef struct {
	int count;
	StackNode* top;
	int size;
}StackL;

StackL* CreateStackL(int size) {
	StackL* pStack = (StackL*)malloc(size*sizeof(StackL));
	if (pStack == NULL) {
		printf("fail to creat stack\n");
		return NULL;
	}
	pStack->count = 0;
	pStack->top = NULL;
	pStack->size = size;

	return pStack;
}

void PushL(StackL* pStack, ElementL item) {
	if (pStack->count == pStack->size) {
		printf("stack is full\n");
		return;
	}
	StackNode* pNewNode = (StackNode*)malloc(sizeof(StackNode));
	if (pNewNode == NULL) {
		printf("fail to creat memory of stack\n");
		return;
	}

	pNewNode->data = item;
	pNewNode->next = pStack->top;
	pStack->top = pNewNode;
	pStack->count++;
}

ElementL PopL(StackL* pStack) {
	if (pStack->count <= 0) {
		printf("stack is empty\n");
		return 0;
	}
	ElementL item = pStack->top->data;
	StackNode* OldTop = pStack->top;
	pStack->top = pStack->top->next;
	free(OldTop);
	pStack->count--;
	return item;
}
ElementL TopL(StackL* pStack) {
	if (pStack->count <= 0) {
		printf("stack is empty\n");
		return 0;
	}
	return pStack->top->data;
}


void DestroyStackL(StackL* pStack) {
	StackNode* OldTop = NULL;

	while (pStack->count != 0) {
		OldTop = pStack->top;
		pStack->top = OldTop->next;
		free(OldTop);
		pStack->count--;
	}
	free(pStack);
}

bool IsFullStackL(StackL* pStack) {
	if (pStack->count == pStack->size) {
		return true;
	}
	else {
		return false;
	}
}

bool IsEmptyStackL(StackL* pStack) {
	if (pStack->count == 0) {
		return true;
	}
	else {
		return false;
	}
}

int CountStackItemL(StackL* pStack) {
	return pStack->count;
}

void ClearStackL(StackL* pStack) {
	StackNode* OldTop = NULL;

	while (pStack->count != 0) {
		OldTop = pStack->top;
		pStack->top = OldTop->next;
		pStack->count--;
	}
}