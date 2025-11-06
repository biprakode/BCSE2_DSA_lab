#include "header.h"

void insertion_sort(Array *array , const char *mode) {
    int n = array->size;
    for(int i = 1 ; i<n ; i++) {
        int j = i-1;
        void *key = array->data[i];
        if(strcmp(mode , "ASC")==0) {
            while(j>=0 && array->compare_func(array->data[j] , key) > 0) {
                array->data[j+1] = array->data[j]; // keep shifting cuz array(0,j) sorted
                j--;
            }    
        }else if(strcmp(mode , "DESC")==0) {
            while(j>=0 && array->compare_func(array->data[j] , key) < 0) {
                array->data[j+1] = array->data[j]; // keep shifting cuz array(0,j) sorted
                j--;
            } 
        }else {
            printf("\nMode is Invalid\n");
            return;
        }
        array->data[j+1] = key;
    }
}