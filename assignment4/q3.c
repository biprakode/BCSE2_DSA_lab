#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node_struct {
    int num;
    struct Node_struct *next;
} Node;

Node *head = NULL;

void push(int num) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newnode->num = num;
    newnode->next = head;
    head = newnode;
}

int pop() {
    if (head == NULL) {
        return -1; // Stack is empty
    }
    Node *temp = head;
    int num = temp->num;
    head = head->next;
    free(temp);
    return num;
}

char *expression(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("Error: Cannot open file %s\n", path);
        return NULL;
    }
    
    // Allocate space for the expression + null terminator
    char *exp = (char *)malloc(sizeof(char) * 100); 
    if (exp == NULL) {
        perror("Memory allocation failed");
        fclose(f);
        return NULL;
    }

    // Read up to 99 characters or until newline is found
    if (fscanf(f, "%99[^\n]", exp) == 1) { 
        printf("Expression read successfully\n");
    } else {
        printf("Error: No expression found in file\n");
        free(exp);
        exp = NULL;
    }
    fclose(f);
    return exp;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int evaluator(const char *exp) {
    if (exp == NULL) return 0;
    
    int len = strlen(exp);
    // Iterate from right to left for Prefix notation evaluation
    for (int i = len - 1; i >= 0; i--) { 
        if (exp[i] == ' ')
            continue;
            
        if (isdigit(exp[i])) {
            push(exp[i] - '0'); 
        }
        else if (isOperator(exp[i])) {
            int operand1 = pop(); // Second operand
            
            if (operand1 == -1) {
                printf("Error: Invalid expression - missing operand for operator '%c'\n", exp[i]);
                return 0;
            }

            int operand2 = pop(); // First operand
            
            if (operand2 == -1) {
                printf("Error: Invalid expression - missing second operand for operator '%c'\n", exp[i]);
                // Restore operand1 onto stack if possible, but returning 0 is safer.
                return 0;
            }
            
            // Operation is: operand2 Op operand1
            switch (exp[i]) {
                case '+':
                    push(operand2 + operand1);
                    break;
                case '-':
                    push(operand2 - operand1); // FIX: Correct order for subtraction
                    break;
                case '*':
                    push(operand2 * operand1);
                    break;
                case '/':
                    if (operand1 == 0) { // Division by zero check on the divisor (operand1)
                        printf("Error: Division by zero\n");
                        return 0;
                    }
                    push(operand2 / operand1); // FIX: Correct order for division
                    break;
            }
        } else {
            printf("Error: Invalid character '%c' in expression.\n", exp[i]);
            return 0;
        }
    }
    
    int result = pop();
    
    // Check if the stack was empty before the final pop
    if (result == -1) {
        printf("Error: Invalid expression - no result found (empty expression or too many operators).\n");
        return 0;
    }

    // Check for remaining operands (e.g., "1 2 3")
    if (head != NULL) {
        printf("Warning: Stack not empty after evaluation - too many operands.\n");
        // Clear the remaining stack nodes to prevent memory leak
        while (head != NULL) {
            pop(); // discard remaining
        }
    }
    
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    char *exp = expression(argv[1]);
    if (exp == NULL) {
        return 1;
    }
    
    printf("Expression: %s\n", exp);
    printf("Result: %d\n", evaluator(exp));
    
    free(exp);
    return 0;
}