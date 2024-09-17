#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queuenode {
	char data;
	struct queuenode* next;
}Node;
typedef struct head {
	int count;
	Node* front;
	Node* back;
}Queue;

Queue* CreateQueue() {
	Queue* hptr = (Queue*)malloc(sizeof(Queue));
	if (hptr == NULL) {
		printf("failed to create queue.\n");
		return NULL;
	}
	hptr->count = 0;
	hptr->front = NULL;
	hptr->back = NULL;
	return hptr;
}

bool IsEmptyQueue(Queue* ptr) {
	if (ptr->count == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Enqueue(Queue* ptr, char item) {
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == NULL) {
		printf("failed to create new node.\n");
		return;
	}
	pNewNode->next = NULL;
	pNewNode->data = item;
	if (IsEmptyQueue(ptr)) {
		ptr->back = pNewNode;
		ptr->front = ptr->back;

	}
	else {
		ptr->back->next = pNewNode;
		ptr->back = pNewNode;
	}
	ptr->count++;
}

char Dequeue(Queue* ptr) {
	Node* NowFront = NULL;
	char return_val;
	if (IsEmptyQueue(ptr)) {
		return '\0';
	}
	else {
		NowFront = ptr->front;
		return_val = ptr->front->data;
		if (ptr->count == 1) {
			ptr->front = ptr->back = NULL;
		}
		else {
			ptr->front = NowFront->next;
		}
		ptr->count--;
		return return_val;
	}
}

char QueueFront(Queue* ptr)
{
	if (IsEmptyQueue(ptr))
		return '\0';
	else
		return ptr->front->data;
}

char Queueback(Queue* ptr)
{
	if (IsEmptyQueue(ptr))
		return '\0';
	else
		return ptr->back->data;
}

void DestroyQueue(Queue* ptr) {
	Node* temp = NULL;
	while (ptr->count != 0) {
		temp = ptr->front;
		ptr->front = temp->next;
		free(temp);
		ptr->count--;
	}
	free(ptr);
}

void ClearQueue(Queue* ptr) {
	ptr->count = 0;
	ptr->front = NULL;
	ptr->back = NULL;
}

int CountQueueItem(Queue* ptr) {
	return ptr->count;
}