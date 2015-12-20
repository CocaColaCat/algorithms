#include <stdio.h>
#include <stdlib.h>
#include "weight_graph_and_priority_queue.c"

bool* createBooleanArray(int V){
	bool* visited = malloc(V*(sizeof(bool)));
	for(int i=0;i<V;i++){
		visited[i] = false;
	}
	return visited;
};

void visit(Graph* graph, PriorityQueue* pq, bool* visited, int v){
	visited[v] = true;
	AdjListNode *head = graph->array[v].head;
	while(head){
		int other = (head->curEdge->w == v) ? head->curEdge->v : head->curEdge->w;
		if(!visited[other]){
			insertPq(pq, head->curEdge);
		}
		head = head->next;
	}
}

MST* findMst(Graph* graph){
	MST* mst = createMST(graph->V);
	bool* visited = createBooleanArray(graph->V);
	PriorityQueue* pq = createPq(graph->E);
	visit(graph, pq, visited, 0);
	while(!isPqEmpty(pq)){
		Edge* edge = topPq(pq);		
		delPq(pq);
		if(visited[edge->v] && visited[edge->w]){
			// printf("node is ineligible\n");
		}else{
			// printf("----- about to insert node v %d, w %d\n", edge->v, edge->w);
			insertEdgeToMST(mst, edge);
			if(!visited[edge->v]){
				visit(graph, pq, visited, edge->v);
			}
			if(!visited[edge->w]){
				visit(graph, pq, visited, edge->w);
			}
		}
	}
	return mst;
};

Graph* createWeightGraph(){
	Edge* a = createEdge(4,5,0.35);
	Edge* b = createEdge(4,7,0.37);
	Edge* c = createEdge(5,7,0.28);
	Edge* d = createEdge(0,7,0.16);
	Edge* e = createEdge(1,5,0.32);
	Edge* f = createEdge(0,4,0.38);
	Edge* g = createEdge(2,3,0.17);
	Edge* h = createEdge(1,7,0.19);
	Edge* i = createEdge(0,2,0.26);
	Edge* j = createEdge(1,2,0.36);
	Edge* k = createEdge(1,3,0.29);
	Edge* l = createEdge(2,7,0.34);
	Edge* m = createEdge(6,2,0.40);
	Edge* n = createEdge(3,6,0.52);
	Edge* o = createEdge(6,0,0.58);
	Edge* p = createEdge(6,4,0.93);

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
	addEdge(graph,p);
	printGraph(graph);
	return graph;
};

int main(){
	Graph* graph = createWeightGraph();
	MST* mst = findMst(graph);
	printf("finish and print mst\n");
	printMst(mst);
	return 0;
}