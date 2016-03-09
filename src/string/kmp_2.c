#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void partialMatchTable(char *ptn, int ptn_size, int *tb){
  int i = 0;
  int j = -1;
  tb[i] = j;
  while(i<=ptn_size){
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
  printf("partial table is: \n");
  for(int i=0;i<=ptn_size;i++)
    printf("%c ", ptn[i]);
  printf("\n");
  for(int i=0;i<=ptn_size;i++)
    printf("%i ", tb[i]);
  printf("\n");

  int str_size = (unsigned int)strlen(str);
  int j=0;
  int i=0;
  while(i<str_size){
    printf("i is %i, j is %i, str char is %c, ptn char is %c\n",i,j,str[i],ptn[j]);
    while(j>=0 && (ptn[j] != str[i])){
      j = tb[j];
      printf("unmatch found,");
      printf("i is %i, j is %i, str char is %c, ptn char is %c\n",i,j,str[i],ptn[j]);
    }
    i=i+1;
    j=j+1;
    if(j==ptn_size){
      printf("pattern match found at %i\n", i-ptn_size);
      j = tb[j];
    }
  }
}

int main(){
  char ptn[] = "abacxabacy";
  char str[] = "abacxabaczabacxabacyabacxa";

  kmp(ptn, str);

  return 1;
}
