#include <stdio.h>
#include "list.h"
#include "dump.h"

int main()
{
    list list = {};
    InitList(&list, 10);
    ListPrint(&list);
    //GraphDump(&list, "log/graphviz_file.txt");
    printf("\n");

    ListAdd(&list, 10, 0);
    ListAdd(&list, 30, 1);
    ListPrint(&list);
    
    ListAdd(&list, 20, 1);
    GraphDump(&list, "log/graphviz_file.txt");
    ListPrint(&list);
    ListAdd(&list, 40, 3);
    
    ListPrint(&list);

    GraphDump(&list, "log/graphviz_file.txt");
    ListPrint(&list);
    

    DestroyList(&list);
}