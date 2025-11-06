#include "header.h"

void mergeList(Array *array , int lo , int mid , int hi , const char *mode) {
    int l_size = mid-lo+1;
    int r_size = hi-mid;
    void **left_temp = (void **)malloc(l_size * sizeof(void *));
    void **right_temp = (void **)malloc(r_size * sizeof(void *));

    for(int i = 0 ; i < l_size ; i++) {
        left_temp[i] = array->data[lo + i];
    }
    for(int i = 0 ; i < r_size ; i++) {
        right_temp[i] = array->data[mid + 1 + i];
    }
    int i = 0 , j = 0 , k = lo;
    while(i<l_size && j<r_size) {
        if(strcmp(mode , "ASC") == 0) {
            if(array->compare_func(left_temp[i] , right_temp[j]) < 0) {
                array->data[k++] = left_temp[i++];
            }else {
                array->data[k++] = right_temp[j++];
            }
        }else if(strcmp(mode , "DESC") == 0) {
            if(array->compare_func(left_temp[i] , right_temp[j]) > 0) {
                array->data[k++] = left_temp[i++];
            }else {
                array->data[k++] = right_temp[j++];
            }
        } else {
            printf("\nInvalid Mode\n");
            free(left_temp);
            free(right_temp);
            return;
        }
    }

    while(i<l_size) {
        array->data[k++] = left_temp[i++];
    }
    while(j<r_size) {
        array->data[k++] = right_temp[j++];
    }

    free(left_temp);
    free(right_temp);
}

void mergeSort(Array *array , int lo , int hi ,const char *mode) {
    if(lo<hi) {
        int mid = (lo + hi)/2;
        mergeSort(array , lo , mid ,mode);
        mergeSort(array , mid+1 , hi , mode);
        mergeList(array , lo , mid , hi , mode);
    }
}