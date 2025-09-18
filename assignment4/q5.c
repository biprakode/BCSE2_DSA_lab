#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    exp[200];
    int top;
}queue_struct;

int isPalindrome(queue_struct *queue) {
    int start = 0;
    int end = queue->top - 1;

    while (start < end) {
        if (queue->exp[start] != queue->exp[end]) {
            return 0; // Not a palindrome
        }
        start++;
        end--;
    }
    return 1; // Is a palindrome
}

int main() {
    printf("Enter expression (end with #):- ");
    char *exp = (char *)malloc(sizeof(char) * 200);
    queue_struct *queue = (queue_struct *)malloc(sizeof(queue_struct));
    queue->top = 0;

    scanf("%s", exp);
    int i = 0;

    // Enqueue characters into the queue until '#'
    while (exp[i] != '#') {
        queue->exp[queue->top] = exp[i];
        queue->top++;
        i++;
    }

    // Check if the string is of the form w#w
    i++; // Skip the '#'
    int j = 0;
    while (exp[i] != '\0') {
        if (exp[i] != queue->exp[j]) {
            printf("The string is not of the form w#w.\n");
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
        printf("The string is not of the form w#w.\n");
    }

    free(exp);
    free(queue);
    return 0;
}