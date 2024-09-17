#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int H_element;

typedef struct heaphead{
	int size, maxsize;
	H_element* heapArr;
}HEAP;

HEAP* createheap(int maxsize)
{
	HEAP* newheap = (HEAP*)malloc(maxsize * sizeof(H_element));
	if (!newheap)
	{
		printf("�޸� �Ҵ� ����.");
		return NULL;
	}

	newheap->heapArr = (H_element*)calloc(maxsize, sizeof(H_element));
	if (!newheap->heapArr)
	{
		printf("�޸� �Ҵ� ����.");
		free(newheap);
		return NULL;
	}

	newheap->size = 0;
	newheap->maxsize = maxsize;

	return newheap;
}
void reheapup(HEAP* heap, int idx) 
{
	int parentidx;
	H_element curdata;

	//idx�� ��ȿ�Ѱ�
	if (idx <= 0 || idx >= heap->size)
		return;

	//parent�� ���ϸ鼭 �� ũ�ٸ� ���� �ø���
	curdata = heap->heapArr[idx];
	parentidx = (idx-1) / 2;
	while (idx > 0 && curdata > heap->heapArr[parentidx]) {
		heap->heapArr[idx] = heap->heapArr[parentidx];
		idx = parentidx;
		parentidx = (idx - 1) / 2;
	}

	heap->heapArr[idx] = curdata;
}
void reheapdown(HEAP* heap, int idx)
{
	int maxChild;
	H_element curData = 0;

	if (idx < 0 || idx >= heap->size)
		return;

	curData = heap->heapArr[idx];

	while (idx * 2 + 1 < heap->size) {
		//left rigt child�� �� ū ��?
		maxChild = idx * 2 + 1;
		if (maxChild + 1 < heap->size && heap->heapArr[maxChild + 1] > heap->heapArr[maxChild])
			maxChild++;
		//��� �������� ������ �Ѵٸ� child�� ��ȯ
		if (heap->heapArr[maxChild] > curData) {
			heap->heapArr[idx] = heap->heapArr[maxChild];
			idx = maxChild;
		}
		else
			break;
	}
	heap->heapArr[idx] = curData;

}
void insertHeap(HEAP* heap, H_element data)
{
	if (heap->size >= heap->maxsize){
		printf("heap is full");
		return;
	}

	//�� ���Ҹ� �� �������� �߰��ϰ� �´� �ڸ� ã��
	heap->heapArr[heap->size++] = data;
	reheapup(heap, heap->size - 1);
}
int deleteHeap(HEAP* heap, H_element* output)
{
	if (heap->size <= 0) {
		printf("Heap is empty!\n");
		return 0;
	}
	*output = heap->heapArr[0];
	//�� ���� ���� ���� ������ ���Ҹ� �ֱ�
	heap->heapArr[0] = heap->heapArr[--heap->size];
	reheapdown(heap, 0);
	return 1;
}
void destroyheap(HEAP* heap)
{
	free(heap->heapArr);
	free(heap);
}
void buildheap(HEAP* Heap)
{
	int i = 0;
	for (i = 1; i < Heap->size; i++)
		reheapup(Heap, i);
}