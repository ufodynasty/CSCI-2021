#include <stdio.h>

void print_intbits(int num);

int main(int argc, char *argv[]){
  int x;

  printf("x has only the 16th bit set\n");
  x = 1 << 16;
  print_intbits(x);

  printf("x as decimal: %d\n", x);
  printf("x as octal  : %o\n", x);
  printf("x as hex    : %x\n", x);
  printf("\n");

  printf("set 19th bit as well\n");
  x = x | (1 << 19);
  print_intbits(x);

  printf("set 3rd bit as well\n");
  x = x | (1 << 3);
  print_intbits(x);

  printf("invert the bits\n");
  x = ~x;
  print_intbits(x);

  printf("clear the 8th bit\n");
  x = x & ~(1 << 8);
  print_intbits(x);
  
  printf("clear the 25th bit\n");
  // TODO: clear given bit in x
  x = x & ~(1 << 25);
  print_intbits(x);
  
  printf("clear all bits via xor\n");
  x = x ^ x;
  print_intbits(x);

  printf("place the pattern 110101 starting at bit 8\n");
  x = x | (0b110101 << 8);
  print_intbits(x);

  printf("place the pattern 10011111 starting at bit 20\n");
  // TODO: clear place given pattern as indicated
  x = x | (0b10011111 << 20);
  print_intbits(x);
  
  int y;
  printf("set y to be x shifted right by 4 bits\n");
  y = x >> 4;
  print_intbits(y);

  printf("set y to be x shifted right by 24 bits\n");
  // TODO: assign y based on shift
  y = x >> 24;
  print_intbits(y);
  
  printf("conditionally print 'x 13th bit SET' or 'x 13th bit CLEAR'\n");
  if( x & (1 << 13) ){
    printf("x 13th bit SET\n");
  }
  else{
    printf("x 13th bit CLEAR\n");
  }
  printf("\n");

  printf("conditionally print 'y 4th bit SET' or 'y 4th bit CLEAR'\n");
  // TODO: check given bit
  if( y & (1 << 4)){
    printf("x 4th bit SET\n");
  }
  else{
    printf("x 4th bit CLEAR\n");
  }
  printf("\n");

  return 0;
}

void print_intbits(int num){
  char *indexes = "\
  28   24   20   16   12    8    4    0\
";
  char bits[32+8+1] = {};       // 32 1/0, 8 spaces, 1 \0
  int idx = 0;
  for(int i=0; i<32; i++){
    if(i>0 && i%4==0){
      bits[idx] = ' ';
      idx++;
    }
    bits[idx] = num & (1 << (31-i)) ? '1' : '0';
    idx++;
  }
  printf("bits:  %s\n",bits);
  printf("index: %s\n",indexes);
  printf("\n");
}
