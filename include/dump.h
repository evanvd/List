#include <stdio.h>
#include "list.h"


#undef __Dump__
// TODO split into lines
#define DUMP_LIST(list, filename) ListPrint(list, __FILE__, __LINE__); GraphDump(list, filename, __FILE__, __LINE__);

void GraphDump(list* list, const char* filename, const char* file, int line);
void ListPrint(list* list, const char* file, int line);
void WriteToDot(list* list, FILE* log_file);
void CallCommand(size_t count_dump);
void DumpToHtml(list* list, size_t count_dump, const char* file, int line);