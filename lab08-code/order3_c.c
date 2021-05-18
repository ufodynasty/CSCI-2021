// order3_c.c: demonstrates C code with several function calls to
// order3() in it. Translate the main() function to assembly in
// order3_asm.s.

#include <stdio.h>

void order3(int *a, int *b, int *c);

int main(){                     // main function to be translated to assembly
  int r=17, t=12, v=13;
  order3(&r, &t, &v);

  int q= 5, e= 9, d= 2;
  order3(&q, &e, &d);

  int i=25, j=27, k=29;
  order3(&i, &j, &k);

  printf("r t v: %2d %2d %2d\n",r,t,v);
  printf("q e d: %2d %2d %2d\n",q,e,d);
  printf("i j k: %2d %2d %2d\n",i,j,k);
  
  return 0;
}

// Ensures that the integers a,b,c are "sorted": a is the min, b is
// the middle, and c is the max.  Changes the integers at these
// locations to accomplish this.
void order3(int *a, int *b, int *c){
  int tmp = 0;
  if(*a > *b){                  // bubble a up
    tmp = *a;
    *a = *b;
    *b = tmp;
  }
  if(*b > *c){
    tmp = *b;
    *b = *c;
    *c = tmp;                   // c is now max
  }            
  if(*a > *b){                   
    tmp = *a;
    *a = *b;
    *b = tmp;                   // b is no middle, b min val
  }
  return;
}

