#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct tagSNode{
	int value;
	struct tagSNode *pNext;
}SNode;

SNode* add(SNode *pHead1, SNode *pHead2){
	SNode *head1 = pHead1->pNext;
	SNode *head2 = pHead2->pNext;
	SNode *pSum = malloc(sizeof(SNode));
	SNode *pTail = pSum;
	SNode *pCur;
	int curry = 0;
	int sum;
	int v;

	while(head2 && head1){
		sum = head1->value + head2->value + curry;
		curry = sum/10;
		v = sum%10;
		pCur = malloc(sizeof(SNode));
		pCur->value = v;
		pTail->pNext = pCur;
		pTail = pCur;
		head1 = head1->pNext;
		head2 = head2->pNext;
	}

	SNode *h = (head1==NULL) ? head2 : head1;

	while(h!=NULL){
		sum = h->value+curry;
		curry = sum/10;
		v = sum%10;
		pCur = malloc(sizeof(SNode));
		pCur->value = v;
		pTail->pNext = pCur;
		pTail = pCur;
		h = h->pNext;
	}

	if(curry!=0){
		pCur = malloc(sizeof(SNode));
		pCur->value = curry;
		pTail->pNext = pCur;
	}
	return pSum;
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	SNode *pHead1 = malloc(sizeof(SNode));
	pHead1->value = 0;
	pHead1->pNext = NULL;
	SNode *pHead2 = malloc(sizeof(SNode));
	pHead2->value = 0;
	pHead2->pNext = NULL;
	puts("First list is:");
	for(int i = 0; i<4; i++){
		SNode *node = malloc(sizeof(SNode));
		node->value = rand()%10;
		node->pNext = pHead1->pNext;
		pHead1->pNext = node;
		printf("%i", node->value);
	};
	puts("\nSecond list is:");
	for(int i = 0; i<7; i++){
		SNode *node = malloc(sizeof(SNode));
		node->value = rand()%10;
		node->pNext = pHead2->pNext;
		pHead2->pNext = node;
		printf("%i", node->value);
	};
	puts("\nStart add");
	SNode *pSum = add(pHead1,pHead2);
	
	puts("Sum is:");
	SNode *sum = pSum->pNext;
	while(sum){
		printf("%i", sum->value);
		sum = sum->pNext;
	}
	puts("\nDone");
	return 0;
}