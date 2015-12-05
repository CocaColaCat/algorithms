#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct tagSNode{
	int value;
	struct tagSNode *pNext;
}SNode;

SNode* create(value){
	SNode *node = malloc(sizeof(SNode));
	node->value=value;
	node->pNext=NULL;
	return node;
}

void print(SNode *list){
	while(list){
		printf("%i\n", list->value);
		list = list->pNext;
	}
}

void split(SNode *list, int size, int v){
	SNode *p = list->pNext;
	SNode *leftHead = create(0);
	SNode *rightHead = create(0);

	SNode *left = leftHead;
	SNode *right = rightHead;

	while(p!=NULL){
		if(p->value > v){
			right->pNext=p;
			right = p;
		}else{
			left->pNext=p;
			left=p;	
		}
		p=p->pNext;
	}
		left->pNext = rightHead->pNext;
		right->pNext=NULL;
		list->pNext=leftHead->pNext;
}

int main(){
	SNode *list = create(0);
	SNode *node1 = create(1);
	SNode *node2 = create(5);
	SNode *node3 = create(7);
	SNode *node4 = create(8);
	SNode *node5 = create(2);
	SNode *node6 = create(9);
	list->pNext = node1;
	node1->pNext = node2;
	node2->pNext = node3;
	node3->pNext = node4;
	node4->pNext = node5;
	node5->pNext = node6;

	int v = 4;
	print(list);
	split(list, 7, 4);
	puts("after reorder");
	print(list);
	return 0;
}