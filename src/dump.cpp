#include <stdio.h>
#include "dump.h"
#include <string.h>

const size_t capacity = 10;

void GraphDump_debug(list* list, const char* filename, const char* file, int line)
{
    __VERIFY__;

    static size_t count_dump = 1;    
    
    FILE* log_file =  fopen(filename, "w");
    WriteToDot(list, log_file);
    fclose(log_file);
    
    CallCommand(count_dump);
    DumpToHtml(list, count_dump, file, line);
    count_dump++;
}

void ListPrint(list* list, const char* file, const int line)
{
    __VERIFY__;
 
    printf("\n====DUMP from %s:%d====\n", file, line);
 
    for (size_t index = 1; index != 0; index = list->next[index])
    {
        if (list->free == 1)
        {
            printf("empty list\n");
            printf("=================================\n\n");
            return;
        }

        printf("data[%lu] = %lf\t", index, list->data[index]);
        
        printf("next[%lu] =  %lu\t", index, list->next[index]);
        
        printf("prev[%lu] = %d\t", index, list->prev[index]);
        
        printf("free = %lu\n", list->free);
    }   

    printf("=================================\n\n");
} 

void WriteToDot(list* list, FILE* log_file)
{
    fprintf(log_file, "digraph {\n");

    fprintf(log_file, "HEAD [shape = record, label = \"Head\", style =  filled, fillcolor = \"green\"];\n");
    fprintf(log_file, "TAIL [shape = record, label = \"Tail\", style =  filled, fillcolor = \"red\"];\n");


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
        if (list->prev[index] == -1)
        {
            continue;
        }
        fprintf(log_file, "->node%lu", index);        
    }
    fprintf(log_file, ";\n");

    fprintf(log_file, "HEAD->node%lu\n", list->head);
    fprintf(log_file, "TAIL->node%lu\n", list->tail);
    fprintf(log_file, "}");
}

void CallCommand(size_t count_dump)
{
    char cmd[60] = {};
    snprintf(cmd, sizeof(cmd), "%s%lu.%s", "dot -Tpng log/graphviz_file.txt -o log/graph", count_dump, "png");
    printf("%s\n",cmd);
    system(cmd);
}

void DumpToHtml(list* list, size_t count_dump, const char* file, int line)
{
    char dump_str[120] = {};
    snprintf(dump_str, sizeof(dump_str), "<h1>DUMP FROM %s:%d\n", file, line);
    fprintf(list->dump_file, "%s",dump_str);

    char img_name[40] = {};
    snprintf(img_name, sizeof(img_name), "<img src = \"log/graph%lu.png\"/>\n",  count_dump);
    fprintf(list->dump_file, "%s", img_name);
}