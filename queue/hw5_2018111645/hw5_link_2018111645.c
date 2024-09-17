#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "link_queue2.h"

void printstatus(QUEUE* q);

int main()
{
	int menu;
	char name[20] ;

	QUEUE* q1 = createqueue();
	

	while (1) {
		printf("In(0), out(1), exit(2) : ");
		scanf("%d", &menu);
		getchar();
		switch (menu)
		{
		case 0:
			printf("\nCustomer : ");
			scanf("%[^\n]s", name);
			getchar();
			//gets(name, 20); 
			enqueue(q1, name);
			printstatus(q1);
			break;
		case 1:
			if (isemptyqueue(q1))
				printf("Queue is empty !\n");
			else{
				dequeue(q1, name);
				printf("\nCustomer dequeued : %s\n",name);
			}
			printstatus(q1);
			break;
		case 2:
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
	QNODE* cur= q->front;

	printf("The current status of Queue : ");
	printf("(");
	if (cur != NULL) 
	{
		printf("%s%d", cur->item, i);
		cur = cur->next;
		for (i = 2; cur != NULL;i++) {
			printf(", %s%d", cur->item, i);
			cur = cur->next;
		}
	}
	printf(")\n\n");
}