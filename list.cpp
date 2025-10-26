#include <stdio.h>
#include <stdlib.h>
#include "list.h"

const double CANARY = 0xDEAD;
const double POIZON = 0xDEAD; //TODO  ADD value to consts 
const size_t default_size = 20;

void InitList(list* list, int count)
{
    list->data = (double*)calloc(default_size, sizeof(double));
    list->next = (int*)calloc(default_size, sizeof(int));
    list->prev = (int*)calloc(default_size, sizeof(int));

    list->data[0] = CANARY;
    list->head = 1;
    list->tail = count;

    list->next[0] = 0;
    list->next[count + 1] = 0; 

    list->prev[0] = 0;
    list->prev[count + 1] = 0;

    list->free = count + 1; 

    for (size_t index = 0; index  < (size_t)count; index++)
    {
        list->data[index] = (double)index * 10;
        list->next[index] = (int)index + 1;
        list-> prev[index] = (int)index - 1;
    }
    
    for (size_t index = (size_t)count + 2; index < default_size; index++)
    {
        list->data[index] = POIZON;
        list->data[index] = -(int)index;
    }
    
    //TODO init in cycle 
}

void DestroyList(list* list)
{
    free(list->data);
    free(list->prev);
    free(list->next);
}



void ListAdd(list* list, double element, size_t index_previous)
{
    list->data[list->free] = element;
    list->next[list->free] = list->next[index_previous];
    list->next[index_previous] = list->free; //TODO list->free = чему-то
}

void ListDelete(list* list, size_t index_previous)
{
    list->next[index_previous] = list->next[list->next[index_previous]];
}