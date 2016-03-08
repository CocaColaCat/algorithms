#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int *lis,int size){
	int i =0;
	int max=1;
	while(i<size){
		if(lis[i]>max)
			max = lis[i];
		i = i+1;
	}
	return max;
}

int lengthOfLIS(int *nums, int size){
	int lis[size];
	for(int i =0;i<size;i++){
		lis[i] = 1;
		for(int j=0;j<i;j++){
			printf("i is %i, j is %i, value is %i, value is %i\n", i, j, nums[i], nums[j]);
			if((nums[i]>nums[j]) && (lis[j]+1>lis[i])){
				printf("increase length\n");
				lis[i] = lis[j]+1;
			}
		}
	}
	return max(lis,size);	
}

int main(){
	int nums[] = { 10, 9, 2, 5, 3, 7, 101, 18 };
	int size = sizeof(nums)/sizeof(int);
	
	int length = lengthOfLIS(nums, size);
	printf("length is %i\n", length);
	return 1;
}