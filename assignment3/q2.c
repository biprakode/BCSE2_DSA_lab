#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100

typedef struct linklist {
    char data[MAX_DATA];
    int number;
    struct linklist *next;
} node;

typedef struct queue {
    int counter;
    node *start;
    node *end;
} queue;

queue *queue_init() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->start = (node *)malloc(sizeof(node));
    q->start->number = 0;
    q->start->next = NULL;
    q->end = q->start;
    q->counter = 0;
    return q;
}

node *createlist(queue *q, node *record) {
    char data_[MAX_DATA];
    printf("Enter dataitem (END):- ");
    scanf("%s", data_);
    if (strcmp(data_, "END") == 0) {
        free(record);
        q->end->next = NULL;
        return q->end;
    } else {
        strncpy(record->data, data_, MAX_DATA - 1);
        record->data[MAX_DATA - 1] = '\0';
        record->number = ++q->counter;
        node *nextrecord = (node *)malloc(sizeof(node));
        nextrecord->next = NULL;
        q->end = record;
        q->end->next = nextrecord;
        return createlist(q, nextrecord);
    }
}

void displaylist(queue *q) {
    printf("\n");
    node *record = q->start;
    do {
        printf("%d) %s\n", record->number, record->data);
        record = record->next;
        if (record->next == NULL) {
            printf("%d) %s\n", record->number, record->data);
            break;
        }
    } while (1);
    printf("\n");
}

void newlist(queue *q) {
    q->end = createlist(q, q->start);
}

void enqueue(queue *q, char *data_) {
    node *record = (node *)malloc(sizeof(node));
    strncpy(record->data, data_, MAX_DATA - 1);
    record->data[MAX_DATA - 1] = '\0';
    record->number = ++q->counter;
    record->next = NULL;
    q->end->next = record;
    q->end = record;
}

char *deque(queue *q) {
    static char result[MAX_DATA];
    node *delstart = q->start;
    strncpy(result, delstart->data, MAX_DATA);
    q->start = q->start->next;
    node *temp = q->start;
    while (temp) {
        temp->number--;
        temp = temp->next;
    }
    free(delstart);
    return result;
}

char *peek(queue *q) {
    static char result[MAX_DATA];
    strncpy(result, q->start->data, MAX_DATA);
    return result;
}

void queue_free(queue *q) {
    node *current = q->start;
    node *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(q);
}

int main() {
    queue *que = queue_init();
    int choice;
    char data_[MAX_DATA];

    do {
        printf("1. Create List\n");
        printf("2. Enqueue\n");
        printf("3. Dequeue\n");
        printf("4. Peek\n");
        printf("5. Display List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Creating List...\n");
                newlist(que);
                displaylist(que);
                break;
            case 2:
                printf("Enter data to enqueue: ");
                scanf("%s", data_);
                enqueue(que, data_);
                break;
            case 3:
                printf("Dequeued item: %s\n", deque(que));
                break;
            case 4:
                printf("Peek item: %s\n", peek(que));
                break;
            case 5:
                printf("Displaying List...\n");
                displaylist(que);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    queue_free(que);
    return 0;
}