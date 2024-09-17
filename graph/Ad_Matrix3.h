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
	
	//�׷��� ����ü�� �����Ҵ�
	graph = (GRAPH*)malloc(sizeof(GRAPH));
	if (!graph)
		return NULL;

	graph->vrtxArr = vrtxArr;
	graph->start = startnode;
	//��� �迭�� ���� ���� ���ϱ�
	while (graph->vrtxArr[i] != '\0') 
		i++;
	graph->count = i; //�ι��� �ε��� = ������ ��� �ε���+1 (ī��Ʈ)

	//��� �湮���� Ȯ���ϴ� �迭 �ʱ�ȭ
	graph->visited = (int*)calloc(graph->count,sizeof(int));
	//����� �´� 2���� �迭 �����
	int** matrix = (int**)malloc((graph->count) * sizeof(int*));
	if (!matrix) {
		printf("�޸� �Ҵ� ����");
		exit(1);
	}
	for ( i = 0; i < (graph->count); i++)
	{
		matrix[i] = (int*)calloc((graph->count), sizeof(int));
		if (!matrix[i]) {
			printf("�޸� �Ҵ� ����");
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

	i = nodeToindex(graph, from); //��
	j = nodeToindex(graph, to);	//��
	
	if (i<0 || j<0)
		return 0;
	
	graph->adj_matrix[i][j] = weight;
	graph->adj_matrix[j][i] = weight;
	return 1;
}
int dltArc(GRAPH* graph, char from, char to) 
{
	int i,  j;

	i = nodeToindex(graph, from); //��
	j = nodeToindex(graph, to);	//��

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
 
	// pop�ϰ�print,  arcȮ�� 
	
	stack = createstack();
	clearvisited(graph);
	//������ ���
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
		if (graph->visited[nodeindex] == 0)		//�湮�� �� ���� ��常 ó��
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
	//disconnected�� ��� ��带 ����� �� �ֵ���.
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
			if (graph->visited[nodeindex] == 0)		//�湮�� �� ���� ��常 ó��
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
	//ù��° ��� ���, 
	// dequeue�ϰ�print,  arcȮ��(enqueue�ϰ� �ش� �� �� �����), 

	queue = createqueue();
	clearvisited(graph);
	//������ ���
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
	//disconnected�� ��� ��带 ����� �� �ֵ���.
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


