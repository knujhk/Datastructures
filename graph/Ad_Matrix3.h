#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s_link_c.h"
#include "q_link_c.h"

typedef struct {
	int count;
	char start;
	char* vrtxArr;
	int** adj_matrix;
	int* visited;
}GRAPH;

GRAPH* creategraph(char* vrtxArr,char startnode) {
	GRAPH* graph;
	int i = 0;
	
	//그래프 구조체에 동적할당
	graph = (GRAPH*)malloc(sizeof(GRAPH));
	if (!graph)
		return NULL;

	graph->vrtxArr = vrtxArr;
	graph->start = startnode;
	//노드 배열의 원소 갯수 구하기
	while (graph->vrtxArr[i] != '\0') 
		i++;
	graph->count = i; //널문자 인덱스 = 마지막 노드 인덱스+1 (카운트)

	//노드 방문여부 확인하는 배열 초기화
	graph->visited = (int*)calloc(graph->count,sizeof(int));
	//사이즈에 맞는 2차원 배열 만들기
	int** matrix = (int**)malloc((graph->count) * sizeof(int*));
	if (!matrix) {
		printf("메모리 할당 실패");
		exit(1);
	}
	for ( i = 0; i < (graph->count); i++)
	{
		matrix[i] = (int*)calloc((graph->count), sizeof(int));
		if (!matrix[i]) {
			printf("메모리 할당 실패");
			exit(1);
		}
	}
	graph->adj_matrix = matrix;

	return graph;
}
int nodeToindex(GRAPH* graph, char node)
{
	int i;
	int index;

	for (i = 0; i < graph->count; i++) {
		if (graph->vrtxArr[i] == node)
			break;
	}

	if (i == (graph->count))
		return -1;
	else {
		index = i;
	}
	return index;
}
char indexToNode(GRAPH* graph, int index)
{
	return graph->vrtxArr[index];
}
int insArc(GRAPH* graph,char from, char to, int  weight)
{
	int i , j ;

	i = nodeToindex(graph, from); //행
	j = nodeToindex(graph, to);	//열
	
	if (i<0 || j<0)
		return 0;
	
	graph->adj_matrix[i][j] = weight;
	graph->adj_matrix[j][i] = weight;
	return 1;
}
int dltArc(GRAPH* graph, char from, char to) 
{
	int i,  j;

	i = nodeToindex(graph, from); //행
	j = nodeToindex(graph, to);	//열

	if (i < 0 || j < 0)
		return 0;

	graph->adj_matrix[i][j] = 0;
	graph->adj_matrix[j][i] = 0;
	return 1;
}
void clearvisited(GRAPH* graph)
{
	int i;

	for (i = 0; i < graph->count; i++)
		graph->visited[i] = 0;

	return;
}
void DFtraverse(GRAPH* graph, char start) 
{
	int i,j;
	STACK* stack;
	int nodeindex;
 
	// pop하고print,  arc확인 
	
	stack = createstack();
	clearvisited(graph);
	//시작점 출력
	printf("%c ", start);
	nodeindex = nodeToindex(graph, start);
	graph->visited[nodeindex] = 1;

	for (j = 0; j < graph->count; j++)
	{
		if (graph->adj_matrix[nodeindex][j] > 0)
			push(stack, j);
	}
	while (!isemptystack(stack))
	{
		nodeindex = pop(stack);
		if (graph->visited[nodeindex] == 0)		//방문한 적 없는 노드만 처리
		{
			printf("%c ", indexToNode(graph, nodeindex));
			graph->visited[nodeindex] = 1;
			for (j = 0; j < graph->count; j++)
			{
				if (graph->adj_matrix[nodeindex][j] > 0)
					push(stack, j);
			}
		}
		
	}
	//disconnected라도 모든 노드를 출력할 수 있도록.
	for (i = 0; i < graph->count; i++)
	{
		for (j = 0; j < graph->count; j++)
		{
			if (graph->adj_matrix[i][j] > 0)
				push(stack, j);
		}
		while (!isemptystack(stack))
		{
			nodeindex = pop(stack);
			if (graph->visited[nodeindex] == 0)		//방문한 적 없는 노드만 처리
			{
				printf("%c", indexToNode(graph, nodeindex));
				graph->visited[nodeindex] = 1;
				for (j = 0; j < graph->count; j++)
				{
					if (graph->adj_matrix[nodeindex][j] > 0)
						push(stack, j);
				}
			}
		}
	}
	destroystack(stack);
	return;
}
void BFtraverse(GRAPH* graph, char start) 
{
	int i, j;
	QUEUE* queue;
	int nodeindex;
	//첫번째 노드 출력, 
	// dequeue하고print,  arc확인(enqueue하고 해당 행 다 지우기), 

	queue = createqueue();
	clearvisited(graph);
	//시작점 출력
	printf("%c ", start);
	nodeindex = nodeToindex(graph, start);
	graph->visited[nodeindex] = 1;
	
	for (j = 0; j < graph->count; j++)
	{
		if (graph->adj_matrix[nodeindex][j] > 0)
			enqueue(queue, j);
	}
	while (!isemptyqueue(queue))
	{
		nodeindex = dequeue(queue);
		if (graph->visited[nodeindex] == 0) {
			printf("%c ", indexToNode(graph, nodeindex));
			graph->visited[nodeindex] = 1;
			for (j = 0; j < graph->count; j++)
			{
				if (graph->adj_matrix[nodeindex][j] > 0)
					enqueue(queue, j);
			}
		}
	}
	//disconnected라도 모든 노드를 출력할 수 있도록.
	for (i = 0; i < graph->count; i++)
	{
		for (j = 0; j < graph->count; j++)
		{
			if (graph->adj_matrix[i][j] > 0)
				enqueue(queue, j);
		}
		while (!isemptyqueue(queue))
		{
			nodeindex = dequeue(queue);
			if (graph->visited[nodeindex] == 0) {
				printf("%c", indexToNode(graph, nodeindex));
				graph->visited[nodeindex] = 1;
				for (j = 0; j < graph->count; j++)
				{
					if (graph->adj_matrix[nodeindex][j] > 0)
						enqueue(queue, j);
				}
			}
		}
	}
	destroyqueue(queue);
	return;
}
int isemptygraph(GRAPH* graph) 
{
	if (graph->count == 0)
		return 1;
	else 
		return 0;
}


