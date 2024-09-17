#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char s_element;

typedef struct stack_node{
    s_element data;
    struct stack_node* next;
}NODE;

typedef struct head{
    int count;
    NODE* top;
}STACK;

STACK* create_stack()
{
    STACK* pStack = (STACK*)malloc(sizeof(STACK));
    if (pStack == NULL)
        return NULL;
    else{
        pStack->count = 0;
        pStack->top = NULL;
    }
    
    return pStack;
}
void push(STACK* pStack, s_element newdata)
{
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    if(newnode == NULL)
        return;
    
    newnode -> data = newdata;
    newnode -> next = pStack -> top;
    pStack -> top = newnode;
    pStack->count++;
}
s_element pop(STACK* pStack)
{
    s_element item;
    NODE* oldtop;
    
    if(pStack->top == NULL)
        return '0';
    else{
        item = pStack->top-> data;
        oldtop = pStack->top;
        pStack->top = oldtop->next;
        free(oldtop);
        pStack->count--;
        return item;
    }
}
s_element top(STACK* pStack)
{
    s_element item;
    
    if(pStack->top == NULL){
        return 0;
    }
    else
        item = pStack->top-> data;
    return item;
}
void destroystack(STACK* pStack)
{
    NODE* temp;
    
    if(pStack->count == 0)
        free(pStack);
    else{
        while(pStack->count != 0){
            temp = pStack->top;
            pStack->top = temp->next;
            free(temp);
            pStack->count--;
        }
        free(pStack);
    }
}
void clearstack(STACK* pStack)
{
    NODE* temp = NULL;
    
    if (pStack->count > 0){
        while(pStack->count != 0){
            temp = pStack->top;
            pStack->top = temp->next;
            free(temp);
            pStack->count--;
        }
    }
}
int countstack(STACK* pStack)
{
    return pStack->count;
}
bool isemptystack(STACK* pStack)
{
    if(pStack->count == 0)
        return true;
    else
        return false;
}