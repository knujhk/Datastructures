#include <stdio.h>
#include <stdlib.h>

typedef int element;
#include "stack_link.h.txt"



int main()
{
    STACK* stack1 = create_stack();
    int new;
    
    printf("Enter a number: <Ctrl+d> to stop: ");
    while(scanf("%d",&new) != 0){
        getchar();
        push(stack1,new);
        printf("Enter a number: <Ctrl+d> to stop: ");
    }
    printf("the list of numbers reversed:\n");
    while(stack1->count != 0){
        printf("%d\n",pop(stack1));
    }

    return 0;
}