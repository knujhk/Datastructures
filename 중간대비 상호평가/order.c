#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link_queue_char.h"
#include "link_stack_char.h"

void print_stat(QUEUE* q);

int main()
{
	char menu[10];
	char* cur = NULL;
	int i;
	int select = 0;
	QUEUE* q1 = createqueue();
	STACK* s1 = create_stack();

	while (1)
	{
		printf("\nOrder (0), Serve (1), Exit (2) : ");
		scanf("%d", &select);
		getchar();
		switch (select)
		{
		case 0 :	//order
			printf("\nOrder : ");
			scanf("%s", menu);
			enqueue(q1, menu);
			print_stat(q1);
			break;
		case 1 :	//serve
			if (!isemptyqueue(q1)){
				dequeue(q1, menu);	//서빙할 메뉴를 menu문자열에 저장
				cur = menu;
				for ( ; *cur != NULL  ; cur++)
				{
					push(s1, *cur);
				}
				//for (i = 0; i < strlen(menu); i++)
				//	push(s1, menu[i]);
				printf("\nServe : ");
				switch (pop(s1))
				{
				case '1': printf("Ice cream"); break;
				case '2': printf("Bibimbab"); break;
				case '3': printf("Bulgogi"); break;
				case '4': printf("Coffee"); break;
				case '5': printf("Noodle"); break;
				default: break;
				}
				while (s1->count > 0) {
					switch (pop(s1))
					{
					case '1': printf(", Ice cream"); break;
					case '2': printf(", Bibimbab"); break;
					case '3': printf(", Bulgogi"); break;
					case '4': printf(", Coffee"); break;
					case '5': printf(", Noodle"); break;
					default: break;
					}
				}
			}
			else
				printf("\n주문이 없습니다.");
			printf("\n");
			print_stat(q1);
			break;
		case 2 :
			destroystack(s1);
			destroyqueue(q1);
			exit(0);
		default:
			break;
		}
	}

	return 0;
}
void print_stat(QUEUE* q)
{
	int i = 1;
	QNODE* cur = q->front;

	printf("\nStat : ");
	if (cur != NULL)
	{
		printf("%s", cur->item);
		cur = cur->next;
		for (; cur != NULL; ) {
			printf(" %s", cur->item);
			cur = cur->next;
		}
	}
	printf(" (%d)\n\n",q->count);
}