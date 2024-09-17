#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Ad_Matrix.h"
#include "list_link.h"

char* createVrtxlist(FILE* , char* );
void printallvrtx(GRAPH* );
void fileToArc(GRAPH* , FILE* );

int main()
{
	GRAPH* graph;
	//char file[30];
	FILE* fp;
	char start;
	char* vrtxArr = NULL;

	do {
		printf("file name of a graph : ");
		//scanf_s("%s", file, 30);
		//fp = fopen(file, "r");
		fp = fopen("input.txt", "r");
	} while (!fp);
	//파일 읽어서 노드의 1차원 배열 만들고 그래프 구조체 만들기
	vrtxArr = createVrtxlist(fp, &start);	
	graph = creategraph(vrtxArr, start);
	//파일 처음부터 다시 읽어서 arc 추가 (fseek 활용)
	fseek(fp, 0, 0);	//fp(FILE* stream, long offset, int whence) whence 0 : 파일 처음으로
	fileToArc(graph, fp);
	fclose(fp);

	printf("\n\nthe graph is : ");
	printallvrtx(graph);

	printf("\ndepth first traversal : ");
	DFtraverse(graph, start);
	printf("\nbreadth first traversal : ");
	BFtraverse(graph, start);
	printf("\n");
	
	return 0;
}
char* createVrtxlist(FILE* fp,char* start)
{
	//배열의 포인터를 다른 함수가 받았을 때 배열 크기를 알 수 없다,
	//배열 마지막에 널문자 넣어줘서 갯수 구할 수 있도록 하기
	char from, to;
	char* vrtxArr;
	int i, flag;
	list* list = createlist();
	listnode* loclist;

	fscanf(fp, "%c", start);
	fgetc(fp);
	fgetc(fp);
	while (1)
	{
		flag = fscanf(fp, "%c %c", &from, &to);
		if (flag == EOF)
			break;
		addlist(list, from);
		addlist(list, to);
		fgetc(fp);
		fgetc(fp);
	}
	
	vrtxArr = (char*)calloc(list->count+1, sizeof(char));
	if (!vrtxArr)
	{
		printf("힙 오버플로우");
		exit(1);
	}
	for ( i = 0, loclist = list->head; i < list->count; i++)
	{
		vrtxArr[i] = loclist->data;
		loclist = loclist->next;
	}
	vrtxArr[i] = '\0';

	destroylist(list);

	return vrtxArr;
}
void printallvrtx(GRAPH* graph)
{
	int i, j;

	printf("\n");
	for ( i = 0; i < graph->count; i++)
	{
		printf("%c : ", graph->vrtxArr[i]);
		for ( j = 0; j < graph->count; j++)
		{
			if (graph->adj_matrix[i][j] == 1)
				printf("%c ", graph->vrtxArr[j]);
		}
		printf("\n");
	}
	return;
}
void fileToArc(GRAPH* graph,FILE* fp)
{
	char from, to;
	char trash;
	int flag;

	fscanf(fp, "%c", &trash);
	fgetc(fp);
    fgetc(fp);
	while (1)
	{
		flag = fscanf(fp, "%c %c", &from, &to);
		if (flag == EOF)
			break;
		insArc(graph, from, to);
		fgetc(fp);
		fgetc(fp);
	}
	return;
}