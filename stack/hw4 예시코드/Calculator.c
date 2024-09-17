#include "Stack_Array2.h"
#include "Stack_Link2.h"
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main() {
	char getExp[100];
	char temp1;
	char postF[1000] = "";
	char space = ' ';

	int count = 0;
	int temp11 = 0;
	int temp22 = 0;

	char err[100][100];

	Stack* getE = CreateStack(100);
	Stack* postfix = CreateStack(100);
	StackL* calcul = CreateStackL(100);

	printf("Arthemetic Expression : ");
	int scan = scanf(" %[^\n]", getExp);
	int len = strlen(getExp);

	printf("Input : %s\n", getExp);
	
	//find error

	for (int i = 0;i < len;i++) {
		if (getExp[i] == '(') {
			count++;
		}
		else if (getExp[i] == ')') {
			count--;
		}
	}
	if (count != 0) {
		printf("Error : Check the pairs of Parenthesis");
		exit(0);
	}
	count = 0;
	char* checkE = strtok(getExp," ");
	while (checkE != NULL) {
		strcpy(err[count], checkE);
		count++;
		checkE = strtok(NULL, " ");
	}

	for (int i = 0; i < count - 1; i++) {
		if ((err[i][0]>'0' && err[i][0] <'9') &&
			(err[i+1][0] > '0' && err[i+1][0] <'9')) {
			printf("Error : Check the binary expression!\n");
			exit(0);
		}
	}

	
	
	

	//infix -> postfix

	for (int i = 0; i < len;i++) {
		if (getExp[i] == '(') {
			Push(getE, getExp[i]);
		}
		else if (getExp[i] == ')') {
			while (1) {
				if (getE->top >= 0) {
					temp1 = Pop(getE);
					if (temp1 == '(') {
						break;
					}
					else {
						strncat(postF, &space, 1);
						strncat(postF, &temp1, 1);
					}
				}
				else {
					Push(getE, getExp[i]);
				}
			}
		}
		else if (getExp[i] == '+' || getExp[i] == '-') {
			if (getE->top >= 0) {
				temp1 = Pop(getE);
				if (temp1 == '(') {
					Push(getE, temp1);
					Push(getE, getExp[i]);
				}
				else if (temp1 == '+' || temp1 == '-') {
					strncat(postF, &space, 1);
					strncat(postF, &temp1, 1);
					Push(getE, getExp[i]);
				}
				else if (temp1 == '*' || temp1 == '%') {
					strncat(postF, &space, 1);
					strncat(postF, &temp1, 1);
					Push(getE, getExp[i]);
				}
			}
			else {
				Push(getE, getExp[i]);
			}
		}
		else if (getExp[i] == '*' || getExp[i] == '%') {
			if (getE->top >= 0) {
				temp1 = Pop(getE);
				if (temp1 == '(') {
					Push(getE, temp1);
					Push(getE, getExp[i]);
				}
				else if (temp1 == '+' || temp1 == '-') {
					Push(getE, temp1);
					Push(getE, getExp[i]);
				}
				else if (temp1 == '*' || temp1 == '%') {
					strncat(postF, &space, 1);
					strncat(postF, &temp1, 1);
					Push(getE, getExp[i]);
				}
			}
			else {
				Push(getE, getExp[i]);
			}
		}
		else if (getExp[i] >= '0' && getExp[i] <= '9') {
			if (i > 0) {
				if (getExp[i - 1] >= '0' && getExp[i - 1] <= '9') {
					strncat(postF, &getExp[i], 1);
				}
				else {
					strncat(postF, &space, 1);
					strncat(postF, &getExp[i], 1);
				}
			}
			else {
				strncat(postF, &getExp[i], 1);
			}
			
		}
	}
	while (getE->top >= 0) {
		temp1 = Pop(getE);
		strncat(postF, &space, 1);
		strncat(postF, &temp1, 1);
	}
	printf("Post : %s\n", postF);
	
	//postfix calculation

	char* tokP = strtok(postF, " ");
	char* check = tokP;

	while (tokP != NULL) {
		if (strcmp(tokP, "+")==0) {
			temp11 = PopL(calcul);
			temp22 = PopL(calcul);
			PushL(calcul, temp11 + temp22);
		}
		else if (strcmp(tokP, "-") == 0) {
			temp11 = PopL(calcul);
			temp22 = PopL(calcul);
			PushL(calcul, temp22 - temp11);
		}
		else if (strcmp(tokP, "*") == 0) {
			temp11 = PopL(calcul);
			temp22 = PopL(calcul);
			PushL(calcul, temp11 * temp22);
		}
		else if (strcmp(tokP, "%") == 0) {
			temp11 = PopL(calcul);
			temp22 = PopL(calcul);
			PushL(calcul, temp22%temp11);
		}
		else {
			temp11 = atoi(tokP);
			PushL(calcul, temp11);
		}
		tokP = strtok(NULL, " ");
	}
	temp11 = PopL(calcul);
	printf("Result : %d", temp11);

}