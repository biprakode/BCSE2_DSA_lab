#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct queue_s{
    char exp[200];
    int top;
}queue_struct;

int main() {
    printf("Enter expression (e.g., ab#ab):- ");
    char *exp = (char *)malloc(sizeof(char) * 200);
    if (exp == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
    
    queue_struct *queue = (queue_struct *)malloc(sizeof(queue_struct));
    if (queue == NULL) {
        perror("Memory allocation failed");
        free(exp);
        return 1;
    }
    queue->top = 0;

    if (fgets(exp, 200, stdin) == NULL) {
        printf("Error reading input.\n");
        free(exp);
        free(queue);
        return 1;
    }

    size_t len = strlen(exp);
    if (len > 0 && exp[len - 1] == '\n') {
        exp[len - 1] = '\0';
        len--;
    }

    int i = 0;
    while (exp[i] != '#' && exp[i] != '\0') {
        if (queue->top >= 200) { // Safety check for queue buffer
            printf("Error: Input string w is too long.\n");
            free(exp);
            free(queue);
            return 1;
        }
        queue->exp[queue->top] = exp[i];
        queue->top++;
        i++;
    }
    
    if (exp[i] != '#') {
        printf("The string is not of the form w#w (missing '#').\n");
        free(exp);
        free(queue);
        return 0;
    }

    i++; 
    
    int j = 0;
    while (exp[i] != '\0') {
        if (j >= queue->top) {
            printf("The string is not of the form w#w (second part is longer).\n");
            free(exp);
            free(queue);
            return 0;
        }

        if (exp[i] != queue->exp[j]) {
            printf("The string is not of the form w#w (mismatch in parts).\n");
            free(exp);
            free(queue);
            return 0;
        }
        i++;
        j++;
    }


    if (j == queue->top) {
        printf("The string is of the form w#w.\n");
    } else {
        printf("The string is not of the form w#w (parts have different lengths).\n");
    }

    free(exp);
    free(queue);
    return 0;
}