#include "List_Link.h"

void ListIn(List**);
void ListOut(List**);
void Stat(List**);
void Search(List**);

int main() {
	List* pList = CreateList(100);
	int sel;

	for (;;) {
		printf("In(0), Search(1), Out(2), Exit(3) : ");
		scanf("%d", &sel);
		getchar();

		switch (sel){
		case 0:
			ListIn(&pList);
			Stat(&pList);
			break;
		case 1:
			Search(&pList);
			Stat(&pList);
			break;
		case 2:
			ListOut(&pList);
			Stat(&pList);
			break;
		case 3:
			DestroyList(pList);
			return 0;
		default:
			break;
		}
	}
	return 0;
}

void ListIn(List **ppList) {
	int InputNum;
	printf("In : ");
	scanf("%d", &InputNum);
	AddNode(*ppList, InputNum);
}
void Stat(List **ppList) {
	int i = 0;
	int data = 0;
	bool re;
	printf("The Current status of List :");

	do {
		re = traverseList(*ppList,i++,&data);
		if (re)
			printf(" %d,", data);
	} while (re);

	printf("\b \n\n");
}
void Search(List** ppList) {
	int searchNum;
	int i = 0, data = 0;
	bool re;

	printf("Search : ");
	scanf("%d",&searchNum);

	do {
		re = traverseList(*ppList, i++, &data);
		if (data == searchNum) {
			printf("My List has %d.\n", searchNum);
			return;
		}
	} while (re);

	printf("My List does not have %d.\n", searchNum);
}
void ListOut(List** ppList) {
	int delNum;
	
	if (IsEmptyList(*ppList)) {
		printf("Have no data!\n\n");
		return;
	}

	printf("Out : ");
	scanf("%d", &delNum);

	RemoveNode(*ppList, delNum);
}