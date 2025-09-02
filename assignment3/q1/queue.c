#include "header.h"

Queue *create_Queue(size_t elem_size) {
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->elem_size = elem_size;
	queue->front = -1;
	queue->rear = -1;
	queue->data = malloc(sizeof(elem_size)*MAX);
}

int q_isFull(Queue *queue) {
	return queue->rear == MAX-1;
}

int q_isEmpty(Queue *queue) {
	return queue->front == queue->rear;
}

void q_push(Queue **queue , void *elem) {
	if(q_isFull(*queue)) {
		printf("Queue Overflow\n");
		return;
	}
	(*queue)->rear++;
	void *target_data = (char *)(*queue)->data + ((*queue)->rear * (*queue)->elem_size); // cast data to char for byte pointer math
	memcpy(target_data , elem , (*queue)->elem_size);
	printf("Data Pushed\n");
}

void q_pop(Queue **queue , void **pop_elem) {
	if(q_isEmpty(*queue)) {
		printf("Queue empty\n");
		return;
	}
	void *target_data = (char *)(*queue)->data + (((*queue)->front+1) * (*queue)->elem_size);
	memcpy(*pop_elem , target_data , (*queue)->elem_size);
	(*queue)->front++;
	printf("Data popped to pointer");
}

void q_peek(Queue **queue , void **pop_elem) {
	if(q_isEmpty(*queue)) {
		printf("Queue empty\n");
		return;
	}
	void *target_data = (char *)(*queue)->data + ((*queue)->rear * (*queue)->elem_size);
	memcpy(*pop_elem , target_data , (*queue)->elem_size);
	printf("Data copied to pointer");
}


void q_delete(Queue **queue) {
	free((*queue)->data);
	free((*queue));
}




























