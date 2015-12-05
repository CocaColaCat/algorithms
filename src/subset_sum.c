#include <stdio.h>

typedef enum { false, true } bool;

int a[] = {1,2,3,4,5};
int size = sizeof(a)/sizeof(int);
int sum = 10;

void EnumNumber(bool *x, int i, int has){
	int y = i;
	while(y>=1){
		printf("%s", "-");
		y--;
	}
	printf("current index is %i\n", i);
	if(i>=size){
		return;
	}
	if(has+a[i]==sum){
		x[i] = true;
		int k = i;
		while(k>=0){
			if(x[k]==true){
				printf("%i-", a[k]);
			}
			k--;
		}
		puts("\n");
	}
	x[i] = true;
	EnumNumber(x,i+1, has+a[i]);
	x[i] = false;
	EnumNumber(x,i+1, has);
}

int main(){
	bool arr[5] = {};
	EnumNumber(arr, 0, 0);
}