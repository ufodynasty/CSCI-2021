#include <stdio.h>
#include <stdlib.h>
#include "coins.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <cents>\n",argv[0]);
    printf(" <cents> : integer from 0 to 99\n");
    return 1;
  }

  int cents = atoi(argv[1]);
  coins_t coins;
  int ret = set_coins(cents, &coins);
  if(ret){
    printf("Invalid cents %d: must be between 0 and 99\n",
           cents);
    return 1;
  }
  printf("%d cents is...\n" ,cents);
  printf("%d quarters\n"    ,coins.quarters);
  printf("%d dimes\n"       ,coins.dimes);
  printf("%d nickels\n"     ,coins.nickels);
  printf("%d pennies\n"     ,coins.pennies);

  int tot = total_coins(coins);
  printf("which is %d cents\n",tot);

  return 0;
}
