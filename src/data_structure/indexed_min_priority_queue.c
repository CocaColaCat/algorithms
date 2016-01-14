#include <stdio.h>
#include <stdlib.h>
#include "indexed_min_priority_queue.h"

IndexMinQueue* createIndexMinQueue(int size){
	IndexMinQueue* queue = malloc(sizeof(IndexMinQueue));
	queue->size = 0;
	queue->pq = malloc((size+1)*sizeof(int));
	queue->qp = malloc(size*sizeof(int));
	return queue;
}

void insert(IndexMinQueue* queue, int i, double value){
	queue->keys[i] = value;
	queue->size = queue->size + 1;
	queue->pq[queue->size] = i;
	swim(queue, queue->size);
}

void swim(IndexMinQueue* queue, int i){
	int parent_index = queue->pq[i/2];
	int child_index = queue->pq[i];
	if(queue->keys[parent_index] > queue->keys[child_index]){
		queue->pq[i/2] = child_index;
		queue->pq[i] = parent_index;
		queue->qp[child_index] = i/2;
		queue->qp[parent_index] = i;
		swim(queue, i/2);
	}
}

int main(){
	double doubles[] = {0.2, 0.9, 1.4, 2, 0.6, 1.1, 1.8, 3.4, 0.13};
	IndexMinQueue* queue = createIndexMinQueue(sizeof(doubles));
	printf("%p\n", queue);
	for(int i = 0; i < sizeof(doubles); i++)
		insert(queue, i, doubles[i]);
	return 1;
}