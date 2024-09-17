#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int* createArr(FILE*, int*);
void heapsort(int* , int );
void insertionsort(int* , int );
void bubblesort(int* ,int);
void quicksort(int*, int);
void _quicksort(int*, int, int);
void swap(int*, int*);
void mergesort(int [],int [], int, int);
void merge(int [],int [], int, int, int);

int main()
{
	int menu, i;
	int count;
	int* arr = NULL;
	int* sorted = NULL;
	char filename[30] = { '\0' };
	FILE* fp = NULL;
	
	while (1)
	{
		printf("input file name : ");
		do {
			rewind(stdin);
			fgets(filename, sizeof(filename), stdin);
			filename[strlen(filename) - 1] = '\0';
			fp = fopen(filename, "r");
		} while (!fp);

		arr = createArr(fp, &count);

		printf("choose a sorting method to use (selection : 0, intsertion : 1 bubble : 2 quick : 3, merge : 4 ) : ");
		while (fscanf(stdin, "%d", &menu) != 1 || (menu < 0 || menu > 5)) {
			rewind(stdin);
			printf("0~4 범위 정수를 입력하시오 : ");
		}
		switch (menu)
		{
		case 0:	//selection(heap)
			heapsort(arr, count);
			break;
		case 1:	//insertion 
			insertionsort(arr, count);
			break;
		case 2:	//bubble
			bubblesort(arr, count);
			break;
		case 3:	//quick
			//quicksort(arr, count);
			quicksort(arr, count);
			break;
		case 4:	//merge
			sorted = (int*)calloc(count, sizeof(int));
			if (!sorted) {
				printf("메모리 할당 오류");
				exit(1);
			}
			mergesort(arr, sorted, 0, count - 1);
			free(sorted);
			break;
		default:
			break;
		}

		printf("\nthe numbers sorted : \n");
		for (i = 0; i < count; i++) {
			printf("%d\n", arr[i]);
		}
		printf("\n");
	}
	return 0;
}
int* createArr(FILE* fp, int* count) {
	int i = 0, flag;
	int temp;
	int* arr = NULL;

	*count = 0;
	//동적할당 위해 자료 개수 구하기
	flag = fscanf(fp, "%d", &temp);
	while (flag != EOF){
		*count += flag;
		flag = fscanf(fp, "%d", &temp);
	}
	fseek(fp, 0, 0);

	arr = (int*)calloc((*count), sizeof(int));
	if (!arr)
	{
		printf("메모리 할당 오류");
		exit(1);
	}
	flag = fscanf(fp, "%d", &temp);
	while (flag != EOF) {
		arr[i] = temp;
		i++;
		flag = fscanf(fp, "%d", &temp);
	}

	return arr;
}
void heapsort(int* arr, int count)
{
	int i, output = 0;;
	HEAP* heap;
	heap = createheap(count);
	heap->maxsize = count;
	heap->size = count;
	heap->heapArr = arr;

	buildheap(heap);
	for ( i = 0; i < count; i++){
		deleteHeap(heap, &output);
		arr[count-i-1] = output;
	}
	return;
}
void insertionsort(int * arr, int count)
{
	int wall, i;
	int hold = 0;

	for ( wall = 1; wall < count; wall++){
		hold = arr[wall];
		for ( i = wall; i > 0 &&  hold < arr[i - 1]; i--)
			arr[i] = arr[i - 1];
		arr[i] = hold;
	}
}
void bubblesort(int* arr,int count)
{
	int i = 0, j = 0;
	int temp = 0;
	int sorted = 0;
	for (i = 0; i < count && !sorted; i++) {
		for (j = count - 1, sorted = 1; j > i; j--) {
			if (arr[j] < arr[j - 1]) {
				sorted = 0; 
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}
void swap(int* a, int* b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;

	return;
}
void _quicksort(int* arr, int left, int right)
{
	int pivot = 0, i = 0, j = 0;
	
	if (left < right) {
		i = left;
		j = right + 1;
		pivot = arr[left];

		do {
			do {
				i++;
			} while (arr[i] < pivot );
			do {
				j--;
			} while (arr[j] > pivot );
			if (i < j)
				swap(&(arr[i]), &(arr[j]));
		} while (i < j);
		swap(&(arr[left]), &(arr[j]));

		_quicksort(arr, left, j - 1);
		_quicksort(arr, j + 1, right);
	}
}
void quicksort(int* arr, int count)
{
	int left, right;

	left = 0;
	right = count - 1;
	_quicksort(arr, left, right);
}
void mergesort(int arr[],int sorted[], int left, int right)
{
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		mergesort(arr,sorted, left, mid);
		mergesort(arr,sorted, mid+1, right);
		merge(arr,sorted, left, mid, right);
	}
}
void merge(int* arr, int* sorted, int left, int mid, int right)
{
	int i, j, k, t;

	i = left; 
	j = mid +1;
	k = left;

	while (i <= mid && j<= right)
	{
		if (arr[i] < arr[j])
			sorted[k++] = arr[i++];
		else
			sorted[k++] = arr[j++];
	}
	if (i <= mid) //첫번째 배열의 원소가 남은 경우
	{
		for (t = i; t <= mid; t++)
			sorted[k++] = arr[t];
	}
	else {		//두번째 배열의 원소가 남은 경우
		for (t = j; t <= right; t++)
			sorted[k++] = arr[t];
	}

	//임시 배열 sorted의 원소를 arr에 복사
	for ( t = left; t <= right; t++)
	{
		arr[t] = sorted[t];
	}
}