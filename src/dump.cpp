#include <stdio.h>
#include "dump.h"
#include <string.h>

const size_t capacity = 10;

void GraphDump(list* list, const char* filename)
{
    if (list->next[1] < 0)
    {
        printf("list->next[1] %d\n",list->next[1]);
        printf("empty list\n");
        return;
    }
    static int count_dump = 1;    
    FILE* log_file =  fopen(filename, "w");
    fprintf(log_file, "digraph {\n");
    
    fprintf(log_file, "rankdir=LR;\n ranksep=0.5;\n nodesep = 0.3;");

    for (size_t index = 1; index < capacity; index++)
    {
        fprintf(log_file, "node%lu [shape=record,label=\" %d |element =  %f |{<f0> next = %d  | prev }\", style=filled, fillcolor=lightblue, width=3, height=0.8];\n", index, index, list->data[index], list->next[index]);
    }


    fprintf(log_file, "node1");
    for (size_t index = 1; index < capacity; index++)
    {
        fprintf(log_file, "->node%lu", index);
    }
    
    fprintf(log_file, "\n");
    fprintf(log_file, "[style=invis, weight=100];\n edge [color=green, penwidth=1, arrowhead = normal];\n");
    

    fprintf(log_file, "node1");
    for (size_t index = list->next[1]; index != 0; index = list->next[index])
    {   
        fprintf(log_file, "->node%lu", index);

    }
    fprintf(log_file, ";\n");

    
    fprintf(log_file, "}");
    fclose(log_file);
    char cmd[60] = {};
    snprintf(cmd, sizeof(cmd), "%s%d.%s", "dot -Tpng log/graphviz_file.txt -o log/graph", count_dump, "png");
    //cmd = strcat(cmd, file_count);
    printf("%s\n",cmd);
    system(cmd);
    count_dump++;
}

void ListPrint(list* list)
{
    for (size_t index = 1; index != 0; index = (int)list->next[index])
    {
        printf("\ndata[%lu] %lf\n", index, list->data[index]);
        printf("next[%lu] %d\n", index, list->next[index]);
        printf("free %d\n", list->free);
        if (list->next[index] < 0)
        {
            printf("empty list\n");
            return;
        }
        getchar();
    }
} 

void WriteToDot(list*, const char* filename)
{
    
}

void DumpToHtml(list* list)
{
    fprintf(list->dump_file, "");
}