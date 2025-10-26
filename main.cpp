#include <stdio.h>
#include "list.h"


int main()
{
    list list = {};
    InitList(&list, 5);
    ListPrint(&list);
    printf("\n");

    ListAdd(&list, 50, 4);    
    ListPrint(&list);
    printf("\n");

    ListDelete(&list, 2);
    ListPrint(&list);
    DestroyList(&list);
}