#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


/*
 * Create the Queue object
 *  @args:
 *      maxsize: size of the queue
 *  @returns:
 *      NULL: Could not create the Queue object
 */
Queue *Queue_create(int maxsize)
{
    if (maxsize < 1) {
        //printf("maxsize must be greater than 0!\n");
        return NULL;
    }
    Queue *q = malloc(sizeof(Queue));
    q->maxsize = maxsize;
    q->queue = List_create();
    return q;
}


/*
 * Destroy the Queue object
 *  @args:
 *      q: The Queue object
 */
void Queue_destroy(Queue *q)
{
    List_clear_destroy(q->queue);
    free(q);
}


/*
 * Put an object at the end of the Queue
 *  @args:
 *      q: The Queue object
 *      value: value to place onto the queue
 */
void Queue_put(Queue *q, void *value)
{
    // Check the bounds of the queue before enquing
    if (Queue_full(q)) {
        printf("Queue is Full!\n");
        return;
    }

    // Just a tail insertion into the queue
    List_push(q->queue, value);
}


/*
 * Deque an element from the head of the Queue
 *  @args:
 *      q: The Queue object
 *  @returns:
 *      NULL: If the queue is empty
 *      void *: the value of the node that was removed
 */
void *Queue_get(Queue *q)
{
    return (Queue_empty(q) ? NULL : List_pop_head(q->queue));
}


/*
 * Print the entire queue
 *  @args:
 *      q: The Queue object
 *      (*fn): Function pointer to a custom print method
 */
void Queue_print(Queue *q, void (*fn)(void *value))
{
    List_print(q->queue, fn);
}
