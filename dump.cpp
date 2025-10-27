#include <stdio.h>
#include "dump.h"
const size_t capacity = 10;
void GraphDump(list* list, const char* filename)
{
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
    for (size_t index = list->next[1]; list->next[index]!= 0; index = list->next[index])
    {
        fprintf(log_file, "->node%lu", index);

    }
    fprintf(log_file, ";\n");

    
    fprintf(log_file, "}");
    fclose(log_file);
    system("dot -Tpng log/graphviz_file.txt -o log/graph.png");
}

void ListPrint(list* list)
{
    for (size_t index = 1; index != 0; index = list->next[index])
    {
        printf("[%lu] %lf\n", index, list->data[index]);
    }
} 