#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node_struct {
    char bracket;
    struct Node_struct *next;
} Node;

Node *head = NULL;

void push(char num) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->bracket = num;
    newnode->next = head;
    head = newnode;
}

char pop() {
    if (head == NULL) {
        return '\0';
    }
    Node *temp = head;
    char num = temp->bracket;
    head = head->next;
    free(temp);
    return num;
}

int pair_matcher(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
}

void bracket_matcher(char *string) {
    int i = 0;
    int flag = 0;
    while (string[i] != '\0') { 
        if (string[i] == '(' || string[i] == '[' || string[i] == '{') {
            push(string[i]);
        } else if (string[i] == ')' || string[i] == ']' || string[i] == '}') {
            char top = pop();
            if (!pair_matcher(top, string[i])) {
                flag = 1;
                break;
            }
        }
        i++;
    }
    if (flag == 1 || head != NULL) { 
        printf("Brackets are not matched\n");
    } else {
        printf("Brackets are matched\n");
    }
}

int main() {
    char string[100];
    printf("Enter a string of brackets: ");
    scanf("%s", string);
    bracket_matcher(string);
    return 0;
}
