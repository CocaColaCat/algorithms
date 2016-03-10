#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lengthOfLIS(int *nums, int size){
	int max[size+1];
	max[1] = nums[0];
	max[0] = 2;
	int lis[size];

	for(int i =0;i<size;i++)
		lis[i] = 1;

	int maxLen =1;

	for(int i =0;i<size;i++){
		int j;
		for(j=maxLen;j>=0;j--){
			if(nums[i]>max[j]){
				lis[i] =j+1;
				break;
			}
		}
		printf("j is %i, maxLen is %i\n", j, maxLen);

		if(lis[i]>maxLen){
			maxLen=lis[i];
			max[lis[i]] = nums[i];
		}else if(max[j]<A[i] && (nums[i]<max[j+1])){
			max[j+i] = nums[i];
		}
	}
	return maxLen;
}

int main(){
	int nums[] = { 10, 9, 2, 5, 3, 7, 101, 18 };
	int size = sizeof(nums)/sizeof(int);
	
	int length = lengthOfLIS(nums, size);
	printf("length is %i\n", length);
	return 1;
}