#include <stdio.h>
#include "list.h"


#undef __Dump__
#define __Dump__(list, filename) do { ListPrint(list, __FILE__, __LINE__); GraphDump_debug(list, filename, __FILE__, __LINE__); } while(0)

void GraphDump_debug(list* list, const char* filename, const char* file, int line);
void ListPrint(list* list, const char* file, int line);
void WriteToDot(list* list, FILE* log_file);
void CallCommand(size_t count_dump);
void DumpToHtml(list* list, size_t count_dump, const char* file, int line);