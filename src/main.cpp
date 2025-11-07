#include <stdio.h>
#include "list.h"
#include "dump.h"

int main()
{
    list list = {};
    InitList(&list, 8);

    DUMP_LIST(&list, "log/graphviz_file.txt"); // TODO rename DumpList or DUMP_LIST
    

    ListInsert(&list, 10, 0);
    DUMP_LIST(&list, "log/graphviz_file.txt"); // TODO pass FILE* to dump func
    
    ListInsert(&list, 30, 1);
    DUMP_LIST(&list, "log/graphviz_file.txt");

    //FIXME ADD ability to insert before first element
    //DUMP_LIST(&list, "log/graphviz_file.txt");
    
    ListInsert(&list, 20, 1);
    DUMP_LIST(&list, "log/graphviz_file.txt");
    ListInsert(&list, 40, 2);
    
    DUMP_LIST(&list, "log/graphviz_file.txt"); 
    
    
    ListInsert(&list, 50, 4);
    DUMP_LIST(&list, "log/graphviz_file.txt");
    
    ListDelete(&list,2);
    DUMP_LIST(&list, "log/graphviz_file.txt");
    
    DestroyList(&list);
}