#ifndef QUEUE_H
#define QUEUE_H

// Use a linked list under the hood
#include "list.h"

typedef struct _Queue {
    // Do Not access these directely, use the API!
    int maxsize;
    List *queue;
}Queue;


/** Methods **/
Queue *Queue_create(int maxsize);
void Queue_destroy(Queue *q);
void Queue_put(Queue *q, void *value);
void *Queue_get(Queue *q);
void Queue_print(Queue *q, void (*fn)(void *value));

#define Queue_maxsize(A) (A->maxsize)
#define Queue_count(A) (A->queue->count)
// return 1 if queue is full otherwise 0
#define Queue_full(A) (Queue_count(A) == Queue_maxsize(A) ? 1 : 0)
// return 1 if queue is empty otherwise 0
#define Queue_empty(A) (Queue_count(A) == 0 ? 1 : 0)

#endif
