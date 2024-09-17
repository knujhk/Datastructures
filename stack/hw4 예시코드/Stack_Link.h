#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct tStackNode {
	Element data;
	struct tStackNode* next;
}StackNode;

typedef struct {
	int count;
	StackNode* top;
	int size;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		printf("fail to creat stack\n");
		return NULL;
	}
	pStack->count = 0;
	pStack->top = NULL;
	pStack->size = size;

	return pStack;
}

void Push(Stack* pStack, Element item) {
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

Element Pop(Stack* pStack) {
	if (pStack->count <= 0) {
		printf("stack is empty\n");
		return 0;
	}
	Element item = pStack->top->data;
	StackNode* OldTop = pStack->top;
	pStack->top = pStack->top->next;
	free(OldTop);
	pStack->count--;
	return item;	
}
Element Top(Stack* pStack) {
	if (pStack->count <= 0) {
		printf("stack is empty\n");
		return 0;
	}
	return pStack->top->data;
}


void DestroyStack(Stack* pStack) {
	StackNode* OldTop = NULL;

	while (pStack->count != 0) {
		OldTop = pStack->top;
		pStack->top = OldTop->next;
		free(OldTop);
		pStack->count--;
	}
	free(pStack);
}

bool IsFullStack(Stack* pStack) {
	if (pStack->count == pStack->size) {
		return true;
	}
	else {
		return false;
	}
}

bool IsEmptyStack(Stack* pStack){
	if (pStack->count == 0) {
		return true;
	}
	else {
		return false;
	}
}

int CountStackItem(Stack* pStack) {
	return pStack->count;
}

void ClearStack(Stack* pStack) {
	StackNode* OldTop = NULL;

	while (pStack->count != 0) {
		OldTop = pStack->top;
		pStack->top = OldTop->next;
		pStack->count--;
	}
}