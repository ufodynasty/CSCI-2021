#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "matvec.h"

double total_points = 0;
double actual_score = 0;

#include "data.c"

void check_hostname();

#define NSIZES 7
int nsizes = NSIZES;
int REPEATS = 3;

int main(int argc, char *argv[]){
  check_hostname();

  printf("==== Matrix Diagonal Sum Benchmark Version 2 ====\n");
  printf("------ Tuned for csel-kh1250-NN machines --------\n");

  int sizes[NSIZES] = {
      512,
     1024,
     1101,
     2048,
     4099,
     6001, 
     8191,
  };

  if(argc > 1 && strcmp(argv[1],"-test")==0){
    nsizes = 3;                 // for valgrind testing
  }

  printf("%6s ","SIZE");
  printf("%10s ","BASE");
  printf("%10s ","OPTM");
  printf("%6s ", "SPDUP");
  printf("%6s ", "POINTS");
  printf("\n");

  // Iterate over different sizes of the matrix
  for(int i=0; i<nsizes; i++){
    long size = sizes[i];
    long rows=size, cols=size;

    matrix_t mat;
    vector_t res_BASE, res_OPTM;
    int ret = matrix_init(&mat,rows,cols);
    if(ret){ return ret; }
    matrix_fill_sequential(mat);

    ret = vector_init(&res_BASE, 2*size-1);
    ret = vector_init(&res_OPTM, 2*size-1);
    vector_fill_sequential(res_BASE); // fill with random data, need to zero in routines
    vector_fill_sequential(res_OPTM);

    clock_t begin, end;
    begin = clock();
    for(int i=0; i<REPEATS; i++){
      ret = sumdiag_BASE(mat,res_BASE);
    }
    end = clock();
    double cpu_time_BASE = ((double) (end - begin)) / CLOCKS_PER_SEC;

    begin = clock();
    for(int i=0; i<REPEATS; i++){
      ret = sumdiag_OPTM(mat,res_OPTM);
    }
    end = clock();
    double cpu_time_OPTM = ((double) (end - begin)) / CLOCKS_PER_SEC;

    double speedup_OPTM = (cpu_time_BASE / cpu_time_OPTM);

    double points = speedup_OPTM - 1.0;     // speedup of 1.0 is no speedup at all
    points = points > 0.0 ? points : 0.0;   // no negative point values: min 0.0

    for(int i=0; i<res_BASE.len; i++){
      int base_i = VGET(res_BASE,i);
      int opt_i  = VGET(res_OPTM,i);
      if(base_i != opt_i){
        printf("ERROR: base and opt multiplication produced different results\n");
        printf("ERROR: res[%d]: %d != %d\n",i,base_i,opt_i);
        printf("ERROR: Skipping checks on remaining elements\n");
        printf("ERROR: Try running the 'sumdiag_print <size>' program to see differences\n");
        speedup_OPTM = -1.0;
        points = 0;
        break;
      }
    }

    total_points += points;


    printf("%6ld ", size);
    printf("%10.4e ",cpu_time_BASE);
    printf("%10.4e ",cpu_time_OPTM);
    printf("%6.2f ", speedup_OPTM);
    printf("%6.2f ",  points);
    printf("\n");

    matrix_free_data(&mat);       // clean up data
    vector_free_data(&res_BASE);
    vector_free_data(&res_OPTM);
  }

  double max_score = 35.0;
  actual_score = total_points;
  printf("RAW POINTS: %.2f\n",actual_score);

  if(actual_score > max_score){
    actual_score = max_score;
    final_check();
  }

  printf("TOTAL POINTS: %.0f / %.0f\n",actual_score,max_score);

  check_hostname();

  return 0;
}
  
#define MAXHOSTNAMELEN 1024
#define EXPECT_HOST "csel-kh1250"
#define FULL_EXPECT_HOST "csel-kh1250-NN"

void check_hostname(){
  char actual_host[MAXHOSTNAMELEN];
  if (gethostname(actual_host, MAXHOSTNAMELEN) != 0) {
    printf("WARNING: Couldn't get machine hostname\n");
  }
  else if(strncmp(EXPECT_HOST, actual_host, strlen(EXPECT_HOST)) != 0){
    printf("WARNING: expected host '%s' but got host '%s'\n",FULL_EXPECT_HOST,actual_host);
    printf("WARNING: timing results / scoring will not reflect actual scoring\n");
    printf("WARNING: run on host '%s' for accurate results\n",FULL_EXPECT_HOST);
  }    
}
