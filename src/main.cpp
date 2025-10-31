#include <stdio.h>
#include "list.h"
#include "dump.h"

int main()
{
    list list = {};
    InitList(&list, 10);
    __Dump__(&list, "log/graphviz_file.txt");
    printf("\n");

    ListAdd(&list, 10, 0);
    __Dump__(&list, "log/graphviz_file.txt");
    ListAdd(&list, 30, 2);
    ListPrint(&list);
    
    ListAdd(&list, 20, 3);
    __Dump__(&list, "log/graphviz_file.txt");
    ListAdd(&list, 40, 4);
    
    __Dump__(&list, "log/graphviz_file.txt"); 
    

    ListAdd(&list, 50, 5);
    __Dump__(&list, "log/graphviz_file.txt");
    ListDelete(&list,3);
    __Dump__(&list, "log/graphviz_file.txt");
    DestroyList(&list);
}