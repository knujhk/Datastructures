#define _CRT_SECURE_NO_WARNINGS
#include "Ad_Matrix.h"
#include <stdio.h>

int main() {
	char fname[1000];
	char a;
	char b;
	char c;
	int count = 0;
	FILE* fp;
	Graph* gptr = CreateGraph();
	printf("File name of a graph : ");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("File does not open.\n");
		return 1;
	}
	while ((a = fgetc(fp)) != EOF) {
		if ((a != ' ') && (a != '\n')) {
			InsertVertex(gptr, a);
		}
	}
	fseek(fp, 0, SEEK_SET);
	fgetc(fp);
	while ((a = fgetc(fp)) != EOF) {
		if ((a != ' ') && (a != '\n')) {
			if (count == 0) {
				b = a;
				count = 1;
			}
			else if (count == 1) {
				c = a;
				count = 2;
			}
			if (count == 2) {
				InsertArc(gptr, b, c);
				count = 0;
			}
		}
	}
	printf("The graph is : \n");
	PrintGraph(gptr);
	printf("\n");

	printf("Depth First Traversal : ");
	fseek(fp, 0, SEEK_SET);
	a = fgetc(fp);
	if ((a != ' ') && (a != '\n'))
		DepthFirstTraversal(gptr, a);
	ClearVisit(gptr);
	printf("\n");

	printf("Breadth First Traversal : ");
	fseek(fp, 0, SEEK_SET);
	a = fgetc(fp);
	if ((a != ' ') && (a != '\n'))
		BreadthFirstTraversal(gptr, a);
	printf("\n");

	fclose(fp);
	return 0;
}