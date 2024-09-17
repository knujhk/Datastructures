#include <stdio.h>
#include <stdlib.h>

typedef int element;
#include "stack_link.h.txt"

int main()
{
    int dec_num, bin_num;
    int quotient, remain;
    
    STACK* stack1 = create_stack();
    
    while(1){
        printf("Enter a number: ");
        scanf("%d",&dec_num);
        if(dec_num>0)
            break;
        else
            printf("the number is not positive integer\n");
    }
    
    quotient = dec_num;
    do{
        remain = quotient % 2;
        push(stack1,remain);
        quotient /= 2;
    }while(quotient != 0);
    
    printf("\nThe binary number of %d:  ",dec_num);
    
    while(stack1->count != 0){
        printf("%d",pop(stack1));
    }
    
    return 0;
}