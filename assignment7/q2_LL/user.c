#include "header.h"

const void print_int(const void *data) {
    if (data) {
        printf("%d", *(int *)data);
    } else {
        printf("NULL");
    }
}

const void delete_int(const void *data) {
    if (data) {
        free(data);
    }
}

int *new_int(int value) {
    int *i = (int *)malloc(sizeof(int));
    if (!i) {
        perror("Failed to allocate int");
        exit(EXIT_FAILURE);
    }
    *i = value;
    return i;
}


int main() {
    srand(time(0));

    printf("--- 1. MAX-PRIORITY QUEUE (Highest Key First) ---\n");
    
    heap *max_pq = init_pq("max", print_int, delete_int);
    
    printf("Inserting elements:\n");
    en_queue(max_pq, new_int(10), 10);
    printf("  Inserted (Key: 10)\n");
    en_queue(max_pq, new_int(50), 50);
    printf("  Inserted (Key: 50)\n");
    en_queue(max_pq, new_int(20), 20);
    printf("  Inserted (Key: 20)\n");
    en_queue(max_pq, new_int(99), 99);
    printf("  Inserted (Key: 99) -> Should be new head\n");
    en_queue(max_pq, new_int(40), 40);
    printf("  Inserted (Key: 40)\n");

    printf("\nQueue Size: %zu\n", max_pq->size);
    
    // Test peek
    peek(max_pq);
    
    printf("\nDequeuing in Priority Order (Max-Key First):\n");
    while (max_pq->head != NULL) {
        printf("  Dequeued Key (%ld): ", max_pq->head->key);
        max_pq->print_func(max_pq->head->data);
        printf("\n");
        de_queue(max_pq);
    }
    printf("Queue Size after emptying: %zu\n", max_pq->size);
    
    delete(max_pq);

    printf("\n--- 2. MIN-PRIORITY QUEUE (Lowest Key First) ---\n");
    
    // Initialize Min-PQ
    heap *min_pq = init_pq("min", print_int, delete_int);
    
    printf("Inserting elements:\n");
    en_queue(min_pq, new_int(5), 5);
    printf("  Inserted (Key: 5)\n");
    en_queue(min_pq, new_int(80), 80);
    printf("  Inserted (Key: 80)\n");
    en_queue(min_pq, new_int(1), 1);
    printf("  Inserted (Key: 1) -> Should be new head\n");
    en_queue(min_pq, new_int(10), 10);
    printf("  Inserted (Key: 10)\n");
    en_queue(min_pq, new_int(55), 55);
    printf("  Inserted (Key: 55)\n");

    printf("\nQueue Size: %zu\n", min_pq->size);
    
    // Test peek
    peek(min_pq);

    printf("\nDequeuing in Priority Order (Min-Key First):\n");
    while (min_pq->head != NULL) {
        printf("  Dequeued Key (%ld): ", min_pq->head->key);
        min_pq->print_func(min_pq->head->data);
        printf("\n");
        de_queue(min_pq);
    }
    
    // Cleanup Min-PQ structure
    delete(min_pq);
    
    return 0;
}