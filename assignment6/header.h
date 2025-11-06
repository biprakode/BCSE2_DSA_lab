#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct array_struct {
    void **data;
    unsigned int size;
    int (*compare_func)(const void *a ,const void *b);
    void (*print_func)(void);
    void (*display_func)(void);
    void (*free_func)(void *);
}Array;
#include <time.h>
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) (((i) - 1) / 2)

#define NUM_TRIALS 5
extern const unsigned int SIZES[];
extern const int NUM_SIZES;

void bubble_sort(Array *array , const char *mode);
void insertion_sort(Array *array , const char *mode);
void quick_sort(Array *array , int lo , int hi , const char *mode , const char *piv_mode);
void mergeList(Array *array , int lo , int mid , int hi , const char *mode);
void mergeSort(Array *array , int lo , int hi ,const char *mode);
void heapify(Array *array, int i , const char *mode);
void buildMaxHeap(Array *array , const char *mode);
void heapSort(Array *array , const char *mode);
void selection_sort(Array *array, const char *mode);


int compare_int(const void *a, const void *b);
void free_int(void *data_ptr);
Array *create_array(unsigned int size);
void fill_random(Array *arr);
void fill_sorted(Array *arr);
void fill_reverse_sorted(Array *arr);
void free_array(Array *arr);
Array *copy_array(const Array *original);
typedef void (*SortFunc)(Array*, const char*);
typedef void (*QuickSortFunc)(Array*, int, int, const char*, const char*);
typedef void (*MergeSortFunc)(Array*, int, int, const char*);
void run_test(const Array *original_arr, void *sort_func, const char *sort_name, const char *data_type, const char *mode, const char *pivot_mode);

#endif