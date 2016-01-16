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
	queue->keys[i] = value;
	queue->size = queue->size + 1;
	queue->pq[queue->size] = i;
	swim(queue, queue->size);
}

void swim(IndexMinQueue* queue, int i){
	if(i<=1)
		return;
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

double topValue(IndexMinQueue* queue){
	if(isEmpty(queue)){
		printf("queue is empty\n");
		return 0.00001;
	}else{
		return queue->keys[queue->pq[1]];
	}
}

int topIndex(IndexMinQueue* queue){
	if(isEmpty(queue)){
		printf("queue is empty\n");
		return -1;
	}else{
		return queue->pq[1];
	}
}

bool isEmpty(IndexMinQueue* queue){
	if(queue->size == 0){
		return true;
	}else{
		return false;
	}
}

void deleteTop(IndexMinQueue* queue){
	// printf("about to delete\n");
	if(isEmpty(queue)){
		printf("queue is empty\n");
	}else{
		int lastIndex = queue->pq[queue->size];
		int topIndex = queue->pq[1];
		queue->pq[1] = lastIndex;
		queue->qp[lastIndex] = 1;
		queue->size = queue->size-1;
		sink(queue, 1);
	}
}

void sink(IndexMinQueue* queue, int i){
	if( isEmpty(queue) || (i > queue->size/2))
		return;
	// index of pq
	int leftChild = i*2;
	int rightChild = leftChild+1;

	// index of keys
	int leftIndex = queue->pq[leftChild];
	int rightIndex = queue->pq[rightChild];
	int curIndex = queue->pq[i];

	// value of keys
	double leftValue = queue->keys[leftIndex];
	double rightValue = queue->keys[rightIndex];
	double pValue = queue->keys[curIndex];

	// printf("cur i is %d index is %d value is %.2f, ", i, curIndex, pValue);
	int minIndex = i;

	if(pValue > leftValue){
		minIndex = leftChild;
	}

	if(rightChild <= queue->size){
		if(minIndex != i){
			if(leftValue > rightValue){
				minIndex = rightChild;
			}
		}else if(pValue > rightValue){
			minIndex = rightChild;
		}
	}

	if(minIndex != i){
		if(minIndex==leftChild){
			queue->pq[i] = leftIndex;
			queue->pq[leftChild] = curIndex;
			queue->qp[leftIndex] = i;
			queue->qp[i] = curIndex;
			sink(queue, leftChild);
		}else{
			queue->pq[i] = rightIndex;
			queue->pq[rightChild] = curIndex;
			queue->qp[rightIndex] = i;
			queue->qp[i] = curIndex;
			sink(queue, rightChild);
		}
	}
}

void change(IndexMinQueue* queue, int i, double v){
	queue->keys[i] = v;
	swim(queue, queue->qp[i]);
	sink(queue, queue->qp[i]);
}

bool isContained(IndexMinQueue* queue, int i){
	if(queue->keys[i]){
		return true;
	}else{
		return false;
	}
}

void printQueue(IndexMinQueue* queue){
	printf("queue‘s value is: \n");
	for(int i = 1; i<=queue->size; i++){
		printf(" -> %.2f, position(pq) is %i, index is %i\n", queue->keys[queue->pq[i]], i, queue->pq[i]);
	}
	printf("\n");
}

// int main(){
// 	double doubles[] = {0.2, 0.9, 1.4, 2, 0.11, 1.1, 1.8, 3.4, 0.13};
// 	int size = sizeof(doubles) / sizeof(doubles[0]);
// 	IndexMinQueue* queue = createIndexMinQueue(size);
// 	printf("%p\n", queue);
// 	for(int i = 0; i < size; i++)
// 		insert(queue, i, doubles[i]);
// 	printQueue(queue);
// 	deleteTop(queue);
// 	printQueue(queue);
// 	deleteTop(queue);
// 	printQueue(queue);
// 	deleteTop(queue);
// 	printQueue(queue);
// 	deleteTop(queue);
// 	printQueue(queue);
// 	return 1;
// }
