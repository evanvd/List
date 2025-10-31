#include <stdio.h>
#include <math.h>

#ifndef LIST_H
#define LIST_H

struct list
{
    double* data = NULL;
    size_t* next = NULL;
    int head = NAN;
    int* prev = NULL;
    size_t tail = NAN;
    size_t free = NAN;
    FILE* dump_file = NULL;
    size_t capacity = NAN;
};

void InitList(list* list, size_t capacity);
void DestroyList(list* list);
void ListAdd(list* list, double element, size_t index_previous); // TODO insert
void ListDelete(list* list, size_t index_previous);
#endif