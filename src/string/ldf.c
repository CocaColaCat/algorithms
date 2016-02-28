#include <stdlib.h>
#include <stdio.h>

const int R = 256;

void ldf(char *strs[], int N, int W){

	for(int x=(W-1); x >= 0; x--){
		int count[R+1] = {0};
		char *aux[N];

		for(int n=0; n<N ; n++){
			printf("digit is %c\n", strs[n][x]);
			count[strs[n][x]+1] += 1;
		}

		for(int k=0;k<R;k++){
			count[k+1] += count[k];
		}

		for(int n=0; n<N; n++){
			aux[count[strs[n][x]]] = strs[n];
			count[strs[n][x]] += 1;
		}

		for(int n=0;n<N;n++){
			strs[n] = aux[n];
			printf("%s\n",aux[n]);
		}
	}
}

int main(){
	const int L = 13;
	char *strs[L] = { "4PGC938", "2IYE230", "3CIO720", "1ICK750", "1OHV845", "4JZY524",
		"1ICK750", "3CIO720", "1OHV845", "1OHV845", "2RLA629", "2RLA629", "3ATW723" };

	ldf(strs, L, 7);
}
