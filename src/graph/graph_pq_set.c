#include <stdio.h>
#include <stdlib.h>
typedef enum { false, true } bool;

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
	int E;
	struct AdjList* array;
}Graph;

Edge* createEdge(int v, int w, double weight){
	Edge* edge = malloc(sizeof(Edge));
	edge->v = v;
	edge->w = w;
	edge->weight = weight;
	return edge;
};

int other(Edge* edge, int v){
	if(edge->v == v){
		return edge->w;
	}else{
		return edge->v;
	}
};

Graph* createGraph(int V)
{
	Graph *graph = malloc(sizeof(Graph));
	graph->V = V;
	graph->E = 0;
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
	graph->E = graph->E+1;
	int v = edge->v;
	AdjListNode* vnode = newAdjListNode(edge);
	vnode->next = graph->array[v].head;
	graph->array[v].head = vnode;

	int w = edge->w;
	AdjListNode* wnode = newAdjListNode(edge);
	wnode->next = graph->array[w].head;
	graph->array[w].head = wnode;
};

Edge** egdes(Graph* graph){
	Edge** edges = malloc(graph->E*(sizeof(Edge*)));
	int e = 0;
	for(int i =0; i< graph->V; i++){
		AdjListNode* node = graph->array[i].head;
		while(node){
			Edge* edge = node->curEdge;
			if(other(edge, i) > i){
				edges[e] = edge;
				e = e+1;
			}
			node = node->next;
		}
	}
	return edges;
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

typedef struct MST
{
	int size;
	struct Edge** edges;
}MST;

MST* createMST(int size){
	MST* mst = malloc(sizeof(MST));
	mst->size = 0;
	mst->edges = malloc(size*sizeof(Edge *));
	return mst;
};

void insertEdgeToMST(MST* mst, Edge* edge){
	mst->edges[mst->size] = edge;
	mst->size = mst->size+1;
};

void printMst(MST* mst){
	Edge* edge;
	for(int i=0; (edge = mst->edges[i]); i++){
		printf("mst node from %d -> %d, weight is %.2f\n", edge->v, edge->w, edge->weight);
	}
};

typedef struct PriorityQueue
{
	int size;
	struct Edge** heap;
}PriorityQueue;

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

PriorityQueue* createPq(int size){
	PriorityQueue* pq = malloc(sizeof(PriorityQueue));
	pq->size = 0;
	pq->heap = malloc((size+1)*sizeof(Edge *));
	insertPq(pq, NULL);
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
		if((smallestIndex!=0)&& right && (left->weight > right->weight)){
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
	if(pq->size<=1){
		printf("queue is empty");
	}else{
		if(pq->size==2){
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

bool isPqEmpty(PriorityQueue* pq){
	return ((pq->size==1) ? true : false);
};

void printPq(PriorityQueue* pq){
	int i = 1;
	Edge* edge = pq->heap[i];
	while(edge){
		printf("pq node is v %d, w %d, weight %.2f\n", edge->v, edge->w, edge->weight);
		i ++;
		edge = pq->heap[i];
	}
}

typedef struct UnionSet{
	int* data;
	int count;
	int size;
}UnionSet;

UnionSet* initUnionSet(int eleCount){
	UnionSet* set = malloc(sizeof(UnionSet));
	set->count = eleCount;
	set->size = eleCount;
	set->data = malloc(sizeof(eleCount));
	for(int i =0; i< eleCount; i++){
		set->data[i] = i;
	}
	return set;
};

int find(UnionSet* set, int p){
	return set->data[p];
};

void doUnion(UnionSet* set, int p, int q){
	int pId = find(set, p);
	int qId = find(set, q);
	if(pId == qId)
		return;
	for(int i = 0; i< set->size; i++){
		if(set->data[i] == pId){
			set->data[i] = qId;
		}
	}
	set->count = set->count - 1;
};

bool connected(UnionSet* set, int p, int q){
	// printf("p is %i and top is %i, q is %i and top is %i\n",p, set->data[p], q, set->data[q]);
	return ((find(set, p) == find(set, q)) ? true : false);
};

void unionFind(UnionSet* set, int p, int q){
	if(connected(set, p, q)){
		printf("p %i and q %i is connected\n", p, q);
		return;
	}else{
		doUnion(set, p, q);
	}
};