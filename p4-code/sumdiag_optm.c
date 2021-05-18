// optimized versions of matrix diagonal summing
#include "matvec.h"

// You can write several different versions of your optimized function
// in this file and call one of them in the last function.

int sumdiag_VER1(matrix_t mat, vector_t vec) {
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  for(int i=0; i<vec.len; i++){                   // initialize vector of diagonal sums
    VSET(vec,i,0);                                // to all 0s
  }
  for(int r = 0; r<mat.rows; r++) {
    for(int c = 0; c<mat.cols; c++) {
      int d = c-r+mat.cols-1;
      int new_total = VGET(vec,d) + MGET(mat,r,c);
      VSET(vec,d,new_total);
    }
  }
  return 0;
}

int sumdiag_VER2(matrix_t mat, vector_t vec) {
  // OPTIMIZED CODE HERE
  return 0;
}

int sumdiag_OPTM(matrix_t mat, vector_t vec) {
  // call your preferred version of the function
  return sumdiag_VER1(mat, vec);
}
