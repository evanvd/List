#include <stdio.h>
#include "list.h"
#include "dump.h"

int main()
{
    list list = {};
    InitList(&list, 8);

    __Dump__(&list, "log/graphviz_file.txt");
    

    ListInsert(&list, 10, 0);
    __Dump__(&list, "log/graphviz_file.txt");
    
    ListInsert(&list, 30, 1);
    __Dump__(&list, "log/graphviz_file.txt");

    //FIXME ADD ability to insert before first element
    //__Dump__(&list, "log/graphviz_file.txt");
    
    ListInsert(&list, 20, 1);
    __Dump__(&list, "log/graphviz_file.txt");
    ListInsert(&list, 40, 2);
    
    __Dump__(&list, "log/graphviz_file.txt"); 
    
    
    ListInsert(&list, 50, 4);
    __Dump__(&list, "log/graphviz_file.txt");
    
    ListDelete(&list,2);
    __Dump__(&list, "log/graphviz_file.txt");
    
    DestroyList(&list);
}