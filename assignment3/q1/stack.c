#include "header.h"

Stack *create_Stack(size_t elem_size) {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->elem_size = elem_size;
	stack->top = -1;
	stack->data = malloc(sizeof(elem_size)*MAX);
}

int s_isFull(Stack *stack) {
	return stack->top == MAX-1;
}

int s_isEmpty(Stack *stack) {
	return stack->top == -1;
}

void s_push(Stack **stack , void *elem) {
	if(s_isFull(*stack)) {
		printf("Stack Overflow\n");
		return;
	}
	(*stack)->top++;
	void *target_data = (char *)(*stack)->data + ((*stack)->top * (*stack)->elem_size); // cast data to char for byte pointer math
	memcpy(target_data , elem , (*stack)->elem_size);
	printf("Data Pushed\n");
}

void s_pop(Stack **stack , void **pop_elem) {
	if(s_isEmpty(*stack)) {
		printf("Stack empty\n");
		return;
	}
	void *target_data = (char *)(*stack)->data + ((*stack)->top * (*stack)->elem_size);
	memcpy(*pop_elem , target_data , (*stack)->elem_size);
	(*stack)->top--;
	printf("Data popped to pointer");
}


void s_peek(Stack **stack , void **pop_elem) {
	if(s_isEmpty(*stack)) {
		printf("Stack empty\n");
		return;
	}
	void *target_data = (char *)(*stack)->data + ((*stack)->top * (*stack)->elem_size);
	memcpy(*pop_elem , target_data , (*stack)->elem_size);
	printf("Data copied to pointer");
}

void s_delete(Stack **stack) {
	free((*stack)->data);
	free((*stack));
}



























