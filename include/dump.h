#include <stdio.h>
#include "list.h"


#define __Dump__(filename) ListPrint(&list);GraphDump(&list, filename, __FILE__, __LINE__); 
void GraphDump(list* list, const char* filename, const char* file, int line);

void ListPrint(list* list);
void WriteToDot(list* list, FILE* log_file);
void CallCommand(size_t count_dump);

#define __DumpToHtml__ DumpToHtml(list, count_dump, file, line)
void DumpToHtml(list* list, size_t count_dump, const char* file, int line);