#include <stdio.h>
#include "list.h"
#include "dump.h"

int main()
{
    list list = {};
    InitList(&list, 5);
    ListPrint(&list);
    printf("\n");
    ListAdd(&list, 60, 2);

    ListAdd(&list, 70, 4);
    GraphDump(&list, "log/graphviz_file.txt");

    //ListPrint(&list);
    printf("\n");

    ListDelete(&list, 2);
    ListAdd(&list, 70, 4);
    ListAdd(&list, 50,2);
    ListPrint(&list);

    ListPrint(&list);
    DestroyList(&list);
}