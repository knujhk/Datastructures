#define _CRT_SECURE_NO_WARNINGS
#include "Ad_Matrix3.h"
#include <stdio.h>

int main() {
	char fname[1000];
	char a;
	char b;
	char c;
	int prior = 0;
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
		if ((a != ' ') && (a != '\n') && (a >= 'A') && (a < 'Z')) {
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
			else if (count == 2) {
				fseek(fp, -1, SEEK_CUR);
				fscanf(fp, "%d", &prior);
				InsertArc(gptr, b, c, prior);
				count = 0;
			}
		}
	}

	printf("The graph is : \n");
	PrintGraph(gptr);
	printf("\n");
	
	fseek(fp, 0, SEEK_SET);
	a = fgetc(fp);
	printf("Minimum spanning tree : \n");
	MinimumSpanningTree(gptr, a);
	printf("\n");
	
	printf("Shortest path from %c : \n", a);
	ShortestPath(gptr, a);
	fclose(fp);
	return 0;
}