//#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>

typedef int element;

typedef struct{
    element *stack;
    int size;
    int top;
}STACK;

STACK* create_stack(int s_size, int a)
{
    STACK* pStack = (STACK*)malloc(sizeof(STACK));
    if(pStack == NULL)
        return NULL;
    
    pStack->stack = (element*)malloc(s_size*sizeof(element));
    if(pStack->stack == NULL){
        free(pStack);
        return NULL;
    }
    pStack->size = s_size;
    pStack->top = -1;
    return  pStack;
}
void push(STACK* pStack, element item)
{
    if(pStack->top == pStack->size-1)
        return;
    
    pStack->stack[++pStack->top] = item;
}
element pop(STACK* pStack)
{
    if(pStack->top<0)
        return 0;
    
    return pStack->stack[pStack->top--];
}
element top(STACK* pStack)
{
    if(pStack->top<0)
        return 0;
    
    return pStack->stack[pStack->top];
}
void destroystack(STACK* pStack)
{
    if(pStack != NULL){
        free(pStack->stack);
        free(pStack);
    }
}
void clearstack(STACK* pStack)
{
    if(pStack->top >= 0)
        free(pStack->stack);
}
int countstack(STACK* pStack)
{
    if(pStack == NULL)
        return 0;
    return pStack->top+1;
}
bool isfullstack (STACK* pStack)
{
    if (pStack->top == pStack->size-1)
        return true;
    else
        return false;
}
bool isemptystack (STACK* pStack)
{
    if (pStack->top < 0)
        return true;
    else
        return false;
}