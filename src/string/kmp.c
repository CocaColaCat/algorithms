#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void partialMatchTable(char *ptn, int ptn_size, int *tb){
  int i = 0;
  int j = -1;
  tb[i] = j;
  while(i<ptn_size){
    while(j>=0 && (ptn[i] != ptn[j])){
      j = tb[j];
    }
    i = i+1;
    j = j+1;
    // printf("i is %i, j is %i\n",i,j );
    tb[i] = j;
  }
}

void kmp(char *ptn, char *str){
  int ptn_size = (unsigned int)strlen(ptn);
  int tb[ptn_size+1];
  partialMatchTable(ptn, ptn_size, tb);

  int str_size = (unsigned int)(strlen)(str);
  int i = 0;
  int j = 0;
  while(i<str_size){
    while(j>=0 && (str[i] != ptn[j])){
      j = tb[j];
    }
    i = i+1;
    j = j+1;
    if(j==ptn_size){
      printf("pattern match at index %i\n", i-ptn_size);
      j = tb[j];
    }
  }

}

// http://tekmarathon.com/2013/05/14/algorithm-to-find-substring-in-a-string-kmp-algorithm/
int main(){
  char ptn[] = "abcabdabc";
  char str[] = "abcabdabckfkksehflaejfabcab.sds.dkdabcjflafjabcabdabcdasf;ksfk";

  kmp(ptn, str);
  return 1;
}
