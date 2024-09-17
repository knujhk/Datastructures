#pragma once
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct qnode {
    treenode* item;
    struct qnode* next;
}QNODE;

typedef struct {
    int count;
    QNODE* front, * rear;
}QUEUE;

QUEUE* createqueue()
{
    QUEUE* ptrq = (QUEUE*)malloc(sizeof(QUEUE));
    if (ptrq == NULL) {
        printf("failed to create\n");
        return NULL;
    }
    ptrq->count = 0;
    ptrq->front = ptrq->rear = NULL;

    return  ptrq;
}
bool isemptyqueue(QUEUE* q)
{
    if (q->count <= 0)
        return true;
    else
        return false;
}
void enqueue(QUEUE* q, treenode* newdata)
{
    QNODE* newnode = (QNODE*)malloc(sizeof(QNODE));
    if (newnode == NULL) {
        printf("failed to create\n");
        return;
    }
    else {
        newnode->item = newdata;
        newnode->next = NULL;
    }
    if (q->count == 0)
        q->front = q->rear = newnode;
    else {
        q->rear->next = newnode;
        q->rear = newnode;
    }
    q->count++;
}
treenode* dequeue(QUEUE* q)
{
    treenode* item;
    QNODE* temp = NULL;

    if (isemptyqueue(q)) {
        return NULL;
    }

    temp = q->front;
    item = temp->item;

    if (q->count == 1)
        q->front = q->rear = NULL;
    else
        q->front = temp->next;

    q->count--;
    free(temp);

    return item;
}
treenode* queuefront(QUEUE* q)
{
    if (isemptyqueue(q)) {
        printf("the queue is empty.\n");
        return 0;
    }
    else
        return q->front->item;
}
void destroyqueue(QUEUE* q)
{
    QNODE* cur, * nextnode = NULL;


    if (isemptyqueue(q))
        free(q);
    else {
        for (cur = q->front; cur != NULL; cur = nextnode)
        {
            nextnode = cur->next;
            free(cur);
        }
        free(q);
    }
}