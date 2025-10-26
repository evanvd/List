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
};

void InitList(list* list, int count);
void DestroyList(list* list);

void ListAdd(list* list, double element, size_t index_previous);
void ListDelete(list* list, size_t index_previous);
#endif