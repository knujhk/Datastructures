#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Element;
typedef struct {
	Element* stack;
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		printf("fail to creat stack\n");
		return NULL;
	}

	pStack->stack = (Element*)malloc(size * sizeof(Element));
	if (pStack->stack == NULL) {
		printf("fail to creat memory of elements\n");
		free(pStack);
		return NULL;
	}
	pStack->size = size;
	pStack->top = -1;

	return pStack;
}

void Push(Stack* pStack, Element item) {
	if (pStack->top == pStack->size - 1) {
		printf("Stack is full\n");
		return;
	}

	pStack->stack[++pStack->top] = item;
}

Element Pop(Stack* pStack) {
	if (pStack->top < 0) {
		printf("Stack is empty\n");
		return 0;
	}
	return pStack->stack[pStack->top--];
}

Element Top(Stack* pStack) {
	if (pStack->top < 0) {
		printf("Stack is empty\n");
		return 0;
	}
	return pStack->stack[pStack->top];
}

void DestroyStack(Stack* pStack) {
	free(pStack->stack);
	free(pStack);
}

bool IsFullStack(Stack* pStack) {
	if (pStack->top == pStack->size - 1) {
		return true;
	}
	else {
		return false;
	}
}

bool IsEmptyStack(Stack* pStack) {
	if (pStack->top < 0) {
		return true;
	}
	else {
		return false;
	}
}
int CountStackItem(Stack* pStack) {
	return pStack->top + 1;
}

void ClearStack(Stack* pStack) {
	if (pStack->top < 0) {
		printf("Stack is empty\n");
		return;
	}
	for (int i = 0;i <= pStack->top;i++) {
		pStack->stack[i] = '\0';
	}
}