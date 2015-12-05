#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.c"

int max(int x, int y){
	return ((x>y) ? x : y);
}

int findLongestValidP(char *str){
	int start = -1;
	int size = strlen(str);
	int ml = 0;
	Stack *s = StackCreate();

	for(int i=0;i<size;i++){
		if(str[i] == '('){
			StackPush(s, i); // 左括号，压栈，存当前括号的 index
		}else{ // 右括号
			if(IsEmpty(s)){ // 当前空栈，把起始位置设为 i
				start = i;
			}else{
				StackPop(s); // 压栈
				if(IsEmpty(s)){ // 栈为空，ml 是当前位置减去起始的 index
					ml = max(ml, (i-start));
				}else{ // 栈不为空，则最长为当前位置减去栈中保存的上一个做括号的 index
					ml = max(ml, (i-StackTop(s)));
				}
			}
		}
	}
	return ml;
}

int main(){
	char str[] = "()(())(";
	int ml = findLongestValidP(str);
	printf("the longest valid parentheses is %i\n", ml);
	return -1;
}