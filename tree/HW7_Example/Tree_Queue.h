#pragma once
#include <stdlib.h>

typedef TreeNode* element;

typedef struct QueueNode
{
	element item;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue
{
	int count;
	QueueNode* front; 
	QueueNode* rear;
}Queue;

Queue* CreateQueue(void)
{
	Queue* p = (Queue*)malloc(sizeof(Queue));
	if (p == NULL)
		return NULL;

	p->count = 0;
	p->front = NULL;
	p->rear = NULL;

	return p;
}

void Enqueue(Queue* p, element item)
{
	QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newnode == NULL)
		return;

	newnode->item = item;
	newnode->next = NULL;

	if (p->count == 0)
	{
		p->front = newnode;
		p->rear = newnode;
		p->count++;
	}
	else
	{
		p->rear->next = newnode;
		p->rear = newnode;
		p->count++;
	}
}

element Dequeue(Queue* p)
{
	QueueNode* pFront = NULL;
	element tmp;
	if (p->count == 0)
		return 0;

	pFront = p->front;
	if (p->count == 1)
	{
		tmp = p->front->item;
		p->front = NULL;
		p->rear = NULL;
		p->count--;
	}
	else
	{
		tmp = p->front->item;
		p->front = p->front->next;
		p->count--;
	}
	free(pFront);
	return tmp;
}