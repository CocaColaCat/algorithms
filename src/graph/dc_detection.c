#include <stdio.h>
#include <stdlib.h>
#include "general_graph.c"
#include "../data_structure/stack.c"

void dfs(Graph* graph, int src, bool* marked, int* edgeTo, bool* onStack, Stack* cycle){
		marked[src] = true;
		onStack[src] = true;
		AdjListNode* adjListNode = graph->array[src].head;
		while(adjListNode){
			if(cycle){
				return;
			}else if(!marked[adjListNode->dest]){
				// 如果当前的邻居是第一次到达，则建立 src 和 邻居之间的关联, 同时对邻居开始做 recusive
				// printf("build path from %i to %i\n",adjListNode->dest, src);
				edgeTo[adjListNode->dest] = src;
				dfs(graph, adjListNode->dest, marked, edgeTo, onStack, cycle);
			}else if(onStack[adjListNode->dest]){
				// 当前邻居已经到过了，那么就去判断这个邻居是不是在 stack 上，如果在，则说明形成了环路
				printf("--- cycle detected. ---\n");
				cycle = StackCreate();
				for(int x = src; x != adjListNode->dest; x=edgeTo[x])
					StackPush(cycle, x);
				StackPush(cycle, adjListNode->dest);
				StackPush(cycle, src);
				while(!IsEmpty(cycle)){
					printf("->%i ", StackTop(cycle));
					StackPop(cycle);
				}
				printf("\n");
			}
			adjListNode = adjListNode->next; // 指向下一个邻居
		}
		// 所有的邻居都处理完了，则也就是这个节点开始的对邻居的遍历也结束了，那么这个点就不在 stack 上了
		onStack[src] = false;
};

bool* createBooleanArray(int V){
	bool* marked = malloc(V*(sizeof(bool)));
	for(int i=0;i<V;i++){
		marked[i] = false;
	}
	return marked;
}

void hasCycle(Graph* graph){
	bool* marked = createBooleanArray(graph->V);
	int* edgeTo = malloc(graph->V*(sizeof(int)));
	bool* onStack = createBooleanArray(graph->V);
	Stack* cycle = NULL;
	int src = 0;
	dfs(graph, src, marked, edgeTo, onStack, cycle);
};

Graph* fetchGraph(){
	Graph* graph = createGraph(8,1);
	addEdge(graph, 0, 1);
	addEdge(graph, 1, 6);
	addEdge(graph, 6, 0);
	addEdge(graph, 1, 5);
	addEdge(graph, 5, 4);
	addEdge(graph, 4, 1);
	addEdge(graph, 6, 2);
	addEdge(graph, 2, 3);
	addEdge(graph, 3, 1);
	return graph;  
};

int main(){
	Graph* graph = fetchGraph();
	printGraph(graph);
	hasCycle(graph);
}