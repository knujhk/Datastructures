#include "Ad_Queue.h"

typedef struct graph {
	int count;
	struct vertex* headVertex;
}Graph;

typedef struct vertex {
	char data;
	struct vertex* nextVertex;
	struct arc* headArc;
	int inDegree;
	int outDegree;
	bool visited;
}Vertex;

typedef struct arc {
	struct vertex* dest;
	struct arc* nextArc;
}Arc;

Graph* CreateGraph();
int InsertVertex(Graph*, char);
void DeleteVertex(Graph*, char);
int InsertArc(Graph*, char, char);
void DeleteArc(Graph*, char, char);
Vertex* FindVertex(Graph*, char);
void PrintGraph(Graph*);
void DepthFirstTraversal(Vertex*);
void BreadthFirstTraversal(Graph*, char);
void ClearVisit(Graph* gptr);

Graph* CreateGraph() {
	Graph* gptr = (Graph*)malloc(sizeof(Graph));
	if (gptr == NULL) {
		printf("Failed to create Graph.\n");
		return NULL;
	}
	gptr->count = 0;
	gptr->headVertex = NULL;
	return gptr;
}

int InsertVertex(Graph* gptr, char data) {
	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	Vertex* temp = NULL;
	Vertex* pre = NULL;
	if (newVertex == NULL) {
		printf("Failed to create vertex.\n");
		return 1;	//if failed to allocate memory return 1
	}
	newVertex->data = data;
	newVertex->nextVertex = NULL;
	newVertex->headArc = NULL;
	newVertex->inDegree = 0;
	newVertex->outDegree = 0;
	newVertex->visited = false;

	if (gptr->count == 0) {
		gptr->headVertex = newVertex;
		gptr->count = 1;
		return 0;
	}
	else {
		temp = gptr->headVertex;
		for (int i = 0;i < gptr->count;i++) {
			if (temp->data == data) {
				printf("%c is already in Graph.\n", data);
				return 2;	//if data is already in Graph, return 2
			}
			else if (temp->data < data) {
				pre = temp;
				temp = temp->nextVertex;
			}
			else if (temp->data > data) {
				newVertex->nextVertex = temp;
				if (i == 0)
					gptr->headVertex = newVertex;
				else
					pre->nextVertex = newVertex;
				gptr->count++;
				return 0;	//if InsertVertex sucessfully, return 0
			}
		}
		pre->nextVertex = newVertex;
		gptr->count++;
		return 0;	//if InsertVertex sucessfully, return 0
	}
}

void DeleteVertex(Graph* gptr, char data) {
	Vertex* temp = NULL;
	Vertex* pre = NULL;
	if (gptr->count == 0) {
		printf("Failed to Delete Vertex.\n");
		printf("Graph is Empty.\n");
	}
	else {
		temp = gptr->headVertex;
		for (int i = 0;i < gptr->count;i++) {
			if (temp->data == data) {
				if (i == 0)
					gptr->headVertex = temp->nextVertex;
				else
					pre->nextVertex = temp->nextVertex;
				gptr->count--;
				free(temp);
				return;
			}
			pre = temp;
			temp = temp->nextVertex;
		}
		printf("Failed to Delete Vertex.\n");
		printf("%c is not in Graph.\n", data);
	}
	return;
}

int InsertArc(Graph* gptr, char start, char dest) {
	Vertex* startVertex = NULL;
	Vertex* destVertex = NULL;
	Arc* nowArc = NULL;
	Arc* preArc = NULL;
	Arc* newArc = (Arc*)malloc(sizeof(Arc));
	if (newArc == NULL) {
		printf("failed to create arc.\n");
		return 1;	//if failed to allocate memory return 1
	}
	startVertex = FindVertex(gptr, start);
	destVertex = FindVertex(gptr, dest);
	newArc->dest = destVertex;
	newArc->nextArc = NULL;
	nowArc = startVertex->headArc;
	preArc = startVertex->headArc;
	if (nowArc == NULL) {
		startVertex->headArc = newArc;
		startVertex->outDegree++;
		destVertex->inDegree++;
	}
	else {
		for (int i = 0;i < startVertex->outDegree;i++) {
			if (nowArc->dest->data == dest) {
				printf("%c to %c Arc is already in graph.\n", start, dest);
				return 2;
			}
			else if (nowArc->dest->data < dest) {
				preArc = nowArc;
				nowArc = nowArc->nextArc;
			}
			else if(nowArc->dest->data > dest) {
				newArc->nextArc = nowArc;
				if (i == 0)
					startVertex->headArc = newArc;
				else
					preArc->nextArc = newArc;
				startVertex->outDegree++;
				destVertex->inDegree++;
				return 0;
			}
		}
		preArc->nextArc = newArc;
		startVertex->outDegree++;
		destVertex->inDegree++;
		return 0;
	}
}

