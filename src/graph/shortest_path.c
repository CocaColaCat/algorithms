#include <stdio.h>
#include <stdlib.h>
#include "graph.c"
#include "../data_structure/stack_queue.c"

// #Single-source shortest paths: 
// Given a graph and a source vertex s, support que- ries of the form Is there a 
// path from s to a given target vertex v? If so, find a shortest such path 
// (one with a minimal number of edges).
void doBft(Graph* graph, Queue* queue, bool* marked, int* edgeTo){
	if(IsQueueEmpty(queue)){
		puts("\n--- traverse is done. ---");
	}else{
		// deal with current node: pop queue, find list's head, 
		int top = QueueTop(queue);
		QueuePop(queue);
		AdjListNode* node = graph->array[top].head;

		if(!marked[top])
			printf("%i ",top);

		marked[top] = true;
		while(node){
			if(!marked[node->dest]){
				edgeTo[node->dest] = top;
				QueuePush(queue, node->dest);
			}
			node = node->next;
		}
		doBft(graph, queue, marked, edgeTo	);
	}
};

void bft(Graph* graph, int pivot, bool* marked, int* edgeTo){
	Queue* queue = CreateQueue();
	QueuePush(queue,pivot);
	printf("--- traverse start from %i ---\n", pivot);
	doBft(graph, queue, marked, edgeTo);
};

void paths(Graph* graph, int src, bool* marked, int* edgeTo){
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
			while(!IsStackEmpty(s)){
				printf(" %i ", StackTop(s));
				StackPop(s);
			}
			printf("\n");
		}else{
			printf("--- path not detected for %i ---\n", i);
		}
	}
};

bool hasPathTo(Graph* graph, int src, int dest, bool* marked, int* edgeTo){
	return marked[dest];
};

void pathTo(Graph* graph, int src, int dest, bool* marked, int* edgeTo){
	if(marked[dest]){
		printf("--- path from %i to %i ---\n", src, dest);
		Stack* s = StackCreate();
		while(dest != src){
			StackPush(s, dest);
			dest = edgeTo[dest];
		}
		StackPush(s, src);
		while(!IsStackEmpty(s)){
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
	addEdge(graph, 5, 0);
	addEdge(graph, 1, 6);
	return graph;  
};

int main(){
	int src = 0;
	int dest = 6;
	Graph* graph = fetchGraph();
	bool* marked = malloc(graph->V*sizeof(bool));
	for(int i=0;i<graph->V;i++){
		marked[i] = false;
	}
	int* edgeTo = malloc(graph->V*sizeof(int));
	bft(graph, src, marked, edgeTo);
	// for(int i=1; i<graph->V;i++){
	// 	printf("edge from %i to %i\n", i, edgeTo[i]);
	// }
	// bool r = hasPathTo(graph, src, dest, marked, edgeTo);
	// printf("%i\n", r);
	// pathTo(graph, src, dest, marked, edgeTo);
	paths(graph, src, marked, edgeTo);
	return 1;
}