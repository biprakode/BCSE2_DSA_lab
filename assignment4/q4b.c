#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue_s{
    char exp[200];
    int top;
}queue_struct;

int main() {
    printf("Enter expression:- ");
    char *exp = (char *)malloc(sizeof(char) * 200);
    queue_struct *queue = (queue_struct *)malloc(sizeof(queue_struct));
    queue->top = 0;
    scanf("%s", exp);
	int len = strlen(exp);
    int i = 0;
    while (i <= len/2-1) {
        queue->exp[queue->top] = exp[i];
        queue->top++;
        i++;
    }
    int j = 0;
    while (exp[i] != '\0') {
        if (exp[i] != queue->exp[j]) {
            printf("The string is not of the form ww.\n");
            free(exp);
            free(queue);
            return 0;
        }
        i++;
        j++;
    }

    if (j == queue->top) {
        printf("The string is of the form ww.\n");
    } else {
        printf("The string is not of the form ww(2).\n");
    }

    free(exp);
    free(queue);
    return 0;
}
