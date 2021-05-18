// baseline version
#include "matvec.h"
int sumdiag_BASE_NORMAL(matrix_t mat, vector_t vec) {
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  for(int i=0; i<vec.len; i++){                   // initialize vector of diagonal sums
    VSET(vec,i,0);                                // to all 0s
  }

  for(int d=0; d < mat.rows; d++){                // iterate over lower diagonals
    int c = 0;                                    // col always starts at 0 in lower diags
    for(int r=mat.rows-d-1; r<mat.rows; r++,c++){ // work down rows, right cols for same diag
      int el_rc = MGET(mat, r, c);                // get matrix element on diagonal
      int vec_d = VGET(vec, d);                   // retrieve current sum for diag
      VSET(vec, d, el_rc+vec_d);                  // add on back to the diagonal sum
    }
  }

  int maxdiag = (mat.rows+mat.cols)-1;            // calculate last diagonal
  for(int d=mat.rows; d < maxdiag ; d++){         // iterate starting at first upper diag
    int r = 0;                                    // row always starts at 0 in upper diags
    for(int c=d-mat.cols+1; c<mat.cols; r++,c++){ // work down rows, right cols for same diag
      int el_rc = MGET(mat, r, c);                // matrix element
      int vec_d = VGET(vec, d);                   // diagonal sum from vector
      VSET(vec, d, el_rc+vec_d);                  // add on to sum
    }
  }
  return 0;                                       // return success
}

int sumdiag_BASE_DBG(matrix_t mat, vector_t vec)
{
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  for(int i=0; i<vec.len; i++){
    VSET(vec,i,0);
  }
  // first sum lower diagonals
  for(int d=0; d < mat.rows; d++){
    int c = 0;                            // col always starts at 0 in lower diags
    for(int r=mat.rows-d-1; r<mat.rows; r++,c++){ // work down rows, right cols for same diag
      int el_rc = MGET(mat, r, c);
      int vec_d = VGET(vec, d);
      printf("adding [%d,%d]=%d to diag[%d]=%d\n",
             r,c,el_rc,d,vec_d);
      VSET(vec, d, el_rc+vec_d);
    }
  }
  // second sum upper diagonals
  for(int d=mat.rows; d < (mat.rows+mat.cols)-1; d++){
    int r = 0;                            // row always starts at 0 in upper diags
    for(int c=d-mat.cols+1; c<mat.cols; r++,c++){ // work down rows, right cols for same diag
      int el_rc = MGET(mat, r, c);
      int vec_d = VGET(vec, d);
      printf("adding [%d,%d]=%d to diag[%d]=%d\n",
             r,c,el_rc,d,vec_d);
      VSET(vec, d, el_rc+vec_d);
    }
  }


  return 0;
}

int sumdiag_BASE(matrix_t mat, vector_t vec){
  return sumdiag_BASE_NORMAL(mat, vec);
}

