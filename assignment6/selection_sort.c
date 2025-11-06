#include "header.h"

void selection_sort(Array *array, const char *mode) {
    int n = array->size;
    for(int i=0; i<n ; i++) {
        int min_idx = i;
        for(int j=i+1 ; j<n ; j++) {
            int comp = array->compare_func(array->data[j], array->data[min_idx]);
            if (strcmp(mode, "ASC") == 0) { 
                if (comp < 0) {
                    min_idx = j;
                }
            } else if (strcmp(mode, "DESC") == 0) { 
                if (comp > 0) { 
                    min_idx = j;
                }
            } else {
                printf("\nInvalid Mode\n");
                return;
            }
        }
        if (min_idx != i) {
            void *temp = array->data[i];
            array->data[i] = array->data[min_idx];
            array->data[min_idx] = temp;
        }
    }
}