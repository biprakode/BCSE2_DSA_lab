#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node_struct {
    int num;
    struct Node_struct *next;
}Node;

Node *head = NULL;

void push(int num) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->num = num;
    newnode->next = head;
    head = newnode;
}

int pop() {
    if (head == NULL) {
        return -1;
    }
    Node *temp = head;
    int num = temp->num;
    head = head->next;
    free(temp);
    return num;
}

void stacked_primes(long int number) {
    long int num_copy = number;
    int fact_count = 0;
    push(1);
    for(int i = 2 ; i<=sqrt(num_copy)+1 ; i++) {
        if(number % i == 0) {
            fact_count++;
            push(i);
            number/=i;
        }
    }
    if (number > 1) {
        push(number);
        fact_count++;
    }
    push(num_copy);
    if(fact_count == 0) {
        printf("Number is prime\n");
    }

    int *factors = (int *)malloc(fact_count * sizeof(int));
    int index = 0;
    while (head != NULL) {
        factors[index++] = pop();
    }
    //reversing for ascending order
    for (int i = index - 1; i >= 0; i--) {
            printf("%d", factors[i]);
            if (i > 0) printf(" , ");
        }
        printf("\n");
        
        free(factors);
}

int main() {
    long int number;
    printf("Enter a number:- ");
    scanf("%ld", &number);
    
    if (number <= 1) {
        printf("Please enter a number greater than 1.\n");
        return 1;
    }
    
    stacked_primes(number);
    
    return 0;
}

