#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
	int v;
	int w;
	double weight;
}Edge;

typedef struct AdjListNode
{
	Edge* curEdge;
	struct AdjListNode* next;
}AdjListNode;

typedef struct AdjList
{
	struct AdjListNode* head;	
}AdjList;

typedef struct WeightGraph
{
	int V;
	struct AdjList* array;
}Graph;

Edge* createEdge(int v, int w, double weight){
	Edge* edge = malloc(sizeof(Edge));
	edge->v = v;
	edge->w = w;
	edge->weight = weight;
	return edge;
};

Graph* createGraph(int V)
{
	Graph *graph = malloc(sizeof(Graph));
	graph->V = V;
	graph->array = malloc(V*sizeof(AdjList)); // 创建 array of AdjList
	int i;
	for(int i=0; i<V; i++){
		graph->array[i].head = NULL;
	}
	return graph;
};

AdjListNode* newAdjListNode(Edge* curEdge)
{
	AdjListNode* node = malloc(sizeof(AdjListNode));
	node->curEdge = curEdge;
	node->next = NULL;
	return node;
};

void addEdge(Graph *graph, Edge* edge){
	int v = edge->v;
	AdjListNode* vnode = newAdjListNode(edge);
	vnode->next = graph->array[v].head;
	graph->array[v].head = vnode;

	int w = edge->w;
	AdjListNode* wnode = newAdjListNode(edge);
	wnode->next = graph->array[w].head;
	graph->array[w].head = wnode;
};

void printGraph(Graph *graph){
	for(int i=0; i<graph->V; i++){
		printf("\n Adjacency list of vertex %d\n", i);
		AdjListNode *head = graph->array[i].head;
		while(head){
			printf("-> v: %d| w: %d| weight: %.2f\n", head->curEdge->v, head->curEdge->w, head->curEdge->weight);
			head = head->next;
		}
		printf("\n");
	}
};

typedef struct PriorityQueue
{
	int size;
	struct Edge** heap;
}PriorityQueue;

PriorityQueue* createPq(int size){
	PriorityQueue* pq = malloc(sizeof(PriorityQueue));
	pq->size = 0;
	pq->heap = malloc(size*sizeof(Edge *));
	return pq;
};

Edge* topPq(PriorityQueue* pq){
	if(pq->size==1){
		printf("queue is empty.");
		return NULL;
	}else{
		return pq->heap[1];
	}
};

void swim(PriorityQueue* pq, int index){
	if(index < 2){
		return;
	}else{
		int parent = index/2;
		if(pq->heap[parent]->weight > pq->heap[index]->weight){
			Edge* parentEdge = pq->heap[parent];
			pq->heap[parent] = pq->heap[index];
			pq->heap[index] = parentEdge;
			swim(pq, parent);
		}
	}
};

void insertPq(PriorityQueue* pq, Edge* edge){
	// place edge after the last node
	pq->heap[pq->size] = edge;
	// increase pq size by 1
	pq->size = pq->size+1;
	swim(pq, pq->size-1);
};

void sink(PriorityQueue* pq, int index){
	if(index > (pq->size-1)/2){ // (pq->size-1)/2 最后一个有子节点的父节点的下标。如果大于这个下标，则停止递归。
		return;
	}else{
		int leftIndex = index*2;
		int rightIndex = leftIndex+1;
		Edge* left = pq->heap[leftIndex];
		Edge* right = pq->heap[rightIndex];
		Edge* parent = pq->heap[index];
		int smallestIndex = 0;

		// find smallest node bwteen parent,left and right.
		if(left && (parent->weight > left->weight)){
			smallestIndex = leftIndex;
		}
		// compare left and right
		if((smallestIndex!=0)&&(left->weight > right->weight)){
			smallestIndex = rightIndex;
		}
		// switch node position
		if((smallestIndex !=0) && (smallestIndex != index) && pq->heap[smallestIndex]){
			if(smallestIndex == leftIndex){
				pq->heap[leftIndex] = parent;	
				pq->heap[index] = left;
				sink(pq, leftIndex);			
			}else{
				pq->heap[rightIndex] = parent;
				pq->heap[index] = right;
				sink(pq, rightIndex);
			}
		}

	}
};

void delPq(PriorityQueue* pq){
	printf("pq size is %d\n", pq->size);
	if(pq->size<=1){
		printf("queue is empty");
	}else{
		if(pq->size==2){
			printf("size is 2");
			pq->heap[1] = NULL;
			pq->size = pq->size-1;
		}else{
			int last = pq->size-1;
			pq->heap[1] = pq->heap[last];
			pq->heap[last] = NULL;
			pq->size = pq->size-1;
			sink(pq, 1);			
		}
	}
};

void printPq(PriorityQueue* pq){
	int i = 1;
	Edge* edge = pq->heap[i];
	while(edge){
		i ++;
		edge = pq->heap[i];
	}
}

// int main(){
// 	Edge* a = createEdge(4,5,0.35);
// 	Edge* b = createEdge(4,7,0.37);
// 	Edge* c = createEdge(5,7,0.28);
// 	Edge* d = createEdge(0,7,0.16);
// 	Edge* e = createEdge(1,5,0.32);
// 	Edge* f = createEdge(0,4,0.38);
// 	Edge* g = createEdge(2,3,0.17);
// 	Edge* h = createEdge(1,7,0.19);
// 	Edge* i = createEdge(0,2,0.26);
// 	Edge* j = createEdge(1,2,0.36);
// 	Edge* k = createEdge(1,3,0.29);
// 	Edge* l = createEdge(2,7,0.34);
// 	Edge* m = createEdge(6,2,0.40);
// 	Edge* n = createEdge(3,6,0.52);
// 	Edge* o = createEdge(6,0,0.58);
// 	Edge* p = createEdge(6,4,0.93);

// 	PriorityQueue* pq = createPq(17);
// 	insertPq(pq, NULL);
// 	insertPq(pq, a);
// 	insertPq(pq, b);
// 	insertPq(pq, c);
// 	insertPq(pq, d);
// 	insertPq(pq, e);
// 	insertPq(pq, f);
// 	insertPq(pq, g);
// 	insertPq(pq, h);
// 	insertPq(pq, i);
// 	insertPq(pq, j);
// 	insertPq(pq, k);
// 	insertPq(pq, l);
// 	insertPq(pq, m);
// 	insertPq(pq, n);
// 	insertPq(pq, o);
// 	insertPq(pq, p);

// 	// printPq(pq);

// 	printf("smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// 	delPq(pq);
// 	printf("after delete, smallest node v is %d, w is %d, weight is %.2f\n", topPq(pq)->v, topPq(pq)->w, topPq(pq)->weight);
// }