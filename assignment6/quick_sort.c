#include "header.h"

void quick_sort(Array *array , int lo , int hi , const char *mode , const char *piv_mode) {
    if(lo >= hi) return;

    int s = lo;
    int e = hi;
    void *piv;

    if(strcmp(piv_mode,"BEGIN")==0) {
        piv = array->data[s];
    }else if(strcmp(piv_mode , "END") == 0) {
        piv = array->data[e];
    }else if(strcmp(piv_mode , "MID") == 0) {
        piv = array->data[lo + (hi - lo) / 2];
    }else if(strcmp(piv_mode , "RANDOM") == 0) {
        piv = array->data[lo + rand() % (hi - lo + 1)];
    }else {
        printf("\nInvalid piv_mode\n");
    }

    if(strcmp(mode , "ASC") == 0) {
        while(array->compare_func(array->data[s] , piv) < 0) {
            s++;
        }
        while(array->compare_func(array->data[e] , piv) > 0) {
            e--;
        }
    }else if(strcmp(mode , "DESC") == 0) {
        while(array->compare_func(array->data[s] , piv) > 0) {
            s++;
        }
        while(array->compare_func(array->data[e] , piv) < 0) {
            e--;
        }
    }else {
        printf("\nMode is Invalid\n");
        return;
    }

    if(s <= e) {
        void *temp = array->data[s];
        array->data[s] = array->data[e];
        array->data[e] = temp;
        s++;
        e--; 
    }

    quick_sort(array , lo , e , mode , piv_mode);
    quick_sort(array , s , hi , mode , piv_mode);
}