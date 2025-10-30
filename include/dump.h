#include <stdio.h>
#include "list.h"

void GraphDump(list* list, const char* filename);
void ListPrint(list* list);
void WriteToDot(list* list, FILE* log_file);
void CallCommand(size_t count_dump);
void DumpToHtml(list* list, size_t count_dump);