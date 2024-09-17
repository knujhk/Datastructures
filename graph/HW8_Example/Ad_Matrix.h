#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Ad_Queue.h"

typedef struct graph {
	char vertex[26];
	int arc[26][26];
	int count;
}Graph;

Graph* CreateGraph();
int InsertVertex(Graph*, char);
int InsertArc(Graph*, char, char);
void DeleteArc(Graph*, char, char);
void DepthFirstTraversal(Graph*, char);
void BreadthFirstTraversal(Graph*, char);
bool IsFull(Graph*);
bool IsEmpty(Graph*);
void PrintGraph(Graph*);
void ClearVisit(Graph*);

Graph* CreateGraph() {
	Graph* gptr = (Graph*)malloc(sizeof(Graph));
	if (gptr == NULL) {
		printf("Failed to create memory.\n");
		return NULL;
	}
	for (int i = 0;i < 26;i++) {
		gptr->vertex[i] = '\n';
	}
	for (int i = 0;i < 26;i++) {
		for (int j = 0;j < 26;j++)
			gptr->arc[i][j] = -1;
	}
	gptr->count = 0;
	return gptr;
}

int InsertVertex(Graph* gptr, char data) {
	if (gptr->count >= 26) {
		printf("Graph is Full.\n");
		return 1;
	}
	else {
		gptr->vertex[data-'A'] = data;
		gptr->count = 0;
		for (int i = 0;i < 26;i++) {
			if (data > 'A')
				gptr->arc[data - 'A'][i] = 0;
			if (gptr->vertex[i] != '\n') {
				gptr->count++;
			}
		}
		return 0;
	}
}

int InsertArc(Graph* gptr, char start, char dest) {
	if (gptr->arc[start - 'A'][dest - 'A'] == 1) {
		printf("%c to %c Arc is already in Graph.\n", start, dest);
	}
	else
		gptr->arc[start - 'A'][dest - 'A'] = 1;
	return 0;
}

void DeleteArc(Graph* gptr, char start, char dest) {
	if (gptr->arc[start - 'A'][dest - 'A'] == 0) {
		printf("Failed to Delete Arc.\n");
		printf("%c to %c Arc is not in Graph.\n", start, dest);
	}
	else
		gptr->arc[start - 'A'][dest - 'A'] = 0;
	return;
}
void DepthFirstTraversal(Graph* gptr, char data) {
	if (gptr->vertex[data - 'A'] == '\n')
		return;
	printf("%c ", gptr->vertex[data - 'A']);
	gptr->vertex[data - 'A'] = '\n';
	for (int i = 0;i < 26;i++) {
		if (gptr->arc[data - 'A'][i] == 1 && gptr->vertex[i] != '\n')
			DepthFirstTraversal(gptr, gptr->vertex[i]);
	}
}

void BreadthFirstTraversal(Graph* gptr, char data) {
	Queue* q = CreateQueue();
	char a;

	Enqueue(q, data);
	while (IsEmptyQueue(q) == false) {
		a = Dequeue(q);
		if (gptr->vertex[a - 'A'] != '\n') {
			printf("%c ", a);
			gptr->vertex[a - 'A'] = '\n';
		}
		for (int i = 0;i < 26;i++) {
			if (gptr->arc[a - 'A'][i] == 1)
				Enqueue(q, gptr->vertex[i]);
		}
	}
	ClearVisit(gptr);
	DestroyQueue(q);
	return;

}

bool IsFull(Graph* gptr) {
	if (gptr->count == 26)
		return true;
	else 
		return false;
}

bool IsEmpty(Graph* gptr) {
	if (gptr->count == 0)
		return true;
	else 
		return false;
}

void PrintGraph(Graph* gptr) {
	for (int i = 0;i < 26;i++) {
		if (gptr->vertex[i] != '\n') {
			printf("%c : ", gptr->vertex[i]);
			for (int j = 0;j < 26;j++) {
				if (gptr->arc[i][j] == 1)
					printf("%c ", j + 'A');
			}
			printf("\n");
		}
	}
	return;
}

void ClearVisit(Graph* gptr) {
	for (int i = 0;i < 26;i++) {
		for (int j = 0;j < 26;j++) {
			if (gptr->arc[i][j] != -1) {
				gptr->vertex[i] = i + 'A';
				break;
			}
		}
	}
	return;
}
