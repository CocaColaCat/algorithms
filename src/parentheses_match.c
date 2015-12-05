#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;

typedef struct tagSNode{
	char value;
	struct tagSNode *pNext;
}SNode;

SNode* create(value){
	SNode *node = malloc(sizeof(SNode));
	node->value=value;
	node->pNext=NULL;
	return node;
}

bool match(char top, char key){
	if(top == '('){
		return ((key == ')') ? true : false);
	}else if(top == '{'){
		return ((key == '}') ? true : false);
	}else if(top == '['){
		return ((key == ']') ? true : false);
	}else{
		return false;
	}
}

void verify(char *str){
	int size = (unsigned int)strlen(str);
	printf("%i\n", size);
	SNode *head = create('&');
	SNode *cur = create(str[0]);
	head->pNext = cur;

	for(int i=1;i<size;i++){

		if(str[i] != cur->value){
			if(match(cur->value,str[i])){
				cur = NULL;
				cur = head;
			}else{
				cur->pNext = create(str[i]);
				cur = cur->pNext;
			}
		}else{
			cur->pNext = create(str[i]);
			cur = cur->pNext;
		}
	}
	if(cur->value == '&'){
		puts("match!");
	}else{
		puts("no match!");
	}
};

int main(){
	char str[] = "()(){}((({{[]";
	verify(str);
}