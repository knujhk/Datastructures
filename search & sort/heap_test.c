#include <stdio.h>
#include "heap.h"

int main()
{
	HEAP* heap;
	int i,j, heapout;

	heap = createheap(10);

	insertHeap(heap, 3);
	insertHeap(heap, 7);
	insertHeap(heap, 8);
	insertHeap(heap, 8);
	insertHeap(heap, 2);
	insertHeap(heap, 10);
	insertHeap(heap, 83);
	insertHeap(heap, 999);
	printf("%d", heap->size);

	while(heap->size>0)	{
		printf("\n");
		for ( j = 0; j < heap->size; j++)
		{
			printf("%d ", heap->heapArr[j]);
		}
		printf("size :%d", heap->size);
		deleteHeap(heap, &heapout);
	}
	printf("\n%d", heap->size);

	return 0;
}