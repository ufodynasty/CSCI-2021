// struct_stride.c: Comparison of struct layouts and cache
// effects. Structs have their fields laid out sequentially in memory.
// This can create strides when visiting the same field in arrays of
// structs. For efficiency, one sometime sees structs where each field
// is an array of values which means all values are sequential.
//
// Complete the TODO items in this code so that it times each set of
// loops and prints output 

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {                // fields are individual ints
  int a;
  int b;
} int_field_t;

typedef struct {                // fields are arrays of ints
  int *a_arr;
  int *b_arr;
} arr_field_t;

// Use this format string for printf() invocations so that the output
// identical for each timing run
const char *FORMAT =
  "method: %14s CPU time: %.4e sec   sum: %d\n";
//          |             |               +-> sum computed in loop, should be 0 each time
//          |             +-> CPU time computed over nested summing loops
//          +-> string describing one of the methods used to print; 
//              One of: "int_field_base"  "arr_field_base" 
//                      "int_field_optm"  "arr_field_optm"
//
// Example: printf(FORMAT, "int_field_optm", some_time, total);

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <arr_length> <num_iters>\n",argv[0]);
    return 1;
  }
  int length = atoi(argv[1]);
  int max_iter = atoi(argv[2]);
  clock_t begin, end;           // Variables for timing
  double cpu_time;
  int suma,sumb;                // sum of elements in structs

  ////////////////////////////////////////////////////////////////////////////////
  // int_field_base approach
  int_field_t *int_field_arr1 =     // allocate/initialize int_field array
    malloc(sizeof(int_field_t)*length);
  for(int i=0; i<length; i++){
    int_field_arr1[i].a = +i;
    int_field_arr1[i].b = -i;
  }

  // TODO: START TIMING HERE
  begin = clock();

  suma=0, sumb=0;                  // initialize sum
  for(int iter=0; iter<max_iter; iter++){
    for(int i=0; i<length; i++){   // sum a fields
      suma += int_field_arr1[i].a;
    }
    for(int i=0; i<length; i++){   // sum b fields
      sumb += int_field_arr1[i].b;
    }
  }
  suma += sumb;
  // TODO: STOP TIMING HERE
  end = clock();

  // TODO: COMPUTE CPU TIME AND PRINT IT using the provided FORMAT string
  cpu_time = end-begin;
  printf(FORMAT, "int_field_base", cpu_time, suma);

  free(int_field_arr1);             // free memory

  ////////////////////////////////////////////////////////////////////////////////
  // arr_field_base approach

  arr_field_t arr_field1 = {        // allocate/initialize arr_field1 struct
    .a_arr = malloc(sizeof(int)*length),
    .b_arr = malloc(sizeof(int)*length)
  };
  for(int i=0; i<length; i++){
    arr_field1.a_arr[i] = +i;
    arr_field1.b_arr[i] = -i;
  }

  // TODO: START TIMING HERE
  begin = clock();

  suma=0, sumb=0;                  // initialize sum
  for(int iter=0; iter<max_iter; iter++){
    for(int i=0; i<length; i++){   // sum a fields
      suma += arr_field1.a_arr[i];
    }
    for(int i=0; i<length; i++){   // sum b fields
      sumb += arr_field1.b_arr[i];
    }
  }
  suma += sumb;
  end = clock();                   // get later moment to compare to start

  // TODO: STOP TIMING HERE

  // TODO: COMPUTE CPU TIME AND PRINT IT using the provided FORMAT string
  cpu_time = end-begin;
  printf(FORMAT, "arr_field_base", cpu_time, suma);

  free(arr_field1.a_arr);           // free memory
  free(arr_field1.b_arr);

  ////////////////////////////////////////////////////////////////////////////////
  // int_field_optm OPTIMIZED approach

  int_field_t *int_field_arr2 =     // allocate/initialize int_field array
    malloc(sizeof(int_field_t)*length);
  for(int i=0; i<length; i++){
    int_field_arr2[i].a = +i;
    int_field_arr2[i].b = -i;
  }

  // TODO: START TIMING HERE
  begin = clock();

  suma=0, sumb=0;                  // initialize sum
  for(int iter=0; iter<max_iter; iter++){
    for(int i=0; i<length; i++){   // sum both fields
      suma += int_field_arr2[i].a;
      sumb += int_field_arr2[i].b;
    }
  }
  suma += sumb;

  // TODO: STOP TIMING HERE
  end = clock();

  // TODO: COMPUTE CPU TIME AND PRINT IT using the provided FORMAT string
  cpu_time = end-begin;
  printf(FORMAT, "int_field_optm", cpu_time, suma);

  free(int_field_arr2);             // free memory

  ////////////////////////////////////////////////////////////////////////////////
  // arr_field_opt OPTIMIZED approach

  arr_field_t arr_field2 = {        // allocate/initialize arr_field2 struct
    .a_arr = malloc(sizeof(int)*length),
    .b_arr = malloc(sizeof(int)*length)
  };
  for(int i=0; i<length; i++){
    arr_field2.a_arr[i] = +i;
    arr_field2.b_arr[i] = -i;
  }

  // TODO: START TIMING HERE
  begin = clock();

  suma=0, sumb=0;                  // initialize sum
  for(int iter=0; iter<max_iter; iter++){
    for(int i=0; i<length; i++){   // sum both fields
      suma += arr_field2.a_arr[i];
      sumb += arr_field2.b_arr[i];
    }
  }
  suma += sumb;

  // TODO: STOP TIMING HERE
  end = clock();

  // TODO: COMPUTE CPU TIME AND PRINT IT using the provided FORMAT string
  cpu_time = end-begin;
  printf(FORMAT, "arr_field_optm", cpu_time, suma);

  free(arr_field2.a_arr);           // free memory
  free(arr_field2.b_arr);

  return 0;
}
