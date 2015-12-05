#include <stdlib.h>
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

void rotate(SNode *pHead, int m, int n){
	SNode *pCur = pHead->pNext;
	int i = 0;
	for(;i<m-1;i++){
		printf("index is%i\n", i);
		pHead = pCur;
		pCur = pCur->pNext;
	}

	SNode *pPre = pCur;
	pCur = pCur->pNext;

	n--;
	SNode *pNext;
	for(;i<n;i++){
		pNext = pCur->pNext;
		pCur->pNext = pHead->pNext;
		pHead->pNext = pCur;
		pPre->pNext=pNext;
		pCur=pNext;
	}
}

// given 1→2→3→4→5, m=2,n=4, return 1→4→3→2→5
int main(){
	int m = 3;
	int n = 6;

	SNode *list = create(0);
	SNode *tail = list;
	for(int i=1;i<9;i++){
		tail->pNext = create(i);
		tail = tail->pNext;		
	}

	print(list);
	rotate(list,m,n);
	print(list);
}