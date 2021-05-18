// Complete this main to benchmark the search algorithms outlined in
// the project specification
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "search.h"
int main(int argc, char *argv[]){
  if(argc<4) {
    printf("usage: ./search_benchmark <minpow> <maxpow> <repeats> [which]\nwhich is a combination of:\na : Linear Array Search\nl : Linked List Search\nb : Binary Array Search\nt : Binary Tree Search\n(default all)"); 
  }
  int min_pow = atoi(argv[1]);
  int max_pow = atoi(argv[2]);
  int repeats = atoi(argv[3]);
  int run_array = 0;
  int run_list = 0;
  int run_binary = 0;
  int run_tree = 0;
  if(argc > 4) {
    char *tests = argv[4];
    int i = 0;
    while(tests[i]!='\0') {
      if(tests[i]=='a') {
        run_array = 1;
      }
      if(tests[i]=='l') {
        run_list = 1;
      }
      if(tests[i]=='b') {
        run_binary = 1;
      }
      if(tests[i]=='t') {
        run_tree = 1;
      }
      i++;
    }
  } else {
    run_array = 1;
    run_list = 1;
    run_binary = 1;
    run_tree = 1;
  }
  printf("LENGTH SEARCHES");
  if(run_array) {
    printf("      array");
  }
  if(run_list) {
    printf("       list");
  }
  if(run_binary) {
    printf("     binary");
  }
  if(run_tree) {
    printf("       tree");
  }
  printf("\n");
  int length = 1;
  for(int i = 0; i < min_pow; i++) {
    length = length * 2;
  }
  int *array;
  list_t *list;
  bst_t *bst;
  double array_time,list_time,binary_time,tree_time;
  clock_t begin, end;
  for(int i = min_pow;i<=max_pow;i++) {
    printf("%6d %8d",length,2*length*repeats);
    if(run_array || run_binary) {
      array = make_evens_array(length);
    }
    if(run_list) {
      list = make_evens_list(length);
    }
    if(run_tree) {
      bst = make_evens_tree(length);
    }
    if(run_array) {
      begin = clock();
      for(int i=0; i < repeats; i++) {
        for(int i = 0; i < 2*length; i++) {
          linear_array_search(array,length,i);
        }
      }
      end = clock();
      array_time = end - begin;
      printf(" %.4e",array_time);
    }
    if(run_list) {
      begin = clock();
      for(int i=0; i < repeats; i++) {
        for(int i = 0; i < 2*length; i++) {
          linkedlist_search(list,length,i);
        }
      }
      end = clock();
      list_time = end - begin;
      printf(" %.4e",list_time);
    }
    if(run_binary) {
      begin = clock();
      for(int i=0; i < repeats; i++) {
        for(int i = 0; i < 2*length; i++) {
          binary_array_search(array,length,i);
        }
      }
      end = clock();
      binary_time = end - begin;
      printf(" %.4e",binary_time);
    }
    if(run_tree) {
      begin = clock();
      for(int i=0; i < repeats; i++) {
        for(int i = 0; i < 2*length; i++) {
          binary_tree_search(bst,0,i);
        }
      }
      end = clock();
      tree_time = end - begin;
      printf(" %.4e",tree_time);
    }
    if(run_array || run_binary) {
      free(array);
    }
    if(run_list) {
      list_free(list);
    }
    if(run_tree) {
      bst_free(bst);
    }
    printf("\n"); 
    length = length * 2;
  }
  return 0;
}
