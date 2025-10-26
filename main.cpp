#include <stdio.h>
#include "list.h"
#include "dump.h"

int main()
{
    list list = {};
    InitList(&list, 5);
    ListPrint(&list);
    printf("\n");
    ListAdd(&list, 60, 5);

    //ListPrint(&list);
    printf("\n");

    ListDelete(&list, 2);
    GraphDump(&list, "log/graphviz_file.txt");

    //ListPrint(&list);
    DestroyList(&list);
}