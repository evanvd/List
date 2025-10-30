#include <stdio.h>
#include "dump.h"
#include <string.h>

const size_t capacity = 10;

void GraphDump(list* list, const char* filename)
{
    // if (list->next[1] < 0)
    // {
    //     printf("list->next[1] %d\n",list->next[1]);
    //     printf("empty list\n");
    //     return;
    // }

    static size_t count_dump = 1;    
    
    FILE* log_file =  fopen(filename, "w");
    WriteToDot(list, log_file);
    fclose(log_file);
    
    CallCommand(count_dump);
    DumpToHtml(list, count_dump);
    count_dump++;
}

void ListPrint(list* list)
{
    for (size_t index = 1; index != 0; index = list->next[index])
    {
        printf("\ndata[%lu] %lf\n", index, list->data[index]);
        printf("next[%lu] %lu\n", index, list->next[index]);
        printf("free %lu\n", list->free);
        if (list->free == 1)
        {
            printf("empty list\n");
            return;
        }
        //getchar();
    }
} 

void WriteToDot(list* list, FILE* log_file)
{
    fprintf(log_file, "digraph {\n");
    
    fprintf(log_file, "rankdir=LR;\n ranksep=0.5;\n nodesep = 0.3;");

    for (size_t index = 1; index < capacity; index++)
    {
        fprintf(log_file, "node%lu [shape=record,label=\" %lu |element =  %f |{<f0> next = %lu  | prev  = %d}\", style=filled, fillcolor=lightblue, width=3, height=0.8];\n", index, index, list->data[index], list->next[index], list->prev[index]);
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
}

void CallCommand(size_t count_dump)
{
    char cmd[60] = {};
    snprintf(cmd, sizeof(cmd), "%s%lu.%s", "dot -Tpng log/graphviz_file.txt -o log/graph", count_dump, "png");
    printf("%s\n",cmd);
    system(cmd);
}

void DumpToHtml(list* list, size_t count_dump)
{
    char dump_str[40] = {};
    snprintf(dump_str, sizeof(dump_str), "<h1>DUMP FROM %s:%d</h1>\n", __FILE__,__LINE__);
    fprintf(list->dump_file, "%s",dump_str);

    char img_name[40] = {};
    snprintf(img_name, sizeof(img_name), "<img src = \"log/graph%lu.png\"/>\n",  count_dump);
    fprintf(list->dump_file, "%s", img_name);
}