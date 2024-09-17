#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;
#include "stack_link.h.txt"

int main()
{
    int i, cur;
    int size;
    char num;
    char* temp;
    char* input = NULL;
    char** tokened_input = NULL;
    char** parenthesis_infix = NULL;
    char* infix = NULL;
    char* postfix = NULL;
    STACK* stack1;
    
    
    
    //수식 입력받기
    input = (char*)malloc(50*sizeof(char));
    printf("Arithmetic Expression : ");
    scanf("%s",input);
    size = strlen(input);
    
    
    //수식을 분해
    tokened_input = (char**)malloc(size*4);
    for(i=0,cur=0;cur<size;cur++){
        if (*(input+cur)==32)
            cur++;
        else{
            *(tokened_input+i) = (char*)malloc(2*sizeof(char));
            strcpy(*(tokened_input+i),NULL);
            
         
        }
    }
    free(input);
    size = strlen(tokened_input);
    
    //두 자리 이상 숫자 합치기, 포인터 배열에 넣기
    parenthesis_infix = (char**)malloc(size*4);
    stack1 = create_stack();
    for(cur=0,i=0;cur<size;cur++){
        if((*(tokened_input+cur)>47)&&(*(tokened_input+cur)<58)){
            push(stack1,*(tokened_input+cur));
            cur++;
        }
        else{
            while(stack1->count != 0){
                num = pop(stack1);
            }
        }
    }
    
    
    
    
    //infix to postfix
    
    //calculate postfix
    return 0;
}