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
    
    if (list->data == NULL || list->prev == NULL || list->next == NULL) {
        fprintf(stderr, "Memory allocation failed in InitList\n");
        abort();
    }

    list->dump_file = fopen("dump.html", "w");
    if (list->dump_file == NULL) {
        fprintf(stderr, "Failed to open dump file\n");
    }

    list->data[0] = CANARY;
    list->head = 1;
    list->tail = 1;
    list->next[0] = 0;  
    list->prev[0] = 0;
    list->free = 1; 
    list->capacity = capacity;  

    for (size_t index = 1; index < capacity; index++)
    {
        list->data[index] = POIZON;
        list->next[index] = index + 1;  
        list->prev[index] = -1;
    }
    if (capacity > 1) {
        list->next[capacity - 1] = 0;
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
    if(list->free == 1)
    {
        printf("empty list\n");
        list->data[list->free] = element;
        list->next[list->free] = 0;
        list->prev = 0;
        list->tail = 1;
        list->free = 2;
        return;
    }
    if(index_previous == 0)
    {
        // TODO why?..
        // ⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⢉⢉⠉⠉⠻⣿⣿⠛⠛⣤⣤⣤⣤⢸⣿⣿⣿⣿⣿
        // ⣿⣿⣿⣿⣿⣿⣿⠟⠠⡰⣕⣗⣷⣧⣀⣅⠘⠛⠄⣿⣿⣿⠛⣿⢸⣿⣿⣿⣿⣿
        // ⣿⣿⣿⣿⣿⣿⠃⣠⣳⣟⣿⣿⠿⣿⡿⣜⠄⣿⣤⣤⣤⠛⠛⣤⣿⣿⣿⣿⣿⣿
        // ⣿⣿⣿⠟⣩⣬⣭⠻⢷⣿⣿⣿⣀⡿⣝⠖⠄⣿⣿⠛⣤⣿⠛⠛⣤⣤⣤⣤⢸⣿
        // ⣿⣿⣷⣤⣒⠲⠶⢿⣿⢷⣯⢿⢷⡫⣗⠍⢰⣿⠛⣤⣿⠛⠘⣿⣿⣿⠛⣿⢸
        // ⣿⣿⣿⡏⢀⢄⠤⣁⠋⠿⣗⣟⡯⡏⢎⠁⢸⠄⣿⠛⠛⣤⣿⣤⣤⣤⠛⠛⣤⣿
        // ⣿⣿⣿⠄⢔⢕⣯⣿⣿⡲⡤⡄⡤⠄⡀⢠⡀⡀⣤⣿⣿⣿⠛⠛⣤⣤⣤⣤⢸⣿
        // ⣿⡿⢉⣴⣶⣦⠙⣿⣿⣿⡼⣿⣿⣿⣿⣿⢿⣷⡌⢿⠛⣤⠄⣿⣿⣿⠛⣿⢸⣿
        // ⣿⣷⡘⠿⠟⣛⡁⢻⣿⣿⣿⣷⣝⢿⣿⠻⣿⢮⣭⣥⣄⡹⣤⣤⣤⠛⠛⣤⣿
        // ⣿⣿⡇⢿⣿⣿⣿⠘⣿⣿⣿⣿⣿⣷⣦⣟⡶⠶⢾⣭⣽⣗⡈⠻⠛⣤⣿⣿⣿
        // ⣿⣿⣷⡈⣿⣿⣿⣧⣌⠛⠿⣿⣿⣿⣿⣿⣿⣷⣷⡲⣶⣶⣾⣷⣌⡛⢿⣿⣿⣿
        // ⣿⣿⣿⠗⡈⠻⣿⣿⡿⢛⣶⣤⣍⠻⣿⣿⣿⣿⣿⡿⠆⠻⠿⣿⣿⡿⠗⣢⣿
        // ⣿⣿⡏⢼⣿⣷⣶⢋⣴⣿⣿⣿⣿⡇⢀⣠⠄⣠⣶⣶⣿⣿⣷⣶⣶⣶⣿⣿⣿
        // ⣿⣿⣷⣌⠛⠿⠛⠈⠛⠿⠿⠿⢛⠁⢈⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
        // ⣿⣿⣿⣿⣿⣿⣇⡈⢉⣩⡭⠽⢛⣒⣒⣒⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
        // ⣿⣿⣿⣿⣿⣿⣿⣇⣉⣥⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
    }

    if(index_previous == (size_t)list->tail)
    {
        printf("tail index\n");
        list->data[list->free] = element;
        list->tail = list->free;

        printf("%lu\n",  list->next[list->free]);
        
        size_t next_free = -list->next[list->free];
        list->next[list->free] = 0;
        list->free = next_free;
        list->next[index_previous] = list->tail;
        return;
    }
    size_t next_free = list->next[list->free];
    list->data[list->free] = element;
    list->next[list->free] = list->next[index_previous];

    list->prev[index_previous] = index_previous;

    list->next[index_previous] = list->free; 
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