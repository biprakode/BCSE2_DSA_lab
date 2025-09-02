#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#define MAX 100

typedef struct Stack_struct {
	void *data;
	int top;
	size_t elem_size;
}Stack;

typedef struct Queue_struct {
	void *data;
	int front;
	int rear;
	size_t elem_size;
}Queue;

Stack *create_Stack(size_t elem_size);

int s_isFull(Stack *stack);
int s_isEmpty(Stack *stack);
void s_push(Stack **stack , void *elem);
void s_pop(Stack **stack , void **pop_elem);
void s_peek(Stack **stack , void **pop_elem);
void s_delete(Stack **stack);

Queue *create_Queue(size_t elem_size);

int q_isFull(Queue *queue);
int q_isEmpty(Queue *queue);
void q_push(Queue **queue , void *elem);
void q_pop(Queue **queue , void **pop_elem);
void q_peek(Queue **stack , void **pop_elem);
void q_delete(Queue **queue);

typedef void (*InputFunc)(void *out_elem);
typedef void (*PrintFunc)(void *elem);

void stack_main(size_t elem_size, InputFunc input, PrintFunc print);
void queue_main(size_t elem_size, InputFunc input, PrintFunc print);