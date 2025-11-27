#include "header.h"

heap *init_pq(const char *type, void (*p_func)(const void *), void (*d_func)(const void *)) {
    heap *PQ = (heap *)malloc(sizeof(heap));
    if (!PQ) {
        perror("Failed to allocate PQ structure");
        return NULL;
    }
    PQ->head = NULL;
    PQ->size = 0;
    PQ->print_func = p_func;
    PQ->delete_func = d_func;

    if (strcmp(type, "min") == 0) {
        PQ->is_max = false;
    } else if (strcmp(type, "max") == 0) {
        PQ->is_max = true;
    } else {
        fprintf(stderr, "Warning: Unknown heap type '%s'. Defaulting to Max-PQ.\n", type);
        PQ->is_max = true;
    }
    return PQ;
}

void en_queue(heap *PQ , void *newData , long int newKey) {
    elem *newNode = (elem *)malloc(sizeof(elem));
    newNode->data = newData;
    newNode->key = newKey;

    if (PQ->head == NULL || (PQ->is_max && newKey > PQ->head->key) || (!PQ->is_max && newKey < PQ->head->key)) {
        newNode->next = PQ->head;
        PQ->head = newNode;
    } else {
        elem *current = PQ->head;

        if(PQ->is_max == false) {
            while(current->next != NULL && current->key<=newNode->key) {
                current = current->next;
            }
        }else {
            while(current->next != NULL && current->key>=newNode->key) {
                current = current->next;
            }   
        }

        newNode->next = current->next;
        current->next = newNode;
    }
    PQ->size++;
}

void de_queue(heap *PQ) {
    if(PQ->head == NULL) {
        perror("EMPTY PQ");
    }
    elem *maxNode = PQ->head;
    PQ->head = PQ->head->next;
    PQ->size--;
    if (PQ->delete_func) {
        PQ->delete_func(maxNode->data);
    }
    free(maxNode);
}

elem *peek(heap *PQ) {
    if(PQ->head == NULL) {
        perror("EMPTY PQ");
    }
    printf("\nExtracted key( %ld):- " , PQ->head->key);
    PQ->print_func(PQ->head->data);
    return PQ->head;
}

void delete(heap *PQ) {
    if(PQ == NULL) return;
    
    elem* current = PQ->head;
    elem* nextNode;

    while (current != NULL) {
        nextNode = current->next; 
        
        if (PQ->delete_func) {
            PQ->delete_func(current->data);
        }
        free(current);
        current = nextNode;
    }
    PQ->head = NULL;
    PQ->size = 0;
    
    printf("PQ and all elements freed.\n");
    free(PQ);
}