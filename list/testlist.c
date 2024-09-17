#include <stdio.h>
#include "list_link.h"

int main() {
	list* list1 = createlist(4);

	//deletelist(list1, 3);
	addlist(list1, 2);
	addlist(list1, 5);
	addlist(list1, 3);
	//deletelist(list1, 3);
	printlist(list1);
	addlist(list1, 4);
	addlist(list1, 4);
	addlist(list1, 6); //full
	addlist(list1, 7);
	printlist(list1);


	return 0;
}