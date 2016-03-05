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

  for(int x=0;x<(ptn_size+1);x++)
    printf("%i ",tb[x]);
  printf("\n");
  // for(int x=0;x<str_size;x++)
  //   printf("%c ", str[x]);
  // printf("\n");

  while(i<str_size){
    while(j>=0 && (str[i] != ptn[j])){
      // for(int x=0;x<i;x++)
      //   printf("%c", str[x]);
      // printf("\n");

      // for(int x=0;x<i;x++)
      //   printf("%i ",i);
      // for(int x=0;x<j;x++)
      //   printf("%c", ptn[x]);
      // printf("\n");

      // printf("str is %c, ptn is %c\n", str[i], ptn[j]);
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
// https://www.youtube.com/watch?v=KG44VoDtsAA
int main(){
  char str[] = "abxabyabmabxabyabzababc";
  char ptn[] = "acacabacacabacacacac";

  kmp(ptn, str);
  return 1;
}