void DeleteArc(Graph* gptr, char start, char dest) {
	Vertex* startVertex = FindVertex(gptr, start);
	Vertex* destVertex = FindVertex(gptr, dest);
	Arc* Atemp = startVertex->headArc;
	Arc* pre = NULL;
	if (gptr->count == 0) {
		printf("Failed to Delete Arc.\n");
		printf("Graph is Empty.\n");
	}
	else if (startVertex->outDegree == 0) {
		printf("Failed to Delete Arc.\n");
		printf("There is no Arc from %c.\n", start);
	}
	else {
		//Atemp = gptr->headVertex;
		for (int i = 0;i < startVertex->outDegree;i++) {
			if (Atemp->dest->data == dest) {
				if (i == 0)
					startVertex->headArc = Atemp->nextArc;
				else
					pre->nextArc = Atemp->nextArc;
				startVertex->outDegree--;
				destVertex->inDegree--;
				free(Atemp);
				return;
			}
			pre = Atemp;
			Atemp = Atemp->nextArc;
		}
		printf("Failed to Delete Arc.\n");
		printf("%c to %c Arc is not in Graph.\n", start, dest);
	}
	return;
}

Vertex* FindVertex(Graph* gptr, char data) {
	Vertex* found = NULL;
	found = gptr->headVertex;
	for (int i = 0;i < gptr->count;i++) {
		if (found->data == data)
			return found;
		found = found->nextVertex;
	}
	return NULL;
}

Arc* FindArc(Vertex* vptr, char data) {
	Arc* found = NULL;
	found = vptr->headArc;
	for (int i = 0;i < vptr->outDegree;i++) {
		if (found->dest->data == data)
			return found;
		found = found->nextArc;
	}
	return NULL;
}

void PrintGraph(Graph* gptr) {
	Vertex* Vtemp = gptr->headVertex;
	Arc* Atemp = NULL;
	while (Vtemp != NULL) {
		Atemp = Vtemp->headArc;
		printf("%c : ", Vtemp->data);
		while (Atemp != NULL) {
			printf("%c ", Atemp->dest->data);
			Atemp = Atemp->nextArc;
		}
		printf("\n");
		Vtemp = Vtemp->nextVertex;
	}
}

void DepthFirstTraversal(Vertex* start) {
	Arc* Atemp = NULL;
	if (start->visited == true)
		return;
	printf("%c ", start->data);
	start->visited = true;
	for (Atemp = start->headArc;Atemp != NULL;Atemp = Atemp->nextArc) {
		if (Atemp->dest->visited == false)
			DepthFirstTraversal(Atemp->dest);
	}
}

void BreadthFirstTraversal(Graph* gptr, char data) {
	Vertex* Vtemp = NULL;
	Queue* q = CreateQueue();
	Arc* Atemp = NULL;
	char a;
	Enqueue(q, data);
	while (IsEmptyQueue(q) == false) {
		a = Dequeue(q);
		Vtemp = FindVertex(gptr, a);
		if (Vtemp->visited == false) {
			printf("%c ", Vtemp->data);
			Vtemp->visited = true;

		}
		for (Atemp = Vtemp->headArc;Atemp != NULL;Atemp = Atemp->nextArc) {
			if (Atemp->dest->visited == false) {
			Enqueue(q, Atemp->dest->data);
			}
		}
	}
	return;
}

void ClearVisit(Graph* gptr) {
	Vertex* Vtemp = gptr->headVertex;
	while (Vtemp != NULL) {
		Vtemp->visited = false;
		Vtemp = Vtemp->nextVertex;
	}
	return;
}