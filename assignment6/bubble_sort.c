#include "header.h"

void bubble_sort(Array *array , const char *mode) {
    int n = array->size;
    for(int i = 0 ; i<n ; i++) {
        for(int j = 0 ; j<n-i-1 ; j++) {
            if(strcmp(mode , "ASC")==0) {
                if (array->compare_func(array->data[j], array->data[j+1]) > 0) {
                    void *tmp = array->data[j];
                    array->data[j] = array->data[j+1];
                    array->data[j+1] = tmp;
                }
            } else if (strcmp(mode , "DESC")==0) {
                if (array->compare_func(array->data[j], array->data[j+1]) < 0) {
                    void *tmp = array->data[j];
                    array->data[j] = array->data[j+1];
                    array->data[j+1] = tmp;
                }
            } else {
                printf("\nMode is Invalid\n");
                return;
            }
        }
    }
}