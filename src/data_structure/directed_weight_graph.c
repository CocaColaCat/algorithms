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
};

void printGraph(Graph *graph){
	for(int i=0; i<graph->V; i++){
		printf("\n Adjacency list of vertex %d\n", i);
		AdjListNode *head = graph->array[i].head;
		while(head){
			printf("-> v: %d| w: %d| weight: %.2f\n", head->curEdge->v, head->curEdge->w, head->curEdge->weight);
			head = head->next;
		}
	}
};

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

// 	Graph* graph = createGraph(8);
// 	addEdge(graph,a);
// 	addEdge(graph,b);
// 	addEdge(graph,c);
// 	addEdge(graph,d);
// 	addEdge(graph,e);
// 	addEdge(graph,f);
// 	addEdge(graph,g);
// 	addEdge(graph,h);
// 	addEdge(graph,i);
// 	addEdge(graph,j);
// 	addEdge(graph,k);
// 	addEdge(graph,l);
// 	addEdge(graph,m);
// 	addEdge(graph,n);
// 	addEdge(graph,o);
// 	addEdge(graph,p);
// 	printGraph(graph);
// }