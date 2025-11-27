#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) (((i) - 1) / 2)

typedef struct elem_struct {
    void *data;       
    long int key;     
    struct elem_struct *next;
} elem;

typedef struct heap_struct {
    size_t size;
    bool is_max; 
    elem *head;
    const void (*print_func)(const void *data);
    const void (*delete_func)(const void *data);
} heap;

void print_int(const void *data);
void delete_int(const void *data);
int *new_int(int value);

heap *init_pq(const char *type, void (*p_func)(const void *), void (*d_func)(const void *)) ;
void en_queue(heap *PQ , void *newData , long int newKey);
void de_queue(heap *PQ);
elem *peek(heap *PQ);
void delete(heap *PQ);

#endif