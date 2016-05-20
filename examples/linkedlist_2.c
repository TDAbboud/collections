#include <stdio.h>
#include <list.h>


void Int_printer(void *val)
{
    printf("Value = %d\n", *(int *)val);
}

int main(void)
{
    List *list = NULL;
    list = List_create();

    // Int Data
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;

    List_push(list, &n1);
    List_push(list, &n2);
    List_push(list, &n3);
    List_print(list, Int_printer);

    List_destroy(list);
}
