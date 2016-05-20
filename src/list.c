#include "list.h"

/** Private Methods **/
static void *List_remove(List *list, ListNode *node)
{ // Remove an element from the list (Do not use directly! Use List_pop)
    void *result = NULL;

    if (list->count == 0 || list->last == NULL || list->first == NULL) {
        return NULL;
    }

    // Check head deletion
    if (node == list->first && node == list->last) {
        // Head deletion with 1 element in list
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        // Just head deletion
        list->first->prev = NULL;
        list->first = list->first->next;
    } else if (node == list->last) {
        // Just tail deletion
        list->last = node->prev;
        list->last->next = NULL;
    } else {
        // Deletion somewhere in the middle
        ListNode *before = node->prev;
        ListNode *after = node->next;
        before->next = after;
        after->prev = before;
    }

    list->count--;
    result = node->value;
    free(node);
    return result;
}

/** Public Methods **/
List *List_create()
{
    List *list = malloc(sizeof(List));
    list->count = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

void List_destroy(List *list)
{
    // Delete every element from the list, then delete the list
    ListNode *cur = list->first;
    while (cur != NULL) {
        ListNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(list);
}

void List_clear(List *list)
{
    // Clear all the values for the nodes in the list
    ListNode *cur = list->first;
    for (; cur != NULL; cur=cur->next)
        free(cur->value);
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value)
{ // Tail insertion
    ListNode *node = malloc(sizeof(ListNode));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->count++;
}

void *List_pop(List *list)
{ // Return the last node
    ListNode *node = list->last;
    return (node != NULL) ? List_remove(list, node): NULL;
}

void *List_pop_head(List *list)
{ // Return the head node
    ListNode *node = list->first;
    return (node != NULL) ? List_remove(list, node): NULL;
}

void List_print(List *list, void (*fn)(void *value))
{ // Print all elements of a list
    ListNode *cur = list->first;

    for (; cur != NULL; cur=cur->next)
        (*fn)(cur->value);
}


