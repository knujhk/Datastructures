#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Ad_List.h"

int addgraph(GRAPH* graph, void* start, void* destination);
void printallvrtx(GRAPH* graph);

//함수포인터에 넘겨줄 함수
int charcmp(void* a, void* b) {
	return strcmp((char*)a, (char*)b);
}
void process(void* dataptr) {
	printf(" %c", *(char*)dataptr);
}

int main()
{
	GRAPH* graph;
	char file[30], trash;
	FILE* fp;
	int flag;
	char* start, * destination;

	graph = creategraph(charcmp);

	do {
		printf("file name of a graph : ");
		//scanf_s("%s", file, 30);
		//fp = fopen(file, "r");
		fp = fopen("input.txt", "r");
	} while (!fp);

	start = (char*)calloc(2, sizeof(char));
	destination = (char*)calloc(2, sizeof(char));
	fscanf(fp, "%c", start);
	fgetc(fp);
	fgetc(fp);
	insVrtx(graph, start);
	while (1){
		start = (char*)calloc(2, sizeof(char));
		destination = (char*)calloc(2, sizeof(char));
		flag = fscanf(fp, "%c %c",start,destination);
		if (flag == EOF)
			break;
		fgetc(fp);
		fgetc(fp);
		addgraph(graph, start, destination);
	}
	fclose(fp);

	printf("\n\nthe graph is : \n");
	printallvrtx(graph);
	
	printf("\ndepth first traversal : ");
	DFtraverse(graph,process);
	printf("\nbreadth first traversal : ");
	BFtraverse(graph, process);
	printf("\n");

	return 0;
}
int addgraph(GRAPH* graph, void* start, void* destination) 
{
	VERTEX* locVrtx;
	int result = 0;

	while (result != 1)
	{
		switch (insArc(graph, start, destination))
		{
		case(1):
			result = 1;
			break;
		case(-2): //start에 해당하는 vertex가 그래프에 없는 경우
			insVrtx(graph, start);
			break;
		case(-3): //dest에 해당하는 vertex가 그래프에 없는 경우
			insVrtx(graph, destination);
			break;
		case(-1):
			printf("힙 오버플로우 발생");
			exit(1);
		default:
			break;
		}
	}
	
	return result;
}
void printallvrtx(GRAPH* graph)
{
	VERTEX* locVrtx = graph->first;
	ARC* locArc;

	while (locVrtx)
	{
		printf("%c : ", *(char*)locVrtx->dataptr);
		locArc = locVrtx->pArc;
		while (locArc){
			process(locArc->destination->dataptr);
			locArc = locArc->pnextarc;
		}
		printf("\n");
		locVrtx = locVrtx->pnextvrtx;
	}

	return;
}

