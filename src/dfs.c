#include <stdio.h>
#include <stdlib.h>
#include "graph.c"
#include "stack.c"

void doDft(Graph* graph, Stack* stack, bool* checked){
	if(IsEmpty(stack)){
		puts("\n--- traverse is done. ---");
	}else{
		// deal with current node: pop stack, find list's head, 
		int top = StackTop(stack);
		StackPop(stack);
		AdjListNode* node = graph->array[top].head;

		if(!checked[top])
			printf("%i ",top);

		checked[top] = true;
		while(node){
			if(!checked[node->dest])
				StackPush(stack, node->dest);
			node = node->next;
		}
		doDft(graph, stack, checked);
	}
};

void dft(Graph *graph, int pivot){
	Stack* stack = StackCreate();

	bool* checked = malloc(graph->V*sizeof(bool));
	for(int i=0;i<graph->V;i++){
		checked[i] = false;
	}

	// put pivot node into stack;
	StackPush(stack, pivot);
	printf("--- traverse start from %i ---\n", pivot);
	doDft(graph, stack, checked);
};

int main(){
	Graph* graph = createGraph(20);
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 3);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 9);
	addEdge(graph, 1, 5);
	addEdge(graph, 4, 7);
	addEdge(graph, 6, 1);
	addEdge(graph, 17, 6);
	addEdge(graph, 5, 3);
	addEdge(graph, 9, 2);
	addEdge(graph, 9, 8);
	addEdge(graph, 8, 1);
	addEdge(graph, 8, 2);
	addEdge(graph, 2, 5);
	addEdge(graph, 5, 7);
	printGraph(graph);
	dft(graph, 0);
	return 1;
}