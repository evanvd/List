#include <stdio.h>
#include <stdlib.h>
#include "list.h"

const double CANARY = 0xDEAD;
const double POIZON = 0xDEAD; //TODO  ADD value to consts 

void InitList(list* list, size_t capacity)
{

    list->data = (double*)calloc(capacity, sizeof(double));
    list->prev = (int*)calloc(capacity, sizeof(int));
    list->next = (size_t*)calloc(capacity, sizeof(size_t));
    
    if (list->data == NULL || list->prev == NULL || list->next == NULL) 
    {
        printf("Memory allocation failed in InitList\n");
        abort();
    }

    list->dump_file = fopen("dump.html", "w");
    if (list->dump_file == NULL) 
    {
        printf("Failed to open dump file\n");
    }

    list->capacity = capacity;
    list->head = 1;
    list->tail = 1;
    list->free = 1; 
    
    list->data[0] = CANARY;
    list->next[0] = 0;  
    list->prev[0] = 0;

    for (size_t index = 1; index < capacity; index++)
    {
        list->data[index] = POIZON;
        list->prev[index] = -1;
        
        if (index < capacity - 1) 
        {
            list->next[index] = index + 1;
        } else 
        {
            list->next[index] = 0; 
        }
    }
}

void DestroyList(list* list)
{
    free(list->data);
    free(list->prev);   
    free(list->next);
    
    if (list->dump_file != NULL)
    {
        fclose(list->dump_file);
        list->dump_file = NULL; 
    }
}



void ListAdd(list* list, double element, size_t index_previous)
{
    if (list == NULL) 
    {
        printf("Error: list is NULL in ListAdd\n");
        return;
    }
    printf("ListAdd: element=%f, index_previous=%lu, free=%lu, capacity=%lu\n", 
           element, index_previous, list->free, list->capacity);


    if (list->free == 1 && list->next[0] == 0)
    {
        // printf("empty list - adding first element\n");
        size_t new_index = list->free;
        
        list->data[new_index] = element;
        list->next[new_index] = 0;
        list->prev[new_index] = 0;
        

        list->next[0] = new_index;
        list->prev[0] = 0;
        
        list->head = new_index;
        list->tail = new_index;
        

        list->free = 2;  
        return;
    }

    
    if (index_previous == list->tail)
    {
        // printf("adding to tail\n");
        size_t new_index = list->free;
        
        list->data[new_index] = element;
        list->prev[new_index] = list->tail;
        list->next[new_index] = 0;  
        
        list->next[list->tail] = new_index;
        list->tail = new_index;
        
        list->free = list->next[new_index];
        return;
    }

    // printf("adding to middle\n");
    size_t new_index = list->free;
    size_t next_free = list->next[new_index];
    
    list->data[new_index] = element;
    list->next[new_index] = list->next[index_previous];
    list->prev[new_index] = index_previous;
    

    list->next[index_previous] = new_index;
    

    if (list->next[new_index] != 0 && list->next[new_index] < list->capacity)
    {
        list->prev[list->next[new_index]] = new_index;
    }
    

    list->free = next_free;
}

void ListDelete(list* list, size_t index)
{
    //TODO verify
    // int next_free = list->data[index_previous];

    // list->data[index_previous] = POIZON;
    // list->next[index_previous] = list->free;
    
    // list->free = next_free;
    list->next[index] = list->next[list->next[index]];
}