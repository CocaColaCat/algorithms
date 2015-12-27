#include <stdlib.h>
#include <stdio.h>

// quick find implementation

typedef enum { false, true } bool;

typedef struct UnionSet{
	int* data;
	int count;
	int size;
}UnionSet;

UnionSet* initUnionSet(int eleCount){
	UnionSet* set = malloc(sizeof(UnionSet));
	set->count = eleCount;
	set->size = eleCount;
	set->data = malloc(sizeof(eleCount));
	for(int i =0; i< eleCount; i++){
		set->data[i] = i;
	}
	return set;
};

int find(UnionSet* set, int p){
	return set->data[p];
};

void doUnion(UnionSet* set, int p, int q){
	int pId = find(set, p);
	int qId = find(set, q);
	if(pId == qId)
		return;
	for(int i = 0; i< set->size; i++){
		if(set->data[i] == pId){
			set->data[i] = qId;
		}
	}
	set->count = set->count - 1;
};

bool connected(UnionSet* set, int p, int q){
	printf("p is %i and top is %i, q is %i and top is %i\n",p, set->data[p], q, set->data[q]);
	return ((find(set, p) == find(set, q)) ? true : false);
};

void unionFind(UnionSet* set, int p, int q){
	if(connected(set, p, q)){
		printf("p %i and q %i is connected\n", p, q);
		return;
	}else{
		doUnion(set, p, q);
	}
};

int main(){
	int count = 10;
	UnionSet* set = initUnionSet(count);
	unionFind(set,4,3);
	unionFind(set,3,8);
	unionFind(set,6,5);
	unionFind(set,9,4);
	unionFind(set,2,1);
	unionFind(set,8,9);
	unionFind(set,5,0);
	unionFind(set,7,2);
	unionFind(set,6,1);
	unionFind(set,1,0);
	unionFind(set,6,7);
	printf("components count is %i\n", set->count);
	return 1;
}