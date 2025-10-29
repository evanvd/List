#include <stdio.h>
#include <stdlib.h>
#include "list.h"

const double CANARY = 0xDEAD;
const double POIZON = 0xDEAD; //TODO  ADD value to consts 

void InitList(list* list, size_t capacity)
{
    list->data = (double*)calloc(capacity, sizeof(double));
    list->next = (int*)calloc(capacity, sizeof(int));
    list->prev = (int*)calloc(capacity, sizeof(int));

    list->dump_file = fopen("dump.html", "w");

    list->data[0] = CANARY;
    list->head = 1;
    list->tail = 1;

    list->next[0] = 0;

    list->prev[0] = 0;
    list->free = 1; 

    
    for (size_t index = 1; index < capacity; index++) // TODO rename index
    {
        list->data[index] = POIZON;
        list->next[index] = -(int)index - 1;
    }
}

void DestroyList(list* list)
{
    free(list->data);
    free(list->prev);
    free(list->next);
    fclose(list->dump_file);
}



void ListAdd(list* list, double element, size_t index_previous)
{
    if(list->free == 1)
    {
        printf("empty list\n");
        list->data[list->free] = element;
        list->next[list->free] = 0;
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

    if(index_previous == list->tail)
    {
        printf("tail index\n");
        list->data[list->free] = element;
        list->tail = list->free;

        printf("%d\n",  -list->next[list->free]);
        
        int next_free = -list->next[list->free];
        list->next[list->free] = 0;
        list->free = next_free;
        list->next[index_previous] = list->tail;
        return;
    }
    int next_free = -list->next[list->free];
    list->data[list->free] = element;
    list->next[list->free] = list->next[index_previous];
    list->next[index_previous] = list->free; 
    list->free = next_free;
}

void ListDelete(list* list, size_t index_previous)
{
    list->next[index_previous] = list->next[list->next[index_previous]];
}