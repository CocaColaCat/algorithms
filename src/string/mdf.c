#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int R = 26;

char charAt(char str[], int d){
	int s_l = strlen(str);
	// printf("size is %i\n", s_l);
	if(s_l>d){
		return str[d];
	}else{
		return -1;
	}
};

void sort(char *strs[], int lo, int hi, int d){
	int count[R+2] = {0};
	printf("current stack\n");

	// count frequency
	for(int i=lo; i<=hi; i++){
		char c = charAt(strs[i], d);
		printf("char is %c\n", c);
		count[c+1] += 1;
	}

	sort(strs, lo, hi, d+1);

	// for(int i=0;i<R+1;i++){
	// 	count[i+1] =
	// }


};

int main(){
	// in order to implement most significant digit sort, i need to have a set of test data.
	// so given an array of strings, pass to the sort method as arg, then return the sorted array
	// the most significant digit sort sorts the string from left to right. the first left digit first.
	// sort the array to group by digit. then sort the sub array of strings and so on.
	// until reach the end.
	int L = 13;
	char *strs[] = { "she", "sells", "seashells", "by", "the", "seashore", 
		"the", "shells", "she", "sells", "are", "surely", "seashells"};

	sort(strs, 0, L-1, 0);
}