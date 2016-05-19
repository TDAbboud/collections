#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

struct ListNode;
typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

/** Methods **/
List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);
void List_push(List *list, void *value);
void *List_pop(List *list);
void List_print(List *list, void (*fn)(void *value));

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
                                 ListNode *V = NULL;\
                                for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
