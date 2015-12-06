#include <stdio.h>
#include <stdlib.h>
#include "graph.c"
#include "../data_structure/stack.c"

// given graph, src and target, check if path exists from src to target
// find all paths from srcs to other vertexs
// return path from src to vertex

// #Single-source paths: 
// Given a graph and a source vertex s, support queries of the form Is there a path 
// from s to a given target vertex v? If so, find such a path.
void doDft(Graph* graph, Stack* stack, bool* marked, int* edgeTo){
	if(IsEmpty(stack)){
		puts("\n--- traverse is done. ---");
	}else{
		// deal with current node: pop stack, find list's head, 
		int top = StackTop(stack);
		StackPop(stack);
		AdjListNode* node = graph->array[top].head;

		if(!marked[top])
			printf("%i ",top);

		marked[top] = true;
		while(node){
			if(!marked[node->dest]){
				edgeTo[node->dest] = top;
				StackPush(stack, node->dest);
			}
			node = node->next;
		}
		doDft(graph, stack, marked, edgeTo);
	}
};

void dft(Graph *graph, int pivot, bool* marked, int* edgeTo){
	Stack* stack = StackCreate();

	// put pivot node into stack;
	StackPush(stack, pivot);
	printf("--- traverse start from %i ---\n", pivot);
	doDft(graph, stack, marked, edgeTo);
};

void paths(Graph* graph, int src){
	bool* marked = malloc(graph->V*sizeof(bool));
	for(int i=0;i<graph->V;i++){
		marked[i] = false;
	}
	int* edgeTo = malloc(graph->V*sizeof(int));
	dft(graph, src, marked, edgeTo);
	for(int i=0; i<graph->V;i++){
		if(i==src){
		}else if(marked[i]){
			printf("--- path from %i to %i: ->", src, i);
			Stack* s = StackCreate();
			int currentNode = i;
			while(currentNode != src){
				StackPush(s, currentNode);
				currentNode = edgeTo[currentNode];
			}
			StackPush(s, src);
			while(!IsEmpty(s)){
				printf(" %i ", StackTop(s));
				StackPop(s);
			}
			printf("\n");
		}else{
			printf("--- path not detected for %i ---\n", i);
		}
	}
};

bool hasPathTo(Graph* graph, int src, int dest){
	bool* marked = malloc(graph->V*sizeof(bool));
	for(int i=0;i<graph->V;i++){
		marked[i] = false;
	}
	int* edgeTo = malloc(graph->V*sizeof(int));
	dft(graph, src, marked, edgeTo);
	return marked[dest];
};

void pathTo(Graph* graph, int src, int dest){
	bool* marked = malloc(graph->V*sizeof(bool));
	for(int i=0;i<graph->V;i++){
		marked[i] = false;
	}
	int* edgeTo = malloc(graph->V*sizeof(int));
	dft(graph, src, marked, edgeTo);
	if(marked[dest]){
		printf("--- path from %i to %i ---\n", src, dest);
		Stack* s = StackCreate();
		while(dest != src){
			StackPush(s, dest);
			dest = edgeTo[dest];
		}
		StackPush(s, src);
		while(!IsEmpty(s)){
			printf("-> %i ", StackTop(s));
			StackPop(s);
		}
		puts("\n");
	}else{
		puts("--- path not detected. ---");
	}
}

Graph* fetchGraph(){
	Graph* graph = createGraph(8);
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 4);
	addEdge(graph, 4, 2);
	addEdge(graph, 2, 5);
	addEdge(graph, 5, 7);
	addEdge(graph, 1, 6);
	return graph;
};

int main(){
	int src = 0;
	int dest = 6;
	Graph* graph = fetchGraph();
	// bool r = hasPathTo(graph, src, dest);
	// printf("%i\n", r);
	// pathTo(graph, src, dest);
	paths(graph, src);
	return 1;
}