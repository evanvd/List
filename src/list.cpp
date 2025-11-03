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

void ListInsert(list* list, double element, size_t index_previous)
{
    
    printf("\nListInsert: element = %f, index_previous = %lu, free = %lu, capacity = %lu\n", 
           element, index_previous, list->free, list->capacity);

    if (list->next[0] == 0 || index_previous == 0)
    {
        printf("empty list - adding first element\n");
        size_t new_index = list->free;
        size_t next_free = list->next[new_index]; 
        
        list->data[new_index] = element;
        list->next[new_index] = 0;
        list->prev[new_index] = 0;
        

        list->next[0] = new_index; 
        list->prev[new_index] = 0; 
        
        list->head = new_index;     
        list->tail = new_index;     
        

        list->free = next_free;     
        return;
    }

    
    if (index_previous == list->tail)
    {
        printf("adding to tail\n");
        size_t new_index = list->free;
        size_t next_free = list->next[new_index];
        
        list->data[new_index] = element;
        list->prev[new_index] = list->tail;
        list->next[new_index] = 0;  
        
        list->next[list->tail] = new_index;
        list->tail = new_index;
        
        list->free = next_free;
        return;
    }

    printf("adding to middle\n");
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
    

    list->free = next_free;
}

void ListDelete(list* list, size_t index)
{
    if (list == NULL || index == 0 || index >= list->capacity) 
    {
        printf("Error: invalid parameters in ListDelete\n");
        return;
    }

    if (list->prev[index] != -1 && list->prev[index] != 0) 
    {
        list->next[list->prev[index]] = list->next[index];
    } 
    else 
    {
        if (list->head == index) 
        {
            list->head = list->next[index];
        }
    }

    if (list->next[index] != 0) 
    {
        list->prev[list->next[index]] = list->prev[index];
    } 
    else 
    {
        if (list->tail == index) 
        {
            list->tail = list->prev[index];
        }
    }

    list->next[index] = list->free;
    list->data[index] = POIZON; 
    list->free = index;
}