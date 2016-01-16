#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../data_structure/indexed_min_priority_queue.c"
#include "../data_structure/directed_weight_graph.c"

int* edgeTo = NULL;
double* disTo = NULL;
IndexMinQueue* queue = NULL;

void relax(Graph* graph, int v){
	AdjListNode* node = graph->array[v].head;
	while(node){
		Edge* edge = node->curEdge;
		int w = edge->w;
		if(disTo[w] > (disTo[v] + edge->weight)){
			edgeTo[w] = v;
			disTo[w] = disTo[v] + edge->weight;
			if(isContained(queue, w)){
				change(queue, w, disTo[w]);
			}else{
				insert(queue, w, disTo[w]);
			}
		}
		node = node->next;
	}
}

void dijkstraSPT(Graph* graph, int source){
	int size = graph->V;
	edgeTo = malloc(size*sizeof(int));
	disTo = malloc(size*sizeof(double));
	queue = createIndexMinQueue(graph->E);
	for(int i=0;i<size;i++)
		disTo[i] = DBL_MAX;

	disTo[source] = 0;
	insert(queue, source, 0.0);
	while(!isEmpty(queue)){
		int top = topIndex(queue);
		deleteTop(queue);
		relax(graph, top);
	}
}

Graph* generateGraph(){
	Edge* a = createEdge(4,5,0.35);
	Edge* b = createEdge(5,4,0.35);
	Edge* c = createEdge(4,7,0.37);
	Edge* d = createEdge(5,7,0.28);
	Edge* e = createEdge(7,5,0.28);
	Edge* f = createEdge(5,1,0.32);
	Edge* g = createEdge(0,4,0.38);
	Edge* h = createEdge(0,2,0.26);
	Edge* i = createEdge(7,3,0.39);
	Edge* j = createEdge(1,3,0.29);
	Edge* k = createEdge(2,7,0.34);
	Edge* l = createEdge(6,2,0.40);
	Edge* m = createEdge(3,6,0.52);
	Edge* n = createEdge(6,0,0.58);
	Edge* o = createEdge(6,4,0.93);

	Graph* graph = createGraph(8);
	addEdge(graph,a);
	addEdge(graph,b);
	addEdge(graph,c);
	addEdge(graph,d);
	addEdge(graph,e);
	addEdge(graph,f);
	addEdge(graph,g);
	addEdge(graph,h);
	addEdge(graph,i);
	addEdge(graph,j);
	addEdge(graph,k);
	addEdge(graph,l);
	addEdge(graph,m);
	addEdge(graph,n);
	addEdge(graph,o);
	return graph;
}

int main(){
	Graph* graph = generateGraph();
	int s = 0;
	dijkstraSPT(graph, s);
	for(int i=0;i<graph->V;i++){
		printf("edge to %i is %i\n", i, edgeTo[i]);
	}
	for(int i=0;i<graph->V;i++){
		printf("disTo to %i is %.2f\n", i, disTo[i]);
	}
	return 0;
}