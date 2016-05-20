#include "minunit.h"
#include <queue.h>
#include <assert.h>

static Queue *q = NULL;
int test1 = 1;
int test2 = 2;
int test3 = 3;

char *test_create()
{
    q = Queue_create(0);
    mu_assert(q == NULL, "Created a queue with 0 size");

    q = Queue_create(3);
    mu_assert(q != NULL, "Failed to create the queue");

    return NULL;
}

char *test_destroy()
{
    Queue_destroy(q);
    return NULL;
}

char *test_put()
{
    Queue_put(q, &test1);
    mu_assert(Queue_count(q) == 1, "Wrong number of elements");

    // Fill up the queue
    Queue_put(q, &test2);
    Queue_put(q, &test3);

    mu_assert(Queue_count(q) == 3, "Wrong number of elements");

    return NULL;
}

char *test_get()
{
    int count = Queue_count(q);
    Queue_get(q);
    mu_assert(Queue_count(q) == (count-1), "Wrong number of elements after dequeuing");

    Queue_get(q);

    // Get last element in queue
    int *elem = Queue_get(q);
    mu_assert(*elem == test3, "Wrong element returned from dequeuing (based on value)");
    mu_assert(elem == &test3, "Wrong element returned from dequeuing (based on address)");

    return NULL;
}

char *test_full()
{
    mu_assert(Queue_full(q) == 1, "Wrong return for queue being full");
    return NULL;
}

char *test_empty()
{
    mu_assert(Queue_empty(q) == 1, "Wrong return for queue being empty");
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_put);
    mu_run_test(test_full);
    mu_run_test(test_get);
    mu_run_test(test_empty);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);

