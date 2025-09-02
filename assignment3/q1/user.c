#include "header.h"

void input_int(void *out) {
    printf("Enter int: ");
    scanf("%d", (int *)out);
}

void print_int(void *elem) {
    printf("%d", *(int *)elem);
}

int main() {
    stack_main(sizeof(int), input_int, print_int);
    queue_main(sizeof(int) , input_int , print_int);
}