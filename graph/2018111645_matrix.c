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
	//���� �о ����� 1���� �迭 ����� �׷��� ����ü �����
	vrtxArr = createVrtxlist(fp, &start);	
	graph = creategraph(vrtxArr, start);
	//���� ó������ �ٽ� �о arc �߰� (fseek Ȱ��)
	fseek(fp, 0, 0);	//fp(FILE* stream, long offset, int whence) whence 0 : ���� ó������
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
	//�迭�� �����͸� �ٸ� �Լ��� �޾��� �� �迭 ũ�⸦ �� �� ����,
	//�迭 �������� �ι��� �־��༭ ���� ���� �� �ֵ��� �ϱ�
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