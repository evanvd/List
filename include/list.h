#include <stdio.h>
#include <math.h>
#include <assert.h>

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

#define __VERIFY__ \
    if (list == NULL)\
    {\
        printf("Error: list is NULL in %s\n", __func__);\
        getchar();\
    }\
    for (size_t list_index = 1; list_index < list->capacity; list_index++)\
    {\
        if(list->next[list_index] == list_index)\
        {\
            printf("Failed, cycle list_index: %lu %s:%d", list_index, __FILE__, __LINE__ );\
            getchar();\
            abort();\
        }\
    }\


#endif