#include "Stack_Link.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main() {
	int a;
	int scan;
	int temp;
	Stack* Convert = CreateStack(100);

	printf("Enter a numver : ");
	scan = scanf("%d", &a);
	temp = a;
	while (temp >= 1) {
		Push(Convert, temp % 2);
		temp /= 2;
	}
	printf("\n");
	printf("The binary number of %d :", a);
	while (IsEmptyStack(Convert) == false) {
		printf("%d", Pop(Convert));
	}
}