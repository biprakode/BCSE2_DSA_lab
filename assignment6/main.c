#include "header.h"

const unsigned int SIZES[] = {10000, 50000, 100000, 500000};
const int NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

int main() {
    srand(time(NULL)); 

    struct {
        const char *name;
        void *func;
        int uses_piv;
    } algorithms[] = {
        {"Bubble Sort", (void*)bubble_sort, 0},
        {"Insertion Sort", (void*)insertion_sort, 0},
        {"Selection Sort", (void*)selection_sort, 0},
        {"Heap Sort", (void*)heapSort, 0},
        {"Merge Sort", (void*)mergeSort, 0},
        {"Quick Sort", (void*)quick_sort, 1}
    };

    int num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    const char *pivot_modes[] = {"BEGIN", "MID", "RANDOM"};
    const int num_pivots = sizeof(pivot_modes) / sizeof(pivot_modes[0]);
    
    printf("\n\n--- Sorting Algorithm Efficiency Test Results ---\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-18s | %-5s | %-12s | %-4s | %-10s | %-10s | %10s ", 
           "Algorithm", "Size", "Data Type", "Mode", "Pivot Mode", "Average (s)");
    for (int t = 1; t <= NUM_TRIALS; t++) {
        printf("| Trial %d (s) ", t);
    }
    printf("|\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");

    
    for (int i = 0; i < NUM_SIZES; i++) {
        unsigned int size = SIZES[i];
        
        Array *random_arr = create_array(size);
        fill_random(random_arr);
        
        Array *sorted_arr = create_array(size);
        fill_sorted(sorted_arr);

        Array *reverse_arr = create_array(size);
        fill_reverse_sorted(reverse_arr);

        //ASCENDING mode
        for (int j = 0; j < num_algorithms; j++) {
            
            // Random Data Tests (ASC)
            run_test(random_arr, algorithms[j].func, algorithms[j].name, "Random", "ASC", algorithms[j].uses_piv ? "RANDOM" : NULL);
            
            // Sorted Data Tests (ASC)
            run_test(sorted_arr, algorithms[j].func, algorithms[j].name, "Sorted (Best)", "ASC", algorithms[j].uses_piv ? "BEGIN" : NULL);

            // Reverse Sorted Data Tests (ASC)
            run_test(reverse_arr, algorithms[j].func, algorithms[j].name, "Reverse (Worst)", "ASC", algorithms[j].uses_piv ? "END" : NULL);
            
            // Quick Sort specific
            if (algorithms[j].uses_piv) {
                // diff pivots
                for (int p = 0; p < num_pivots; p++) {
                    if (strcmp(pivot_modes[p], "RANDOM") != 0) { // Skip RANDOM
                        run_test(random_arr, algorithms[j].func, algorithms[j].name, "Random", "ASC", pivot_modes[p]);
                    }
                }
            }
        }
        
        free_array(random_arr);
        free_array(sorted_arr);
        free_array(reverse_arr);
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    return 0;
}