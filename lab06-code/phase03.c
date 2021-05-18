// phase03.c: mock phase03 from puzzlebox.c with a fixed hash
// code. Use GDB and knoweldge of how bit-wise operations like shifts,
// ors, xors work to gain insight on solvin the Project 2's puzzlebox.

#include <stdio.h>
#include <stdlib.h>
void end_now();
char *next_input();

int hash = 8765309;
int INPUTS[4];

void phase03(){
  // TODO: put numbers in input.txt to pass the code below
  int a = atoi(next_input());
  int b = atoi(next_input());
  int c = atoi(next_input());
  int d = atoi(next_input());

  int targ =
    1 << ((hash % 7)+24) |
    1 << (hash % 17)     |
    1 << (hash % 19);

  int shot = 0;
  shot |= 1 << a;
  shot |= 1 << b;
  shot |= 1 << c;
  shot |= 1 << d;

  int hit = shot ^ targ;
  hit = !hit;

  if(hit){
    printf("Right on target: nice shootin' bitslinger!\n");
    return;
  }

  printf("Shifty bits hit? Xor not it seems...\n");
  end_now();
}


////////////////////////////////////////////////////////////////////////////////
// additional code to get inputs/start up the program/run main()

#define BUFSIZE 128
char inputs[BUFSIZE][BUFSIZE] = {}; // array of inputs read from input file
int input_idx = -1;                 // index of most recently read input
FILE *input_fh = NULL;              // file handle for inputs

// Open the provided input file
void setup_input(char *fname){
  input_fh = fopen(fname,"r");
  if(input_fh == NULL){
    perror("Couldn't open input file");
    exit(1);
  }
}

// Close the input file
void close_input(){
  if(input_fh == NULL){
    fprintf(stderr,"Input file not open\n");
    exit(1);
  }
  fclose(input_fh);
}

// Retrieve the next input from the file. Empty strings are placed in
// the inputs array if the file is out of input.
char *next_input(){
  input_idx++;
  int ret = fscanf(input_fh, "%s", inputs[input_idx]);
  if(ret != 1){
    fprintf(stderr, "!! No more input: assuming \"\" for input %d\n", input_idx);
    inputs[input_idx][0] = '\0';
  }
  return inputs[input_idx];
}

// Ending sequence for program
void end_now(){
  close_input();
  exit(0);
}

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <infile>\n",argv[0]);
    return 1;
  }
  char *infile = argv[1];
  setup_input(infile);
  printf("Running mock Phase03\n");
  phase03();
  printf("Phase complete\n");
  end_now();
  return 0;
}
    
