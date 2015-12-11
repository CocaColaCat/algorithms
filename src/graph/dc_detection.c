#include <stdio.h>
#include <stdlib.h>
#include "general_graph.c"
#include "../data_structure/stack.c"

Stack* cycle = NULL; // 定义全局变量，这样 cycle 指针不会在 recursive 结束的时候被回收

void dfs(Graph* graph, int src, bool* visited, int* edgeTo, bool* onStack){
	visited[src] = true;
	onStack[src] = true;
	AdjListNode* adjListNode = graph->array[src].head;
	while(adjListNode){
		if(cycle){
			return;
		}else if(!visited[adjListNode->dest]){
			// 如果当前的邻居是第一次到达，则建立 src 和 邻居之间的关联, 同时对邻居开始做 recusive
			edgeTo[adjListNode->dest] = src;
			dfs(graph, adjListNode->dest, visited, edgeTo, onStack);
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
	bool* visited = malloc(V*(sizeof(bool)));
	for(int i=0;i<V;i++){
		visited[i] = false;
	}
	return visited;
}

void hasCycle(Graph* graph){
  // createBooleanArray 创建 V 个元素的 boolean 数组，V = 图中点个数
  bool* visited = createBooleanArray(graph->V);
  int* edgeTo = malloc(graph->V*(sizeof(int)));
  bool* onStack = createBooleanArray(graph->V);
  for(int i =0; i< graph->V; i++)
  	dfs(graph, i, visited, edgeTo, onStack);
};

Graph* fetchGraph(){
	Graph* graph = createGraph(8,1);
	addEdge(graph, 0, 1);
	addEdge(graph, 1, 6);
	addEdge(graph, 6, 0);
	addEdge(graph, 1, 5);
	addEdge(graph, 5, 4);
	addEdge(graph, 4, 1);
	addEdge(graph, 7, 3);
	addEdge(graph, 3, 2);
	addEdge(graph, 2, 7);
	return graph;  
};

int main(){
	Graph* graph = fetchGraph();
	// printGraph(graph);
	hasCycle(graph);
}