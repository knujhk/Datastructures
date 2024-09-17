#include "Stack_Link.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main() {
	Stack* reverse = CreateStack(100);
	
	int a=0;
	int scan = 0;

	while (1) {
		printf("Enter a number(<Ctrl+d> to stop) : ");
		scan = scanf("%d", &a);
		if (scan !=1) {
			break;
		}
		Push(reverse,a);
	}
	printf("The List of numbers reversed:\n");

	while (IsEmptyStack(reverse) == false) {
		printf("%d\n", Pop(reverse));
	}
}