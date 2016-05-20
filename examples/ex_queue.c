#include <stdio.h>
#include <queue.h>


void int_printer(void *value)
{
    printf("val = %d\n", *(int *)value);
}

int main(void)
{
    Queue *q = Queue_create(10);
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;

    printf("Put onto the Queue\n");
    Queue_put(q, &n1);
    Queue_put(q, &n2);
    Queue_put(q, &n3);
    Queue_put(q, &n4);

    printf("Printing the queue\n");
    Queue_print(q, int_printer);

    printf("Popping two elements off the queue\n");
    int *n = Queue_get(q);
    printf("Popped -> %d\n", *n);
    n = Queue_get(q);
    printf("Popped -> %d\n", *n);

    printf("Printing the queue again\n");
    Queue_print(q, int_printer);

    printf("Destroying the Queue!\n");
    Queue_destroy(q);

}
