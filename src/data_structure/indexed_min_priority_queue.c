#include <stdio.h>
#include <stdlib.h>
#include "indexed_min_priority_queue.h"

IndexMinQueue* createIndexMinQueue(int size){
	IndexMinQueue* queue = malloc(sizeof(IndexMinQueue));
	queue->size = 0;
	queue->pq = malloc((size+1)*sizeof(int));
	queue->qp = malloc(size*sizeof(int));
	queue->keys = malloc(size*sizeof(double));
	return queue;
}

void insert(IndexMinQueue* queue, int i, double value){
	printf("index is %d, value is %.2f\n", i, value);
	queue->keys[i] = value;
	queue->size = queue->size + 1;
	queue->pq[queue->size] = i;
	swim(queue, queue->size);
	printf("current min value is %.2f\n", topValue(queue));
}

void swim(IndexMinQueue* queue, int i){
	if(i<=1)
		return;
	int parent_index = queue->pq[i/2];
	int child_index = queue->pq[i];
	printf("parent_index is %d,value is %.2f, child_index is %d, value is %.2f\n", parent_index,queue->keys[parent_index], child_index, queue->keys[child_index]);
	if(queue->keys[parent_index] > queue->keys[child_index]){
		queue->pq[i/2] = child_index;
		queue->pq[i] = parent_index;
		queue->qp[child_index] = i/2;
		queue->qp[parent_index] = i;
		swim(queue, i/2);
	}
}

double topValue(IndexMinQueue* queue){
	if(isEmpty(queue)){
		printf("queue is empty\n");
		return 0.00001;
	}else{
		return queue->keys[queue->pq[1]];
	}
}

bool isEmpty(IndexMinQueue* queue){
	if(queue->size == 0){
		return true;
	}else{
		return false;
	}
}

void printQueue(IndexMinQueue* queue){
	printf("queue‘s value is:");
	for(int i = 1; i<=queue->size; i++){
		printf(" -> %.2f, position is %i\n", queue->keys[queue->pq[i]], i);
	}
	printf("\n");
}

int main(){
	double doubles[] = {0.2, 0.9, 1.4, 2, 0.11, 1.1, 1.8, 3.4, 0.13};
	IndexMinQueue* queue = createIndexMinQueue(9);
	printf("%p\n", queue);
	for(int i = 0; i < 9; i++)
		insert(queue, i, doubles[i]);
	printQueue(queue);
	return 1;
}
