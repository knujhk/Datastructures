#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph {
	char vertex[26];
	int arc[26][26];
	int count;
}Graph;

Graph* CreateGraph();
int InsertVertex(Graph*, char);
int InsertArc(Graph*, char, char, int);
void DeleteArc(Graph*, char, char);
bool IsFull(Graph*);
bool IsEmpty(Graph*);
void PrintGraph(Graph*);
void ClearVisit(Graph*);
void MinimumSpanningTree(Graph*, char);
void ShortestPath(Graph*, char);

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
	else if(gptr->count < 26){
		gptr->vertex[data - 'A'] = data;
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

int InsertArc(Graph* gptr, char start, char dest, int prior) {
	if (gptr->arc[start - 'A'][dest - 'A'] > 0) {
		printf("%c to %c Arc is already in Graph.\n", start, dest);
		return 1;
	}
	else {
		gptr->arc[start - 'A'][dest - 'A'] = prior;
		gptr->arc[dest - 'A'][start - 'A'] = prior;
		return 0;
	}
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
				if (gptr->arc[i][j] > 0) {
					printf("%c ", j + 'A');
					printf("(%d) ", gptr->arc[i][j]);
				}
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
int FindMinIndex(Graph* gptr, char start) {
	int idx;
	int min;
	for (int i = 0;i < 26;i++) {
		if (gptr->arc[start - 'A'][i] > 0) {
			min = gptr->arc[start - 'A'][i];
			idx = i;
			break;
		}
	}
	for (int i = 0;i < 26;i++) {
		if(gptr->arc[start-'A'][i] > 0){
			if (gptr->arc[start - 'A'][i] < min) {
				min = gptr->arc[start - 'A'][i];
				idx = i;
			}
		}
	}
	return idx;
}

void MinimumSpanningTree(Graph* gptr, char start) {
	int T[26][2];
	int TV[26];
	int count = 0;
	bool isIncluded;

	for (int i = 0; i < 26; i++) {
		T[i][0] = -1;
		T[i][1] = -1;
		TV[i] = -1;
	}

	TV[0] = (int)(start - 'A');

	while (count < gptr->count - 1) {
		int minEdge[3] = { -1, -1, 1000 };
		for (int i = 0; i < count + 1; i++) {
			int now = TV[i];
			for (int j = 0; j < 26; j++) {
				if (gptr->arc[now][j] > 0 && gptr->arc[now][j] < minEdge[2]) {
					isIncluded = false;
					for (int k = 0; k < count + 1; k++) {
						if (j == TV[k]) {
							isIncluded = true;
							break;
						}
					}
					if (isIncluded) {
						continue;
					}
					minEdge[0] = now;
					minEdge[1] = j;
					minEdge[2] = gptr->arc[now][j];
				}
			}
		}

		if (minEdge[0] == -1) {
			break;
		}

		TV[count + 1] = minEdge[1];
		T[count][0] = minEdge[0];
		T[count][1] = minEdge[1];
		count++;
	}

	if (count < gptr->count - 1) {
		printf("no spanning tree\n");
		return;
	}

	for (int i = 0; i < count; i++) {
		printf("%c %c : (%d)\n", 'A' + T[i][0], 'A' + T[i][1], gptr->arc[T[i][0]][T[i][1]]);
	}
	return;
}

void ShortestPath(Graph* gptr, char start) {
	int count = 0;
	int dist[26];
	int cost[26][26];
	int TV[26];
	bool found[26];
	bool update;
	int startIdx = start - 'A';
	int destIdx;
	int nowVerIdx;
	int tempmin;

	for (int i = 0;i < 26;i++) {
		found[i] = false;
		TV[i] = -1;
		for (int j = 0;j < 26;j++) {
			if (gptr->arc[i][j] <= 0) {
				cost[i][j] = 1000;
			}
			else {
				cost[i][j] = gptr->arc[i][j];
			}
			if (i == j)
				cost[i][j] = 0;
		}
	}

	for (int i = 0;i < 26;i++) {
		if (gptr->vertex[i] != '\n' && gptr->vertex[i] != start) {
			dist[i] = cost[startIdx][i];
			printf("%c %c : %d\n", start, gptr->vertex[i], dist[i]);
		}
	}
	printf("\n");
	found[start - 'A'] = true;
	
	while(count < gptr->count - 1) {
		update = false;
		tempmin = 1000;
		for (int i = 0;i < 26;i++) {
			if (found[i] == true) {
				nowVerIdx = i;
				for (int j = 0;j < 26;j++) {
					if (cost[i][j] > 0 && cost[i][j] < tempmin && found[j] == false) {
						tempmin = cost[i][j];
						destIdx = j;
						startIdx = i;
					}
				}
			}
		}
		if (tempmin == 1000) {
			break;
		}
		update = true;
		found[destIdx] = true;
		count++;
		for (int k = 0; k < 26;k++) {
			if (found[k] == false && dist[destIdx] + cost[destIdx][k] < dist[k])
				dist[k] = dist[destIdx] + cost[destIdx][k];
		}
		if (update = true) {
			for (int i = 0;i < 26;i++) {
				if (gptr->vertex[i] != '\n' && gptr->vertex[i] != start) {
					printf("%c %c : %d\n", start, gptr->vertex[i], dist[i]);
				}
			}
			printf("\n");
		}
	}
	if (count < gptr->count - 1) {
		printf("There is no Shortest Path.\n");
		return;
	}
	else
		return;
}