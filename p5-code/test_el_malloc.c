// el_malloc.c test program
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include "el_malloc.h"

#define HEAP_SIZE 1024

#define PRINT_TEST sprintf(sysbuf,"awk 'NR==(%d+1){P=1;print \"{\"} P==1 && /ENDTEST/{P=0; print \"}\"} P==1{print}' %s", __LINE__, __FILE__); \
                   system(sysbuf);

void print_ptr(char *str, void *ptr){
  if(ptr == NULL){
    printf("%s: (nil)\n", str);
  }
  else{
    printf("%s: %p\n", str, ptr);
  }
}
void print_ptrs(void *ptr[], int len){
  char buf[128];
  for(int i=0; i<len; i++){
    snprintf(buf,128,"ptr[%2d]",i);
    print_ptr(buf,ptr[i]);
  }
}

// void run_test();

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];

  el_init(HEAP_SIZE);
  
  if(0){}

  else if( strcmp( test_name, "Single Allocation" )==0 ) {
    PRINT_TEST;
    // Tests that an allocation correctly splits the first single
    // block into 2 blocks, one used and one available

    printf("BEFORE MALLOC 0\n"); el_print_stats(); printf("\n");

    void *p0 = el_malloc(128);
    printf("AFTER MALLOC 0\n"); el_print_stats(); printf("\n");

    printf("POINTERS\n");
    print_ptr("p0",p0);
  } // ENDTEST

  else if( strcmp( test_name, "Three Allocs" )==0 ) {
    PRINT_TEST;
    // Tests that 3 allocations in a row correctly split off the main
    // block leaving 4 blocks, Used x 3 + Available x 1

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    printf("\nMALLOC 0\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(200);
    printf("\nMALLOC 1\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(64);
    printf("\nMALLOC 2\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);
  } // ENDTEST

  else if( strcmp( test_name, "Required Basics" )==0 ) {
    PRINT_TEST;
    // Allocates 3 blocks then tests that required functions like
    // el_get_header() and el_block_below() correctly calculate the
    // positions of block parts and adjacent blocks.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    ptr[len++] = el_malloc(200);
    ptr[len++] = el_malloc(64);

    el_blockhead_t *head = el_ctl.used->beg->next;
    el_blockfoot_t *foot;

    foot = el_get_footer(head);
    head = el_get_header(foot);
    print_ptr("used head 0",head);
    print_ptr("used foot 0",foot);

    head = el_block_below(head);
    foot = el_get_footer(head);
    head = el_get_header(foot);
    print_ptr("used head 1",head);
    print_ptr("used foot 1",foot);

    head = el_block_below(head);
    foot = el_get_footer(head);
    head = el_get_header(foot);
    print_ptr("used head 2",head);
    print_ptr("used foot 2",foot);

    head = el_block_below(head);
    printf("used head below 2 is: %p\n",head);

    printf("POINTERS\n"); print_ptrs(ptr, len);
  } // ENDTEST

  else if( strcmp( test_name, "Single Allocate/Free" )==0 ) {
    PRINT_TEST;
    // Tests a single allocate followed by freeing that block. The
    // free()'d block should be merged with the other available block
    // into a single large available block.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    printf("\nMALLOC 0\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[0]);
    printf("\nFREE 0\n"); el_print_stats(); printf("\n");
  } // ENDTEST

  else if( strcmp( test_name, "Four Allocs Free Ver1" )==0 ) {
    PRINT_TEST;
    // Allocates 4 times the frees 4 times in the order that the
    // allocation occured in. Looks for merging of blocks.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    printf("\nMALLOC 0\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(200);
    printf("\nMALLOC 1\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(64);
    printf("\nMALLOC 2\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(312);
    printf("\nMALLOC 3\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[0]);
    printf("\nFREE 0\n"); el_print_stats(); printf("\n");

    el_free(ptr[1]);
    printf("\nFREE 1\n"); el_print_stats(); printf("\n");

    el_free(ptr[2]);
    printf("\nFREE 2\n"); el_print_stats(); printf("\n");

    el_free(ptr[3]);
    printf("\nFREE 3\n"); el_print_stats(); printf("\n");
  } // ENDTEST

  else if( strcmp( test_name, "Four Allocs Free Ver2" )==0 ) {
    PRINT_TEST;
    // Allocates 4 times again but free()'s in a different order. This
    // prevents some merging and requires different cases of merging
    // above/below.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    printf("\nMALLOC 0\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(200);
    printf("\nMALLOC 1\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(64);
    printf("\nMALLOC 2\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(312);
    printf("\nMALLOC 3\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[1]);
    printf("\nFREE 1\n"); el_print_stats(); printf("\n");

    el_free(ptr[0]);
    printf("\nFREE 0\n"); el_print_stats(); printf("\n");

    el_free(ptr[3]);
    printf("\nFREE 3\n"); el_print_stats(); printf("\n");

    el_free(ptr[2]);
    printf("\nFREE 2\n"); el_print_stats(); printf("\n");
  } // ENDTEST

  else if( strcmp( test_name, "Four Allocs Free Ver3" )==0 ) {
    PRINT_TEST;
    // Another variation of allocating 4 times then free()'ing blocks
    // in a different order to examine if mergin works properly.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    printf("\nMALLOC 0\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(200);
    printf("\nMALLOC 1\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(64);
    printf("\nMALLOC 2\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(312);
    printf("\nMALLOC 3\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[3]);
    printf("\nFREE 3\n"); el_print_stats(); printf("\n");

    el_free(ptr[0]);
    printf("\nFREE 0\n"); el_print_stats(); printf("\n");

    el_free(ptr[2]);
    printf("\nFREE 2\n"); el_print_stats(); printf("\n");

    el_free(ptr[1]);
    printf("\nFREE 1\n"); el_print_stats(); printf("\n");
  } // ENDTEST

  else if( strcmp( test_name, "Alloc Fails" )==0 ) {
    PRINT_TEST;
    // Allocates 4 times which each succeed. Then attempts to allocate
    // again for a large block which cannot be allocated. el_malloc()
    // should return NULL in this case and the heap remains unchanged.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(1000);
    ptr[len++] = el_malloc(1000);
    ptr[len++] = el_malloc(1000);
    ptr[len++] = el_malloc(800);
    printf("\nMALLOC 4\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(512);
    printf("\nMALLOC 5\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);
    printf("should be (nil)\n");
  } // ENDTEST

  else if( strcmp( test_name, "EL Demo" )==0 ) {
    PRINT_TEST;
    // Recreates the behavior of the el_demo.c program and checks that
    // allocations/mergins are occurring correctly.

    printf("INITIAL\n"); el_print_stats(); printf("\n");

    void *p1 = el_malloc(128);
    void *p2 = el_malloc(48);
    void *p3 = el_malloc(156);
    printf("MALLOC 3\n"); el_print_stats(); printf("\n");

    printf("POINTERS\n");
    print_ptr("p3",p3);
    print_ptr("p2",p2);
    print_ptr("p1",p1);
    printf("\n");

    void *p4 = el_malloc(22);
    void *p5 = el_malloc(64);
    printf("MALLOC 5\n"); el_print_stats(); printf("\n");

    printf("POINTERS\n");
    print_ptr("p5",p5);
    print_ptr("p4",p4);
    print_ptr("p3",p3);
    print_ptr("p2",p2);
    print_ptr("p1",p1);
    printf("\n");

    el_free(p1);
    printf("FREE 1\n"); el_print_stats(); printf("\n");

    el_free(p3);
    printf("FREE 3\n"); el_print_stats(); printf("\n");

    p3 = el_malloc(32);
    p1 = el_malloc(200);
  
    printf("RE-ALLOC 3,1\n"); el_print_stats(); printf("\n");

    printf("POINTERS\n");
    print_ptr("p1",p1);
    print_ptr("p3",p3);
    print_ptr("p5",p5);
    print_ptr("p4",p4);
    print_ptr("p2",p2);
    printf("\n");

    el_free(p1);

    printf("FREE'D 1\n"); el_print_stats(); printf("\n");

    el_free(p2);

    printf("FREE'D 2\n"); el_print_stats(); printf("\n");

    el_free(p3);
    el_free(p4);
    el_free(p5);

    printf("FREE'D 3,4,5\n"); el_print_stats(); printf("\n");
  } // ENDTEST

  else if( strcmp( test_name, "Stress 1" )==0 ) {
    PRINT_TEST;
    // Stress testing with many malloc()'s / free()'s. More thoroughly
    // tests combinations of calls and sequences. Implementations that
    // may have appeared correct in simple tests may buckle under such
    // added stress.

    void *ptr[16] = {};
    int len = 0;

    ptr[len++] = el_malloc(128);
    ptr[len++] = el_malloc(256);
    ptr[len++] = el_malloc(64);
    ptr[len++] = el_malloc(200);
    printf("MALLOC 1-4\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[2]);    ptr[2] = NULL;
    printf("\nFREE 2\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(64);
    printf("\nMALLOC 5\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[1]);    ptr[1] = NULL;
    printf("\nFREE 1\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(50);
    ptr[len++] = el_malloc(50);
    printf("\nMALLOC 6-7\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(100);
    printf("\nMALLOC 8\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    el_free(ptr[5]);   ptr[5] = NULL;
    el_free(ptr[0]);   ptr[0] = NULL;
    el_free(ptr[6]);   ptr[6] = NULL;
    printf("\nFREE 5,0,6\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);

    ptr[len++] = el_malloc(200);
    ptr[len++] = el_malloc(512);
    ptr[len++] = el_malloc(16);
    ptr[len++] = el_malloc(32);
    printf("\nMALLOC 9,10,11\n"); el_print_stats(); printf("\n");
    printf("POINTERS\n"); print_ptrs(ptr, len);
  } // ENDTEST

  else{
    printf("No test named '%s' found\n",test_name);
    return 1;
  }

  el_cleanup();
  return 0;
}
