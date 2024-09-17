#include <stdio.h>
#include <stdlib.h>

void get_in(int **inp1, int **inp2, int cnt)
{
    int i;
    
    *inp1 = (int*)malloc(cnt*sizeof(int));
    *inp2 = (int*)malloc(cnt*sizeof(int));
    for (i = 0 ; i<cnt; i++)
    {
        getchar();
        printf("in1 in2 : ");
        scanf("%d %d",*(inp1)+i,*(inp2)+i);
    }
}
int* add(int *inp1, int *inp2, int cnt)
{
    int i;
    int* sum;
    
    sum = (int*)malloc(cnt*sizeof(int));
    for (i = 0 ; i<cnt; i++)
        *(sum+i) = *(inp1+i) + *(inp2+i);
        
    return sum;
}
int main(void){
    int count, i;
    int *in1=NULL, *in2=NULL, *result=NULL;
    
    printf("# of input pairs : ");
    scanf("%d", &count);
    
    get_in(&in1, &in2, count);
    result = add(in1, in2, count);
    
    for(i=0; i<count; i++)
        printf("%d + %d = %d\n",in1[i],in2[i],result[i]);
        
    free(in1);
    free(in2);
    free(result);
    
    return 0;
    
}

