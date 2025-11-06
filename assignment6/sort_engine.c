#include "header.h"

int compare_int(const void *a, const void *b) {
    const int *val_a = (const int *)a;
    const int *val_b = (const int *)b;

    if (*val_a < *val_b) return -1;
    if (*val_a > *val_b) return 1;
    return 0;
}

void free_int(void *data_ptr) {
    free(data_ptr);
}

Array *create_array(unsigned int size) {
    Array *arr = (Array *)malloc(sizeof(Array));
    if (!arr) {
        perror("Failed to allocate Array struct");
        return NULL;
    }

    arr->size = size;
    arr->compare_func = compare_int;
    arr->free_func = free_int;
    
    arr->data = (void **)malloc(size * sizeof(void *));
    if (!arr->data) {
        perror("Failed to allocate data array");
        free(arr);
        return NULL;
    }
    return arr;
}

void fill_random(Array *arr) {
    srand(time(NULL));
    for (unsigned int i = 0; i < arr->size; i++) {
        int *val = (int *)malloc(sizeof(int));
        if (!val) { perror("malloc failed"); return; }
        *val = rand() % 1000000; 
        arr->data[i] = val;
    }
}

//(Best case)
void fill_sorted(Array *arr) {
    for (unsigned int i = 0; i < arr->size; i++) {
        int *val = (int *)malloc(sizeof(int));
        if (!val) { perror("malloc failed"); return; }
        *val = i; 
        arr->data[i] = val;
    }
}

// (Worst Case)
void fill_reverse_sorted(Array *arr) {
    for (unsigned int i = 0; i < arr->size; i++) {
        int *val = (int *)malloc(sizeof(int));
        if (!val) { perror("malloc failed"); return; }
        *val = arr->size - 1 - i; 
        arr->data[i] = val;
    }
}

void free_array(Array *arr) {
    if (arr) {
        if (arr->data) {
            for (unsigned int i = 0; i < arr->size; i++) {
                if (arr->data[i]) {
                    arr->free_func(arr->data[i]);
                }
            }
            free(arr->data);
        }
        free(arr);
    }
}

//deepcopy
Array *copy_array(const Array *original) {
    Array *copy = create_array(original->size);
    if (!copy) return NULL;

    for (unsigned int i = 0; i < original->size; i++) {
        int *val_orig = (int *)original->data[i];
        int *val_copy = (int *)malloc(sizeof(int));
        if (!val_copy) { perror("malloc copy failed"); free_array(copy); return NULL; }
        *val_copy = *val_orig;
        copy->data[i] = val_copy;
    }
    return copy;
}

void run_test(const Array *original_arr, void *sort_func, const char *sort_name, const char *data_type, const char *mode, const char *pivot_mode) {
    double times[NUM_TRIALS];
    double total_time = 0;

    for (int t = 0; t < NUM_TRIALS; t++) {
        Array *test_arr = copy_array(original_arr);
        if (!test_arr) return;

        clock_t start = clock();

        if (strcmp(sort_name, "Quick Sort") == 0) {
            QuickSortFunc qs_func = (QuickSortFunc)sort_func; // cast to sort func 
            qs_func(test_arr, 0, test_arr->size - 1, mode, pivot_mode);
        } else if (strcmp(sort_name, "Merge Sort") == 0) {
            MergeSortFunc ms_func = (MergeSortFunc)sort_func;
            ms_func(test_arr, 0, test_arr->size - 1, mode); 
        } else {
            SortFunc s_func = (SortFunc)sort_func;
            s_func(test_arr, mode);
        }

        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        times[t] = cpu_time_used;
        total_time += cpu_time_used;
        
        free_array(test_arr);
    }

    double average_time = total_time / NUM_TRIALS;
    
    printf("| %-18s | %-5u | %-12s | %-4s | %-10s | %10.6f ", 
           sort_name, original_arr->size, data_type, mode, 
           pivot_mode ? pivot_mode : "N/A", // Pivot mode
           average_time);

    for (int t = 0; t < NUM_TRIALS; t++) {
        printf("| %8.6f ", times[t]);
    }
    printf("|\n");
}