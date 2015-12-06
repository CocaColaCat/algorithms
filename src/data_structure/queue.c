#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 100

typedef enum { false, true } bool;

typedef struct Queue{
	int data[QUEUE_MAX];
	int size;
}Queue;

Queue* CreateQueue(){
	Queue* queue = malloc(sizeof(Queue));
	queue->size = 0;
	return queue;
};

int QueueTop(Queue* queue){
	if(queue->size == 0){
		puts("--- queue is empty. ---");
		return -1;
	}else{
		return queue->data[0];
	}
};

void QueuePop(Queue* queue){
	if(queue->size == 0){
		puts("--- queue is empty. ---");
	}else{
		for(int i=0;i<queue->size;i++){
			queue->data[i] = queue->data[i+1];
		}
		queue->size = queue->size-1;
	}
};

void QueuePush(Queue* queue, int value){
	if(queue->size == QUEUE_MAX){
		puts("--- queue is full. ---");
	}else{
		queue->data[queue->size+1] = value;
		queue->size = queue->size+1;
	}
};

bool IsEmpty(Queue* queue){
	return ((queue->size == 0) ? true : false);
};