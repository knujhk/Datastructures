#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Ad_Matrix3.h"
#include "list_link.h"

char* createVrtxlist(FILE* , char* );
void printallvrtx(GRAPH* );
void fileToArc(GRAPH* , FILE* );
void minSpanningTree(GRAPH* );


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
		fp = fopen("input2.txt", "r");
	} while (!fp);
	//파일 읽어서 노드의 1차원 배열 만들고 그래프 구조체 만들기
	vrtxArr = createVrtxlist(fp, &start);	
	graph = creategraph(vrtxArr, start);
	//파일 처음부터 다시 읽어서 arc와 가중치 추가 (fseek 활용)
	fseek(fp, 0, 0);	//fp(FILE* stream, long offset, int whence) whence 0 : 파일 처음으로
	fileToArc(graph, fp);
	fclose(fp);

	printf("\n\nthe graph is : \n");
	printallvrtx(graph);

	printf("\n\nminimum spanning tree : \n");
	minSpanningTree(graph);

	return 0;
}
char* createVrtxlist(FILE* fp,char* start)
{
	//배열의 포인터를 다른 함수가 받았을 때 배열 크기를 알 수 없다,
	//배열 마지막에 널문자 넣어줘서 갯수 구할 수 있도록 하기
	char from, to;
	char* vrtxArr;
	int i, flag, weight;
	list* list = createlist();
	listnode* loclist;

	fscanf(fp, "%c", start);
	fgetc(fp);
	fgetc(fp);
	while (1)
	{
		flag = fscanf(fp, "%c %c %d", &from, &to,&weight);
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
		printf(" %c :", graph->vrtxArr[i]);
		for ( j = 0; j < graph->count; j++)
		{
			if (graph->adj_matrix[i][j] > 0) {
				printf(" %c", graph->vrtxArr[j]);
				printf(" (%d)", graph->adj_matrix[i][j]);
			}
		}
		printf("\n");
	}
	return;
}
void fileToArc(GRAPH* graph,FILE* fp)
{
	char from, to;
	char trash;
	int flag ,weight;

	fscanf(fp, "%c", &trash);
	fgetc(fp);
	fgetc(fp);

	while (1)
	{
		flag = fscanf(fp, "%c %c %d", &from, &to, &weight);
		if (flag == EOF)
			break;
		insArc(graph, from, to, weight);
		fgetc(fp);
		fgetc(fp);
	}
	return;
}
void minSpanningTree(GRAPH* graph)
{
	//출력 형태는 각각 엣지와 가중치
	//tv에 추가된 노드는 배열원소 1
	int* TV = calloc(graph->count, sizeof(int));
	int** treeEdge;
	int edgecount = 0;
	int i,j;
	//최소코스트 엣지 찾을 때 사용하는 변수
	int leastcost;
	int low, column;
	char from, to;

	//스패닝 트리 엣지 저장하는 2차원 배열
	treeEdge = (int**)malloc((graph->count) * sizeof(int*));
	if (!treeEdge) {
		printf("메모리 할당 실패");
		exit(1);
	}
	for (i = 0; i < (graph->count); i++)
	{
		treeEdge[i] = (int*)calloc(2, sizeof(int));
		if (!treeEdge[i]) {
			printf("메모리 할당 실패");
			exit(1);
		}
	}

	TV[0] = 1; //스패닝 트리에 시작노드 한 개 넣기
	while (edgecount < (graph ->count - 1))
	{
		low = 0;
		column = 0;
		leastcost = 10000;
		for ( i = 0; i < graph->count; i++)
		{
			if (TV[i] == 1)
			{
				for ( j = 0; j < graph->count; j++)
				{
					if ((TV[j] == 0) && (graph->adj_matrix[i][j] > 0)) //tv에 아직 넣지않은 노드 서치
					{
						if (graph->adj_matrix[i][j]<leastcost)
						{
							leastcost = graph->adj_matrix[i][j];
							low = i;
							column = j;
						}
					}
				}
			}
		}
		TV[column] = 1;
		treeEdge[edgecount][0] = low;
		treeEdge[edgecount][1] = column;
		edgecount++;
	}

	for ( i = 0; i < edgecount; i++)
	{
		from = indexToNode(graph, treeEdge[i][0]);
		to = indexToNode(graph, treeEdge[i][1]);
		printf("%c %c (%d)\n", from, to, graph->adj_matrix[treeEdge[i][0]][treeEdge[i][1]]);
	}

	return;
}