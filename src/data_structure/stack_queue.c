#include <stdlib.h>
#include <stdio.h>
#define STACK_MAX 100
#define QUEUE_MAX 100
typedef enum { false, true } bool;

typedef struct Stack{
	int data[STACK_MAX];
	int size;
}Stack;

void StackInit(Stack *s){
	s->size = 0;
}

Stack* StackCreate(){
	Stack *s = malloc(sizeof(Stack));
	StackInit(s);
	return s;
}

int StackTop(Stack *s){
	if(s->size==0){
		puts("--- stack empty ---");
		return -1;
	}else{
		return s->data[s->size-1];
	}
}

void StackPush(Stack *s, int v){
	if(s->size >= STACK_MAX){
		puts("--- stack full ---");
	}else{
		s->size = s->size+1;
		s->data[s->size-1] = v;
	}
}

void StackPop(Stack *s){
	if(s->size==0){
		puts("--- stack empty ---");
	}else{
		s->size = s->size-1;
	}
}

bool IsStackEmpty(Stack *s){
	return ((s->size==0) ? true : false);
}

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

bool IsQueueEmpty(Queue* queue){
	return ((queue->size == 0) ? true : false);
};