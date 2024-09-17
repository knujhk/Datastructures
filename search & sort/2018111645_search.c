#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int* createArr(FILE*, int*);
void insertionsort(int*, int);
int binary_search(int* , int , int , int* );
int* createHash(FILE* , int*,int* );
int hash_search(int*, int, int,int);

int main()
{
	int menu, i, target, loc, flag;
	int count, maxcollision = 0;
	int* arr = NULL;
	char filename[30] = { '\0' };
	FILE* fp = NULL;

	while (1) {
		printf("input file name : ");
		
		do {
			rewind(stdin);
			fgets(filename, sizeof(filename), stdin);
			filename[strlen(filename) - 1] = '\0';
			fp = fopen(filename, "r");
		} while (!fp);

		printf("target integer : ");
		while (fscanf(stdin, "%d", &target) != 1) {
			rewind(stdin);
			printf("정수를 입력하시오 : ");
		}
		
		printf("\n\nchoose a searching method to use (binary : 1, hashed : 2) : ");
		while (fscanf(stdin, "%d", &menu) != 1 || (menu < 1 || menu > 2)) {
			rewind(stdin);
			printf("1또는 2를 입력하시오 : ");
		}
		switch (menu)
		{
		case 1:	//binary search
			arr = createArr(fp, &count);
			insertionsort(arr, count);
			if (binary_search(arr, count, target, &loc))
				printf("%d is found", target);
			else
				printf("%d is not found", target);
			break;
		case 2: //hashed search
			arr = createHash(fp, &count, &maxcollision);
			if (hash_search(arr, target, count, maxcollision))
				printf("%d is found", target);
			else
				printf("%d is not found", target);
			break;
		default:
			break;
		}
		printf("\n\n");
		fclose(fp);
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
	while (flag != EOF) {
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
int* createHash(FILE* fp, int* count, int* maxcollision) {
	int i = 0, flag;
	int temp, newidx, listsize;
	int* arr = NULL;
	int collision;

	*count = 0;
	//동적할당 위해 자료 개수 구하기
	while (1) {
		flag = fscanf(fp, "%d", &temp);
		if (flag == EOF)
			break;
		else
			*count += flag;
	}
	fseek(fp, 0, 0);
	listsize = 3 * (*count);
	//배열 만들기
	arr = (int*)calloc(listsize,sizeof(int));
	if (!arr)
	{
		printf("메모리 할당 오류");
		exit(1);
	}
	//index = (7 * key +13) % listsize
	while (1) {
		flag = fscanf(fp, "%d", &temp);
		if (flag == EOF)
			break;
		else {
			newidx = (7 * temp + 13) % listsize;
			if (arr[newidx] == 0)
				arr[newidx] = temp;
			else {
				collision = 0;
				do {		//linear probe
					newidx = (newidx+1) % listsize;
					collision++;
				} while (arr[newidx] == 0);
				if (collision > *maxcollision)
					*maxcollision = collision;
				arr[newidx] = temp;
			}
		}
	}
	

	return arr;
}
int hash_search(int* arr, int target,int count, int maxcollision) 
{
	int index = (7 * target + 13) % (3 * count);
	int i = 0;
	
	while (i <= maxcollision)
	{
		if (arr[index] == target)
			return 1;
		else {			//linear probe
			index = (index+1) % (3 * count);
			i++;
		}
	}
	return 0;

}
void insertionsort(int* arr, int count)
{
	int wall, i;
	int hold = 0;

	for (wall = 1; wall < count; wall++) {
		hold = arr[wall];
		for (i = wall; i > 0 && hold < arr[i - 1]; i--)
			arr[i] = arr[i - 1];
		arr[i] = hold;
	}
}
int binary_search(int* arr, int count, int target, int* loc)
{
	int begin = 0;
	volatile int mid = 0;
	int end = count - 1;

	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target > arr[mid])
			begin = mid + 1; // look in upper half 
		else if (target < arr[mid])
			end = mid - 1; // look in lower half 
		else
			begin = end + 1; // found: force exit
	}

	if (arr[mid] == target) {
		*loc = mid;
		return 1;
	}
	else
		return 0;
}