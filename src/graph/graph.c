#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode{
	int dest;
	struct AdjListNode* next;
}AdjListNode;

typedef struct AdjList
{
	struct AdjListNode* head;	
}AdjList;

typedef struct Graph
{
	int V;
	struct AdjList* array;
}Graph;

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

AdjListNode* newAdjListNode(int dest)
{
	AdjListNode* node = malloc(sizeof(AdjListNode));
	node->dest = dest;
	node->next = NULL;
	return node;
};

void addEdge(Graph *graph, int src, int dest){
	AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
};

void printGraph(Graph *graph){
	for(int i=0; i<graph->V; i++){
		printf("\n Adjacency list of vertex %d\n head ", i);
		AdjListNode *head = graph->array[i].head;
		while(head){
			printf("-> %d", head->dest);
			head = head->next;
		}
		printf("\n");
	}
};