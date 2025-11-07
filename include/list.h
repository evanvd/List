#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifndef LIST_H
#define LIST_H

struct list
{
    double* data = NULL;
    size_t* next = NULL;
    size_t head = 0;
    int* prev = NULL;
    size_t tail = 0;
    size_t free = 0;
    FILE* dump_file = NULL;
    size_t capacity = 0;
};

void InitList(list* list, size_t capacity);
void DestroyList(list* list);
void ListInsert(list* list, double element, size_t index_previous); 
void ListDelete(list* list, size_t index_previous);

#define VERIFY_LIST_(list)                                                                                  \
    if (list == NULL)                                                                               \
    {                                                                                               \
        printf("Error: list is NULL in %s\n", __func__);                                            \
        getchar();                                                                                  \
    }                                                                                               \
    for (size_t list_index = 1; list_index < list->capacity; list_index++)                          \
    {                                                                                               \
        if(list->next[list_index] == list_index)                                                    \
        {                                                                                           \
            printf("Failed, cycle list_index: %lu %s:%d", list_index, __FILE__, __LINE__ );         \
            getchar();                                                                              \
            abort();                                                                                \
        }                                                                                           \
    }                                                                                               \


#endif