#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

const char *expression(const char *path) {
    FILE *f = fopen(path , "r");
    const char *exp = (char *)malloc(sizeof(char) * 100);
    if(fscanf(f , "%[^\n]" , exp)) {
        printf("Expression read\n");
    }
    fclose(f);
    return exp;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int evaluator(const char *exp) {
    int len = strlen(exp);
    for (int i = len - 1; i >= 0; i--) {
    if (exp[i] == ' ')
        continue;
        
    if (isdigit(exp[i])) {
        push(exp[i] - '0'); 
    }

    else if (isOperator(exp[i])) {
            int operand1 = pop();
            int operand2 = pop();
            
            switch (exp[i]) {
                case '+':
                    push(operand1 + operand2);
                    break;
                case '-':
                    push(operand1 - operand2);
                    break;
                case '*':
                    push(operand1 * operand2);
                    break;
                case '/':
                    push(operand1 / operand2);
                    break;
            }
        }
    }
    return pop();
}

int main(int argc , char *argv[]) {
    const char *exp = expression(argv[1]);
    printf("Expression: %s\n", exp);
    printf("Result: %d\n", evaluator(exp));
    return 0;
}
