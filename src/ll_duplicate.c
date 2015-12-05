#include <stdlib.h>
#include <stdio.h>

typedef enum { false, true } bool;

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

void remove_duplicate(SNode *list){
	SNode *cur = list->pNext;
	while(cur!=NULL){
		SNode *next = cur->pNext;
		if((next!=NULL) && (cur->value == next->value)){
			cur->pNext = next->pNext;
		}else{
			cur=next;
		}
	}
}

void remove_duplicate_2(SNode *list){
	SNode *pPre = list;
	SNode *pCur = pPre->pNext;
	SNode *pNext;
	bool bDup;
	while(pCur){
		pNext = pCur->pNext;
		bDup=false;
		while(pNext && (pCur->value==pNext->value)){
			pPre->pNext=pNext;
			delete pCur;
			pCur = pNext;
			pNext=pCur->pNext;
			bDup=true;
		}
		if (bDup)
		{
			pPre->pNext=pNext;
			delete pCur;
		}else{
			pPre = pCur;
		}
		pCur = pNext;
	}
}

int main(){
	int value[] = {1,2,2,4,8,9,3,3,3};
	int size = sizeof(value)/sizeof(int);
	SNode *list = create(0);
	SNode *head = list;

	for(int i=0;i<size;i++){
		SNode *node = create(value[i]);
		head->pNext = node;
		head = node;
	}

  puts("before remove");
	print(list);
	remove_duplicate_2(list);
  puts("after remove");
	print(list);
}