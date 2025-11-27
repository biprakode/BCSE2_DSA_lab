#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

void gen_ints(int **array, size_t size) {
    *array = (int *)malloc(sizeof(int) * size);
    if (*array == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }
    for(int i = 0 ; i<size ; i++) {
        (*array)[i] = rand() % 500;
    }
}

int seq_search(int *array , int key , size_t size) {
    for(int i=0 ; i<size ; i++) {
        if(array[i] == key) {
            printf("Key found at index (sequential) :- %d\n" , i);
            return TRUE;
        }
    }
    return FALSE;
}

int bin_search(int *array , int key , size_t size , int lo , int hi) {
    if(lo > hi) {
        return FALSE;
    }
    int mid = lo + (hi - lo) / 2;
    if(array[mid] == key) {
        printf("Key found at index (binary) :- %d\n" , mid);
        return TRUE;
    }
    if(array[mid] > key) {
        return bin_search(array , key , size , lo , mid-1);  
    } else {
        return bin_search(array , key , size , mid+1 , hi); 
    }
}

int binary_search(int *array , int key , size_t size) {
    return bin_search(array , key , size , 0 , (int)size-1);
}

int compare_integers(const void *a, const void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    return *x - *y;
}

int main() {
    srand(time(0));
    int *array = NULL;
    size_t size = 1000;

    gen_ints(&array , size);
    qsort(array , size , sizeof(int) , compare_integers);

    int key_index = rand() % size; 
    int key = array[key_index];
    printf("Searching for key: %d (originally at index %d)\n", key, key_index);

    printf("\n--- Binary Search ---\n");
    int bin_result = binary_search(array , key , size);
    
    printf("\n--- Sequential Search ---\n");
    int seq_result = seq_search(array , key , size);

    if(!bin_result && !seq_result) {
        printf("Key not found in either search.\n");
    }

    free(array);
    return 0;
}