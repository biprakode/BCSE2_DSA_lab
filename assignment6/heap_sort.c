#include "header.h"

void heapify(Array *array, int i , const char *mode) {
    int largest = i;
    int left = LEFT(i);
    int right = RIGHT(i);

    if(strcmp(mode , "MAX") == 0) {
        if(left < array->size && array->compare_func(array->data[left] , array->data[largest]) > 0) {
        largest = left;
        }
        if(right < array->size && array->compare_func(array->data[right] , array->data[largest]) > 0) {
            largest = right;
        }
    }else if(strcmp(mode , "MIN") == 0) {
        if(left < array->size && array->compare_func(array->data[left] , array->data[largest]) < 0) {
        largest = left;
        }
        if(right < array->size && array->compare_func(array->data[right] , array->data[largest]) < 0) {
            largest = right;
        }
    }else {
        printf("\nInvalid Mode\n");
        return;
    }
    if(largest != i) {
        void *temp = array->data[largest];
        array->data[largest] = array->data[i];
        array->data[i] = temp;
        heapify(array , largest , mode);
    }
}

void buildMaxHeap(Array *array , const char *mode) {
    int n = array->size;
    for(int i = PARENT(n-1) ; i>=0 ; i--) {
        heapify(array , i , mode);
    }
}

void heapSort(Array *array , const char *mode) {
    const char *heap_mode = strcmp(mode, "ASC") == 0 ? "MAX" : "MIN";
    if (strcmp(mode, "DESC") == 0) heap_mode = "MIN";
    else if (strcmp(mode, "ASC") != 0) {
        printf("\nInvalid Mode\n");
        return;
    }
    
    int orig_size = array->size;
    buildMaxHeap(array , heap_mode);

    for(int i=array->size-1 ; i>0 ; i--) {
        void *temp = array->data[0];
        array->data[0] = array->data[i];
        array->data[i] = temp;
        array->size--;
        heapify(array , 0 , heap_mode);
    }
    array->size = orig_size;
}