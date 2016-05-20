#include <stdio.h>
#include <list.h>

typedef enum Type {
    INT,
    STRING
}Type;

typedef struct _Node {
    Type type;
    union {
        int ival;
        char *sval;
    }data;
}Node;


void Printer(void *node)
{
    Node *n_node = (Node *)node;
    switch (n_node->type) {
        case INT:
            printf("Int = %d\n", n_node->data.ival);
            break;
        case STRING:
            printf("String = %s\n", n_node->data.sval);
            break;
    }
}


int main(void)
{
    List *list1 = NULL;
    List *list2 = NULL;
    list1 = List_create();
    list2 = List_create();

    Node sn1 = {.type = STRING, .data.sval = "test1 data!"};
    Node sn2 = {.type = STRING, .data.sval = "test2 data!"};
    Node sn3 = {.type = STRING, .data.sval = "test3 data!"};

    List_push(list1, &sn1);
    List_push(list1, &sn2);
    List_push(list1, &sn3);
    List_print(list1, Printer);
    List_destroy(list1);


    // Int Data
    Node in1 = {.type = INT, .data.ival = 1 };
    Node in2 = {.type = INT, .data.ival = 2 };
    Node in3 = {.type = INT, .data.ival = 3 };

    List_push(list2, &in1);
    List_push(list2, &in2);
    List_push(list2, &in3);
    List_print(list2, Printer);

    printf("Popping 1 element!\n");
    List_pop(list2);
    List_print(list2, Printer);

    List_destroy(list2);
}
