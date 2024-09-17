#include <stdio.h>
#include <stdlib.h>
typedef int element;
#include "link_queue.h"

int main()
{
    int a, b, c, d;

    a = 1;
    b = 2;
    c = 3;
    d = 4;


    QUEUE* q1 = createqueue(4);

    dequeue(q1);

    enqueue(q1,a);
    enqueue(q1,b);
    enqueue(q1,c);
    enqueue(q1,a);
    enqueue(q1,a);


    printf("%d\n",dequeue(q1));
    printf("%d\n",dequeue(q1));
    

    return 0;
}