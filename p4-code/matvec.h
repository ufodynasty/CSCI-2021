#ifndef MATVEC_H
#define MATVEC_H 1

#include <stdio.h>

typedef struct {
  long rows;
  long cols;
  int *data;
} matrix_t;

typedef struct {
  long len;
  int *data;
} vector_t;

#define MGET(mat,i,j) ((mat).data[((i)*((mat).cols)) + (j)])
#define VGET(vec,i)   ((vec).data[(i)])

#define MSET(mat,i,j,x) ((mat).data[((i)*((mat).cols)) + (j)] = (x))
#define VSET(vec,i,x)   ((vec).data[(i)] = (x))


// matvec_util.c
int vector_init(vector_t *vec, long len);
int matrix_init(matrix_t *mat, long rows, long cols);
void vector_free_data(vector_t *vec);
void matrix_free_data(matrix_t *mat);
int vector_read_from_file(char *fname, vector_t *vec_ref);
int matrix_read_from_file(char *fname, matrix_t *mat_ref);
void vector_write(FILE *file, vector_t vec);
void matrix_write(FILE *file, matrix_t mat);
void vector_fill_sequential(vector_t vec);
void matrix_fill_sequential(matrix_t mat);

// sumdiag_base.c
int sumdiag_BASE(matrix_t mat, vector_t vec);

// sumdiag_optm.c
int sumdiag_OPTM(matrix_t mat, vector_t vec);

#endif
