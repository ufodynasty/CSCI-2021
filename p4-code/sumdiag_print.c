#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "matvec.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <size>\n",argv[0]);
    exit(1);
  }

  printf("==== Matrix Diagonal Sum Print ====\n");
  long size = atoi(argv[1]);
  long rows=size, cols=size;
  matrix_t mat;
  vector_t res_BASE, res_OPTM;
  matrix_init(&mat,rows,cols);
  matrix_fill_sequential(mat);

  printf("Matrix:\n");
  matrix_write(stdout, mat);
  printf("\n");

  vector_init(&res_BASE, 2*size-1);
  vector_init(&res_OPTM, 2*size-1);
  
  sumdiag_BASE(mat,res_BASE);
  sumdiag_OPTM(mat,res_OPTM);

  printf("Diagnonal Sums:\n");
  printf("[ i]: BASE OPTM\n");
  for(int i=0; i<res_BASE.len; i++){
    int b = VGET(res_BASE,i);
    int o = VGET(res_OPTM,i);
    char *diff = (b != o) ? "***" : "";
    printf("[%2d]: %4d %4d %s\n",i,b,o,diff);
  }
    
  matrix_free_data(&mat);       // clean up data
  vector_free_data(&res_BASE);
  vector_free_data(&res_OPTM);
  return 0;
}
