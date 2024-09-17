#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s_link.h"
#include "q_link.h"

typedef struct {
	int count;
	struct vertex* first;
	int (*compare) (void* argu1, void* argu2);
}GRAPH;

typedef struct vertex{
	struct vertex* pnextvrtx;
	void* dataptr;
	struct arc* pArc;
	int indeg;
	int outdeg;
	int processed;
}VERTEX;

typedef struct arc {
	struct vertex* destination;
	struct arc* pnextarc;
}ARC;

GRAPH* creategraph(int (*compare) (void* argu1, void* argu2)) {
	GRAPH* graphhead = (GRAPH*)malloc(sizeof(GRAPH));
	if (!graphhead) {
		printf("failed to create.");
		return NULL;
	}

	graphhead->count = 0;
	graphhead->compare = compare;
	graphhead->first = NULL;

	return graphhead;
}
void insVrtx(GRAPH* graph, void* dataptr)
{
	VERTEX* newVrtx;
	VERTEX* locPtr;
	VERTEX* prePtr;

	newVrtx = (VERTEX*)malloc(sizeof(VERTEX));
	if (newVrtx)
	{
		newVrtx->pnextvrtx = NULL;
		newVrtx->dataptr = dataptr;
		newVrtx->pArc = NULL;
		newVrtx->indeg = 0;
		newVrtx->outdeg = 0;
		newVrtx->processed = 0;
		(graph->count)++;
	} // if malloc
	else
		printf("�޸� �Ҵ� ����.\n"),
		exit(100);

	locPtr = graph->first;
	if (!locPtr)
		graph->first = newVrtx;
	else {
		prePtr = NULL;
		while (locPtr && (graph->compare(dataptr, locPtr->dataptr) > 0)) {
			prePtr = locPtr;
			locPtr = locPtr->pnextvrtx;
		}
		if (!prePtr)
			graph->first = newVrtx;
		else
			prePtr->pnextvrtx = newVrtx;
		newVrtx->pnextvrtx = locPtr;
	}
	return;
}
int dltVrtx(GRAPH* graph,void* dltkey)
{ 
	//return 1: dlt success, -1: degree not zero -2: dlt key not found

	VERTEX* prePtr;
	VERTEX* locPtr;

	if (!graph->first)
		return -2;

	prePtr = NULL;
	locPtr = graph->first;
	while (locPtr &&
		graph->compare(dltkey, locPtr->dataptr) > 0) {
		prePtr = locPtr;
		locPtr = locPtr->pnextvrtx;
	}
	if (!locPtr || graph->compare(locPtr->dataptr, dltkey) != 0)
		return -2; //���Ŵ�� �� ã�� ���
	if (locPtr->indeg != 0 || locPtr ->outdeg !=0)//ã������ arc�޷��ִ� ���
		//���Ŵ�� vertx�� ���� arc�������, ���Ŵ�� vrtx�� arc�� ����
		return -1; 

	if (!prePtr) 
		graph->first = locPtr->pnextvrtx; //�׷����� first �����ϴ� ���
	else
		prePtr->pnextvrtx = locPtr->pnextvrtx;

	graph->count--;
	free(locPtr);
	return 1;
}
int insArc(GRAPH* graph, void* fromKey, void* toKey) 
{
	//return 1: success, -1: heap overflow -2: fromKey not found -3: toKey not found
	ARC* newArc;
	ARC* preArc;
	ARC* locArc;
	VERTEX* fromVrtx;
	VERTEX* toVrtx;

	//�� arc�� �����Ҵ�
	newArc = (ARC*)malloc(sizeof(ARC));
	if (!newArc)
		return (-1);
	//fromvrtxã��
	fromVrtx = graph->first;
	while (fromVrtx && (graph->compare(fromKey, fromVrtx->dataptr) > 0))
		fromVrtx = fromVrtx->pnextvrtx;
	if (!fromVrtx || (graph->compare(fromKey, fromVrtx->dataptr) != 0))
		return -2;
	//tovrtxã��
	toVrtx = graph->first;
	while (toVrtx && (graph->compare(toKey, toVrtx->dataptr) > 0))
		toVrtx = toVrtx->pnextvrtx;
	if (!toVrtx || (graph->compare(toKey, toVrtx->dataptr) != 0))
		return -3;
	//arc �����ϱ�
	++fromVrtx->outdeg;
	++toVrtx->indeg;
	newArc->destination = toVrtx;
	//fromVrtx�� arc�� �ϳ��� ���� ���
	if (!fromVrtx->pArc){
		fromVrtx->pArc = newArc;
		newArc->pnextarc = NULL;
		return 1;
	}
	//fromVrtx�� arc�� �ϳ� �̻��� ��� ��arc ���� ��ġ Ž��
	preArc = NULL;
	locArc = fromVrtx->pArc;
	while (locArc &&
		graph->compare(toKey, locArc->destination->dataptr) <= 0)
	{
		preArc = locArc;
		locArc = locArc->pnextarc;
	}
	if (!preArc) //adjacency list�� ù��°�� �߰��ϴ� ���
		fromVrtx->pArc = newArc;
	else
		preArc->pnextarc = newArc;
	newArc->pnextarc = locArc;
	return 1;
}
int dltArc(GRAPH* graph, void* fromKey, void* toKey)
{	
	//return 1: success -2: fromKey not found -3: toKey not found
	VERTEX* fromVrtx;
	VERTEX* toVrtx;
	ARC* preArc;
	ARC* locArc;
	
	//vertex ���� ���
	if (!graph->first)
		return -2;
	//fromvrtxã��
	fromVrtx = graph->first;
	while (fromVrtx && (graph->compare(fromKey, fromVrtx->dataptr) > 0))
		fromVrtx = fromVrtx->pnextvrtx;
	if (!fromVrtx || (graph->compare(fromKey, fromVrtx->dataptr) != 0))
		return -2;
	//adjacency list���� toKey�� �´�destination���� arcã��
	if (!fromVrtx->pArc)
		return -3;
	preArc = NULL;
	locArc = fromVrtx->pArc;
	
	while (locArc && (graph->compare(toKey, locArc->destination->dataptr) > 0)) {
		preArc = locArc;
		locArc = locArc->pnextarc;
	}
	if (!locArc || (graph->compare(toKey, locArc->destination->dataptr) != 0))
		return -3;
	toVrtx = locArc->destination;
	//arc�����ϱ�
	fromVrtx->outdeg--;
	toVrtx->indeg--;
	if (!preArc)
		fromVrtx->pArc = locArc->pnextarc;
	else
		preArc->pnextarc = locArc->pnextarc;
	free(locArc);
	return 1;
}
void DFtraverse(GRAPH* graph, void (*process) (void* dataPtr)) 
{
	int success;
	VERTEX* walkVrtx;
	VERTEX* vrtxPtr;
	VERTEX* toVrtxPtr;
	ARC* arcPtr;
	STACK* stack;

	if (isemptygraph(graph))
		return;
	
	//��� vertex�� ���μ����� �÷��׸� 0���� �ʱ�ȭ
	walkVrtx = graph->first;
	while (walkVrtx){
		walkVrtx->processed = 0;
		walkVrtx = walkVrtx->pnextvrtx;
	}

	//������ vertex�� ���������� �Ͽ� ��� vertex�� ���� traverse
	stack = createstack();
	walkVrtx = graph->first;
	while (walkVrtx){
		if (walkVrtx->processed == 0){
			success = push(stack,walkVrtx);
			if (!success){
				printf("���� �����÷ο� �߻�.");
				exit(1);
			}
			while (!isemptystack(stack)){
				vrtxPtr = (VERTEX*)pop(stack);
				if (vrtxPtr->processed == 0) { //unprocessed�� process 
					process(vrtxPtr->dataptr);
					vrtxPtr->processed = 1;
				}
				//��� unproccessed adjacency vrtx Ǫ��
				arcPtr = vrtxPtr->pArc;
				while (arcPtr) {
					toVrtxPtr = arcPtr->destination;
					success = push(stack, toVrtxPtr);
					if (!success) {
						printf("���� �����÷ο� �߻�.");
						exit(1);
					}
					arcPtr = arcPtr->pnextarc;
				}
			}
		}
		walkVrtx = walkVrtx->pnextvrtx;
	}
	destroystack(stack);
	return;
}
void BFtraverse(GRAPH* graph, void (*process) (void* dataPtr))
{
	int success;
	VERTEX* walkVrtx;
	VERTEX* vrtxPtr;
	VERTEX* toVrtxPtr;
	ARC* arcPtr;
	QUEUE* queue;

	if (isemptygraph(graph))
		return;

	//��� vertex�� ���μ����� �÷��׸� 0���� �ʱ�ȭ
	walkVrtx = graph->first;
	while (walkVrtx) {
		walkVrtx->processed = 0;
		walkVrtx = walkVrtx->pnextvrtx;
	}
	//������ vertex�� ���������� �Ͽ� ��� vertex�� ���� traverse
	queue = createqueue();
	walkVrtx = graph->first;
	while (walkVrtx) {
		if (walkVrtx->processed == 0) {
			success = enqueue(queue, walkVrtx);
			if (!success) {
				printf("�����÷ο� �߻�.");
				exit(1);
			}
			while (!isemptyqueue(queue)) { //unprocessed�� process 
				vrtxPtr = (VERTEX*)dequeue(queue);
				if (vrtxPtr->processed == 0){
					process(vrtxPtr->dataptr);
					vrtxPtr->processed = 1;
				}
				//��� adjacency vrtx ť�� �ֱ�
				arcPtr = vrtxPtr->pArc;
				while (arcPtr) {
					toVrtxPtr = arcPtr->destination;
					success = enqueue(queue, toVrtxPtr);
					if (!success) {
						printf("�����÷ο� �߻�.");
						exit(1);
					}
				arcPtr = arcPtr->pnextarc;
				}
			}
		}
		walkVrtx = walkVrtx->pnextvrtx;
	}
	destroyqueue(queue);
	return;
}
int isemptygraph(GRAPH* graph) {
	if (graph->count == 0)
		return 1;
	else
		return 0;
}