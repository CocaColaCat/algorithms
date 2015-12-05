#include <stdlib.h>
#include <stdio.h>

#define STACK_MAX 100
typedef enum { false, true } bool;

typedef struct Stack{
	int data[STACK_MAX];
	int size;
}Stack;

void StackInit(Stack *s){
	s->size = 0;
}

Stack* StackCreate(){
	Stack *s = malloc(sizeof(Stack));
	StackInit(s);
	return s;
}

int StackTop(Stack *s){
	if(s->size==0){
		puts("--- stack empty ---");
		return -1;
	}else{
		return s->data[s->size-1];
	}
}

void StackPush(Stack *s, int v){
	if(s->size >= STACK_MAX){
		puts("--- stack full ---");
	}else{
		s->size = s->size+1;
		s->data[s->size-1] = v;
	}
}

void StackPop(Stack *s){
	if(s->size==0){
		puts("--- stack empty ---");
	}else{
		s->size = s->size-1;
	}
}

bool IsEmpty(Stack *s){
	return ((s->size==0) ? true : false);
}