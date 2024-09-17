#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct stack_node{
    void* data;
    struct stack_node* next;
}NODE;

typedef struct head{
    int count;
    NODE* top;
}STACK;

STACK* createstack()
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
int push(STACK* pStack, void* newdata)
{
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    if(newnode == NULL)
        return 0;
    
    newnode -> data = newdata;
    newnode -> next = pStack -> top;
    pStack -> top = newnode;
    pStack->count++;

    return 1;
}
void* pop(STACK* pStack)
{
    void* item;
    NODE* oldtop;
    
    if(pStack->top == NULL)
        return NULL;
    else{
        item = pStack->top-> data;
        NODE* oldtop = pStack->top;
        pStack->top = oldtop->next;
        free(oldtop);
        pStack->count--;
        return item;
    }
}
void* top(STACK* pStack)
{
    void* item;
    NODE* oldtop;
    
    if(pStack->top == NULL){
        return NULL;
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