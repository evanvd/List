#include <stdio.h>
#include "dump.h"
const size_t capacity = 10;
void GraphDump(list* list, const char* filename)
{
    FILE* log_file =  fopen(filename, "w");
    fprintf(log_file, "digraph {\n");
        
    for (size_t index = 1; index < capacity; index++)
    {
        fprintf(log_file, "node%lu [shape=record,label=\" %d |{element =  %f |<f0> next = %d } | prev \" ];\n", index, index, list->data[index], list->next[index]);
    }

    fprintf(log_file, "node1:<f0>");
    for (size_t index = list->next[1]; list->next[index]!= 0; index = list->next[index])
    {
        fprintf(log_file, "->node%lu:<f0>", index);

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