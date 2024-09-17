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
	//���� �о ����� 1���� �迭 ����� �׷��� ����ü �����
	vrtxArr = createVrtxlist(fp, &start);	
	graph = creategraph(vrtxArr, start);
	//���� ó������ �ٽ� �о arc�� ����ġ �߰� (fseek Ȱ��)
	fseek(fp, 0, 0);	//fp(FILE* stream, long offset, int whence) whence 0 : ���� ó������
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
	//�迭�� �����͸� �ٸ� �Լ��� �޾��� �� �迭 ũ�⸦ �� �� ����,
	//�迭 �������� �ι��� �־��༭ ���� ���� �� �ֵ��� �ϱ�
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
		printf("�� �����÷ο�");
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
	//��� ���´� ���� ������ ����ġ
	//tv�� �߰��� ���� �迭���� 1
	int* TV = calloc(graph->count, sizeof(int));
	int** treeEdge;
	int edgecount = 0;
	int i,j;
	//�ּ��ڽ�Ʈ ���� ã�� �� ����ϴ� ����
	int leastcost;
	int low, column;
	char from, to;

	//���д� Ʈ�� ���� �����ϴ� 2���� �迭
	treeEdge = (int**)malloc((graph->count) * sizeof(int*));
	if (!treeEdge) {
		printf("�޸� �Ҵ� ����");
		exit(1);
	}
	for (i = 0; i < (graph->count); i++)
	{
		treeEdge[i] = (int*)calloc(2, sizeof(int));
		if (!treeEdge[i]) {
			printf("�޸� �Ҵ� ����");
			exit(1);
		}
	}

	TV[0] = 1; //���д� Ʈ���� ���۳�� �� �� �ֱ�
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
					if ((TV[j] == 0) && (graph->adj_matrix[i][j] > 0)) //tv�� ���� �������� ��� ��ġ
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