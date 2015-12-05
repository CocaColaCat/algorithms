#include <stdio.h>
#include <stdlib.h>
#include "graph.c"
#include "queue.c"

void doBft(Graph* graph, Queue* queue, bool* checked){
	if(IsEmpty(queue)){
		puts("\n--- traverse is done. ---");
	}else{
		// deal with current node: pop queue, find list's head, 
		int top = QueueTop(queue);
		QueuePop(queue);
		AdjListNode* node = graph->array[top].head;

		if(!checked[top])
			printf("%i ",top);

		checked[top] = true;
		while(node){
			if(!checked[node->dest])
				QueuePush(queue, node->dest);
			node = node->next;
		}
		doBft(graph, queue, checked);
	}
};

void bft(Graph* graph, int pivot){
	Queue* queue = CreateQueue();
	QueuePush(queue,pivot);
	bool* checked = malloc(graph->V*sizeof(bool));
	for(int i=0;i<graph->V;i++){
		checked[i] = false;
	}
	printf("--- traverse start from %i ---\n", pivot);
	doBft(graph, queue, checked);
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
	bft(graph, 0);
	return 1;
}