#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "list_link.h"

int main()
{
	int menu, num, index = 0;
	list* list1 = createlist();
	

	do {
		printf("\nIn (0), Search (1), Out (2), Exit (3) : ");
		while (scanf("%d", &menu) != 1) {
			printf("0~3 범위의 정수를 입력하세요. ");
			rewind(stdin);
		}

		switch (menu) {
		case(0):
			printf("in : ");
			while (scanf("%d", &num) != 1) {
				printf("정수를 입력하세요 ");
				rewind(stdin);
			}
			addlist(list1, num);
			printlist(list1);
			break;
		case(1):
			printf("search : ");
			while (scanf("%d", &num) != 1) {
				printf("정수를 입력하세요 ");
				rewind(stdin);
			}
			if (searchlist(list1, num) == 1)
				printf("the list has %d\n", num);
			else
				printf("the list does not have %d\n", num);
			printlist(list1);
			break;
		case(2):
			printf("out : ");
			while (scanf("%d", &num) != 1) {
				printf("정수를 입력하세요 ");
				rewind(stdin);
			}
			if (deletelist(list1, num) == 1)
				printf("%d was removed\n", num);
			printlist(list1);
			break;
		case(3):
			exit(0);
		default:
			printf("0~3 범위의 정수를 입력하세요. ");
			break;
		}
	} while (1);

	return 0;
}