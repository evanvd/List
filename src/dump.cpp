#include <stdio.h>
#include "dump.h"
#include <string.h>



void GraphDump(list* list, const char* filename, const char* file, int line)
{
    VERIFY_LIST_(list);

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
    VERIFY_LIST_(list);
 
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
    fprintf(log_file, "digraph {\n splines=ortho;\n");

    fprintf(log_file, "HEAD [shape = record, label = \"Head\", style =  filled, fillcolor = \"green\"];\n");
    fprintf(log_file, "TAIL [shape = record, label = \"Tail\", style =  filled, fillcolor = \"red\"];\n");
    fprintf(log_file, "Free [shape = record, label = \"Free\", style =  filled, fillcolor = \"yellow\"];\n");


    fprintf(log_file, "rankdir=LR;\n ranksep=0.5;\n nodesep = 0.3;");

    for (size_t index = 1; index < list->capacity; index++)
    {
        if (list->prev[index] == -1)
        {
            fprintf(log_file, "node%lu [shape=record,label=\" phys idx %lu |element =  PZN |{<f0> next = %lu  | prev  = %d}\", style=\"filled, rounded\", fillcolor = \"#ff3434bd\", width=3, height=0.8];\n", index, index, list->next[index], list->prev[index]);
        }
        else
        {
            fprintf(log_file, "node%lu [shape=record,label=\" phys idx %lu |element =  %.2f |{<f0> next = %lu  | prev  = %d}\", style=\"filled, rounded\", fillcolor = lightblue, width=3, height=0.8];\n", index, index, list->data[index], list->next[index], list->prev[index]);
        }   
    }

    fprintf(log_file, "list_info [shape=record,label=\" Free %lu | Tail = %lu  | Head  = %lu\", style=\"filled, rounded\", fillcolor = yellow, width=3, height=0.8];\n", list->free, list->tail, list->head);


    fprintf(log_file, "list_info");
    for (size_t index = 1; index < list->capacity; index++)
    {
        fprintf(log_file, "->node%lu", index);
    }
    
    fprintf(log_file, "\n");
    fprintf(log_file, "[style=invis, weight=100];\n edge [color=\"#001affff\", penwidth = 1, arrowhead = normal];\n");
    

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
    
    fprintf(log_file, "subgraph {rank = same; HEAD; node%lu; HEAD->node%lu }\n", list->head, list->head);
    fprintf(log_file, "subgraph {rank = same; TAIL; node%lu; TAIL->node%lu }\n", list->tail, list->tail);
    fprintf(log_file, "subgraph {rank = same; Free; node%lu; Free->node%lu }\n", list->free, list->free);
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
    snprintf(dump_str, sizeof(dump_str), "<h1 style=\"color: #8a0000ff;\">====DUMP FROM %s:%d====</h1>\n", file, line);
    fprintf(list->dump_file, "%s",dump_str);

    for(size_t index = 1; index != 0; index = list->next[index])
    {
        if (list->free == 1)
        {
            fprintf(list->dump_file, "empty list<br>\n");
            break;
        }

        fprintf(list->dump_file, "data[%lu] = %.2f\t", index, list->data[index]);
        
        fprintf(list->dump_file, "next[%lu] =  %lu\t", index, list->next[index]);
        
        fprintf(list->dump_file, "prev[%lu] = %d\t", index, list->prev[index]);
        
        fprintf(list->dump_file, "free = %lu<br>", list->free);
    }   

    char img_name[40] = {};
    snprintf(img_name, sizeof(img_name), "<img src = \"log/graph%lu.png\"/>\n",  count_dump);
    fprintf(list->dump_file, "%s", img_name);
}