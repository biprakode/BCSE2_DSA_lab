#include "header.h"

typedef void (*InputFunc)(void *out_elem);
typedef void (*PrintFunc)(void *elem);


void stack_main(size_t elem_size, InputFunc input, PrintFunc print) {
    Stack *stack = create_Stack(elem_size);
    if (!stack) {
        printf("Error: could not create stack\n");
        return;
    }

    int choice = 0;
    while (choice != 4) {
        printf("\nEnter choice (1=Push, 2=Pop, 3=Peek, 4=Exit): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        void *buffer = malloc(elem_size);
        if (!buffer) { printf("Allocation failed\n"); break; }

        switch (choice) {
            case 1:
                input(buffer);
                s_push(&stack, buffer);
                break;

            case 2:
                if (!s_isEmpty(stack)) {
                    s_pop(&stack, &buffer);
                    printf("Popped: ");
                    print(buffer);
                    printf("\n");
                } else {
                    printf("Stack is empty\n");
                }
                break;

            case 3:
                if (!s_isEmpty(stack)) {
                    s_peek(&stack, &buffer);
                    printf("Top: ");
                    print(buffer);
                    printf("\n");
                } else {
                    printf("Stack is empty\n");
                }
                break;

            case 4:
                s_delete(&stack);
                printf("Stack deleted\n");
                break;

            default:
                printf("Invalid choice\n");
        }
        free(buffer);
    }
}

void queue_main(size_t elem_size, InputFunc input, PrintFunc print) {
    Queue *queue = create_Queue(elem_size);
    if (!queue) {
        printf("Error: could not create queue\n");
        return;
    }

    int choice = 0;
    while (choice != 4) {
        printf("\nEnter choice (1=Enqueue, 2=Dequeue, 3=Peek, 4=Exit): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        void *buffer = malloc(elem_size);
        if (!buffer) { printf("Allocation failed\n"); break; }

        switch (choice) {
            case 1:
                input(buffer);
                q_push(&queue, buffer);
                break;

            case 2:
                if (!q_isEmpty(queue)) {
                    q_pop(&queue, &buffer);
                    printf("Dequeued: ");
                    print(buffer);
                    printf("\n");
                } else {
                    printf("Queue is empty\n");
                }
                break;

            case 3:
                if (!q_isEmpty(queue)) {
                    q_peek(&queue, &buffer);
                    printf("Front: ");
                    print(buffer);
                    printf("\n");
                } else {
                    printf("Queue is empty\n");
                }
                break;

            case 4:
                q_delete(&queue);
                printf("Queue deleted\n");
                break;

            default:
                printf("Invalid choice\n");
        }
        free(buffer);
    }
}
