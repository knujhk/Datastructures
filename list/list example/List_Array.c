#include "List_Array.h"

void ListIn(List**);
void ListOut(List**);
void Stat(List*);
void Search(List**);

int main() {
	List* pList = CreateList(100);
	int sel;

	for (;;) {
		printf("In(0), Search(1), Out(2), Exit(3) : ");
		scanf("%d", &sel);
		getchar();

		switch (sel) {
		case 0:
			ListIn(&pList);
			Stat(pList);
			break;
		case 1:
			Search(&pList);
			Stat(pList);
			break;
		case 2:
			ListOut(&pList);
			Stat(pList);
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

void ListIn(List** ppList) {
	int InputNum;
	printf("In : ");
	scanf("%d", &InputNum);
	AddNode(*ppList, InputNum);
}

void Stat(List* pList) {
	int i = 0;
	printf("The Current status of List :");
	
	for (i = 0; i < pList->count; i++) {
		printf(" %d,",pList->list[i]);
	}

	printf("\b \n\n");	//문자열 마지막에 ,를 없애기 위에 \b(커서 한 칸 뒤로 이동)
}

void Search(List** ppList) {
	int data;
	printf("Search : ");
	scanf("%d",&data);

	SearchList(*ppList, data);
}
void ListOut(List** ppList) {
	int delNum;

	if (IsEmptyList(*ppList)) {
		printf("Have no data!\n\n");
		return;
	}

	printf("Out : ");
	scanf("%d", &delNum);

	RemoveList(*ppList, delNum);
}