#include <stdio.h>
#include "dump.h"

void GraphDump(list* list, const char* filename)
{
    FILE* log_file =  fopen(filename, "w");
    fprintf(log_file, "digraph {\n");
        
    for (size_t index = 1; index != 0; index = list->next[index])
    {
        fprintf(log_file, "node%lu [shape=record,label=\" %d |data %f |<f0> next | prev \" ];", index, index, list->data[index]);
    }
    for (size_t index = 1; list->next[index]!= 0; index = list->next[index])
    {
        fprintf(log_file, "node%lu:<f0> -> node%lu:<f0>;\n", index, index + 1);
    }
    


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