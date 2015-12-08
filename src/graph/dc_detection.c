#include <stdio.h>
#include <stdlib.h>
#include "general_graph.c"
#include "../data_structure/stack.c"

void dfs(Graph* graph, Stack* stack, bool* marked, int* edgeTo, bool* onStack, Stack* cycle){
	if(IsEmpty(stack)){
		puts("---- dfs done. ----");
	}else if(cycle != NULL){
		printf("---- cycle detected. ----\n");
		while(!IsEmpty(cycle)){
			printf("-> %i ", StackTop(cycle));
			StackPop(cycle);
		}
		printf("\n");
	}else{
		int head = StackTop(stack);
		StackPop(stack);
		onStack[head] = true;
		marked[head] = true;

		AdjListNode* adjNode = graph->array[head].head;	

		while(adjNode){
			if(!marked[adjNode->dest]){
				edgeTo[adjNode->dest] = head;
				StackPush(stack, adjNode->dest);
			}else if(onStack[adjNode->dest]){
				cycle = StackCreate();
				StackPush(cycle, adjNode->dest);
				while(head){
					StackPush(cycle, head);
					head = edgeTo[head];
				}	
				StackPush(cycle, adjNode->dest);
			}
			adjNode = adjNode->next;
		}
		dfs(graph, stack, marked, edgeTo, onStack, cycle);
	}
};

void hasCycle(Graph* graph){
	Stack* stack = StackCreate();
	bool* marked = malloc(graph->V*(sizeof(bool)));
	for(int i=0;i<graph->V;i++){
		marked[i] = false;
	}
	int* edgeTo = malloc(graph->V*(sizeof(int)));
	bool* onStack = malloc(graph->V*(sizeof(bool)));
	Stack* cycle = NULL;
	int src = 0;
	StackPush(stack, src);
	dfs(graph, stack, marked, edgeTo, onStack, cycle);
};

Graph* fetchGraph(){
	Graph* graph = createGraph(8, 1);
	addEdge(graph, 0, 4);
	addEdge(graph, 0, 1);
	addEdge(graph, 1, 6);
	addEdge(graph, 4, 2);
	addEdge(graph, 2, 5);
	addEdge(graph, 5, 0);
	addEdge(graph, 5, 7);
	addEdge(graph, 6, 0);
	return graph;  
};

int main(){
	Graph* graph = fetchGraph();
	printGraph(graph);
	hasCycle(graph);
}