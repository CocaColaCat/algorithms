#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c){
	return ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)));
}

int levenshtein(char *s1, char *s2){
  unsigned int x, y, s1len, s2len;
  s1len = strlen(s1);
  s2len = strlen(s2);
  unsigned int matrix[s2len+1][s1len+1];

  matrix[0][0] = 0;
  for (x = 1; x <= s2len; x++)
      matrix[x][0] = matrix[x-1][0] + 1;
  for (y = 1; y <= s1len; y++)
      matrix[0][y] = matrix[0][y-1] + 1;
  for (x = 1; x <= s2len; x++)
      for (y = 1; y <= s1len; y++)
          matrix[x][y] = min3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
  return(matrix[s2len][s1len]);
}

int main(){
	char src[] = "exception";
	char trgt[] = "intention";
	int distance = levenshtein(src,trgt);
	printf("distance is %i\n", distance);
	return 1;
}