#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "array_queue2.h"

void printstatus(QUEUE* q);

int main()
{
	int menu;
	char name[20];

	QUEUE *q1 = createqueue(30);

	while (1) {
		printf("In(0), out(1), exit(2) : ");
		scanf("%d", &menu);
		getchar();
		switch (menu)
		{
			case 0 :
				printf("\nCustomer : ");
				scanf("%[^\n]s", name);
				enqueue(q1, name);
				printstatus(q1);
				break;
			case 1 :
				if (isemptyqueue(q1))
					printf("Queue is empty !\n");
				else {
					dequeue(q1, name);
					printf("\nCustomer dequeued : %s\n", name);
				}
				printstatus(q1);
				break;
			case 2 :
				destroyqueue(q1);
				exit(0);
		default:
			break;
		}
	}
	return 0;
}
void printstatus(QUEUE* q)
{
	int i = 1;

	printf("The current status of Queue : ");
	printf("(");
	if (!isemptyqueue(q))
	{
		printf("%s%d", q->queue[(q->front + 1) % q->size], i);
		for (i = 2; ((q->front + i) % q->size) <= q->rear; i++)
			printf(", %s%d", q->queue[(q->front + i) % q->size], i);
	}
	printf(")\n\n\n");
}