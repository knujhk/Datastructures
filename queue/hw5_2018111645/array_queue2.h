#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char element;

typedef struct {
    element** queue;
    int size, front, rear;
}QUEUE;

QUEUE* createqueue(int size)
{
    QUEUE* pqueue = (QUEUE*)malloc(sizeof(QUEUE));
    if (pqueue == NULL) {
        printf("failed to create\n");
        return NULL;
    }
    pqueue->queue = (element**)malloc(size * sizeof(element));
    if (pqueue->queue == NULL) {
        free(pqueue);
        printf("failed to create\n");
        return NULL;
    }

    pqueue->size = size;
    pqueue->front = 0;
    pqueue->rear = 0;

    return  pqueue;
}
bool isemptyqueue(QUEUE* q)
{
    if (q->front == q->rear)
        return true;
    else
        return false;
}
bool isfullqueue(QUEUE* q)
{
    if (q->front == (q->rear + 1) % q->size)
        return true;
    else
        return false;
}
void enqueue(QUEUE* q, element* name)
{
    if (isfullqueue(q)) {
        printf("the queue is full.\n");
        return;
    }
    else {
        q->rear = (q->rear + 1) % q->size;
        q->queue[q->rear] = (char*)malloc(5*sizeof(int));
        if (q->queue[q->rear] != NULL)
            strcpy(q->queue[q->rear], name);
    }
}
void dequeue(QUEUE* q, element* name)
{

    if (isemptyqueue(q)) {
        printf("the queue is empty.\n");
        return;
    }
    else {
        q->front = (q->front + 1) % q->size;
    }
    strcpy(name, q->queue[q->front]);
    free(q->queue[q->front]);
}
element* queuefront(QUEUE* q)
{
    if (isemptyqueue(q)) {
        printf("the queue is empty.\n");
        return 0;
    }
    else
        return q->queue[(q->front + 1) % q->size];
}
void destroyqueue(QUEUE* q)
{
    free(q->queue);
    free(q);
}



