#include "header.h"
#include <time.h>
#include <stdlib.h> // for rand, srand, malloc
#include <stdio.h>  // for printf, fopen, fclose, fscanf, fprintf

#define MAX 100
#define INT_FILE "int_data.txt"
#define DOUBLE_FILE "double_data.txt"

void dump_int_data(const char *filename, int count);
void read_int_data(const char *filename, heap *h);
void dump_double_data(const char *filename, int count);
void read_double_data(const char *filename, heap *h);

void print_int(void *data) {
        printf("%d", *(int *)data);
}

void print_double(void *data) {
        printf("%0.2lf", *(double *)data);
}

int main() {
    srand(time(0)); 
    
    printf("Dumping %d random integers to %s...\n", MAX, INT_FILE);
    dump_int_data(INT_FILE, MAX);
    
    heap *max_int_h = build_heap(20, "max");
    
    printf("Testing Max-Heap with ints read from %s:\n", INT_FILE);
    read_int_data(INT_FILE, max_int_h);
    
    print_queue(max_int_h, print_int);
    printf("Size: %d\n", get_size(max_int_h));
    
    if (get_size(max_int_h) > 0) {
        printf("Peek: %d\n", *(int *)get_peek(max_int_h));
        
        elem *ext1 = extract_peek(&max_int_h);
        printf("Extracted: key=%ld, value=", ext1->key);
        print_int(ext1->data);
        printf("\n");
        free(ext1->data);
        free(ext1); 
        
        print_queue(max_int_h, print_int);
        
        if (get_size(max_int_h) > 0) {
            elem **sorted_int = get_heap_sort(&max_int_h);
            printf("Heap Sorted (max, descending): ");
            for (int i = 0; i < MAX-1; i++) { 
                printf("Key=%ld, ", sorted_int[i]->key);
                print_int(sorted_int[i]->data);
                printf(" ");
                free(sorted_int[i]->data);
                free(sorted_int[i]);
            }
            printf("\n");
            free(sorted_int);
        } else {
            printf("Heap empty after extraction/sort. Nothing to sort.\n");
        }
    } else {
        printf("Heap is empty.\n");
    }
    
    free_heap(max_int_h);

    printf("\n--- Double Min-Heap Testing ---\n");
    
    // 3. Dump random doubles to file
    printf("Dumping %d random doubles to %s...\n", MAX, DOUBLE_FILE);
    dump_double_data(DOUBLE_FILE, MAX);
    
    heap *min_double_h = build_heap(15, "min");
    
    printf("Testing Min-Heap with doubles read from %s:\n", DOUBLE_FILE);
    read_double_data(DOUBLE_FILE, min_double_h);
    
    print_queue(min_double_h, print_double);
    printf("Size: %d\n", get_size(min_double_h));
    
    if (get_size(min_double_h) > 0) {
        printf("Peek: %0.2lf\n", *(double *)get_peek(min_double_h));
        
        elem *ext2 = extract_peek(&min_double_h);
        printf("Extracted: key=%ld, value=", ext2->key);
        print_double(ext2->data);
        printf("\n");
        free(ext2->data);
        free(ext2); 
        
        print_queue(min_double_h, print_double);
        
        if (get_size(min_double_h) > 0) {
            elem **sorted_double = get_heap_sort(&min_double_h);
            printf("Heap Sorted (min, ascending): ");
            for (int i = 0; i < MAX-1; i++) { 
                printf("Key=%ld, ", sorted_double[i]->key);
                print_double(sorted_double[i]->data);
                printf(" ");
            }
            printf("\n");
            for (int i = 0; i < MAX-1; i++) {
                free(sorted_double[i]->data);
                free(sorted_double[i]);
            }
            free(sorted_double);
        } else {
            printf("Heap empty after extraction/sort. Nothing to sort.\n");
        }
    } else {
        printf("Heap is empty.\n");
    }
    
    free_heap(min_double_h);

    return 0;
}

void dump_int_data(const char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening int file for writing");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        int val = rand() % 100;
        fprintf(fp, "%d\n", val);
    }
    
    fclose(fp);
}

void read_int_data(const char *filename, heap *h) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening int file for reading");
        return;
    }
    
    int val;
    while (fscanf(fp, "%d", &val) == 1) {
        int *data = (int *)malloc(sizeof(int));
        *data = val;
        long int key = *data;
        heap_insert(&h, data, key);
    }
    
    fclose(fp);
}

void dump_double_data(const char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening double file for writing");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        double val = (rand() % 10000) / 100.0;
        fprintf(fp, "%0.2lf\n", val);
    }
    
    fclose(fp);
}

void read_double_data(const char *filename, heap *h) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening double file for reading");
        return;
    }
    
    double val;
    // Note: fscanf with %lf for reading double from text file
    while (fscanf(fp, "%lf", &val) == 1) { 
        double *data = (double *)malloc(sizeof(double));
        *data = val;
        // Key calculation matches the original logic
        long int key = (long int)(*data * 100); 
        heap_insert(&h, data, key);
    }
    
    fclose(fp);
}