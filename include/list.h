#include <stdio.h>
#include <math.h>

#ifndef LIST_H
#define LIST_H

struct list
{
    double* data = NULL;
    int* next = NULL;
    int head = NAN;
    int* prev = NULL;
    int tail = NAN;
    int free = NAN;
    FILE* dump_file = NULL;
};

void InitList(list* list, size_t capacity);
void DestroyList(list* list);

// TODO insert to end
// TODO find element by value
void ListAdd(list* list, double element, size_t index_previous); // TODO insert
void ListDelete(list* list, size_t index_previous);
#endif