/// puzzlebox.c: Inputs are read from a file on the command line.  The
/// inputs are modified in various ways to checked to match specific
/// patterns associated with "phases".  Each set of correct inputs
/// "passes" a phase and scores points.
///
/// USING THE DEBUGGER is almost essential to understand what is
/// happening in the source code. Compile with debug flags and run in
/// the gdb debugger as in
///
/// > gcc -g -o puzzlebox puzzlebox.c
/// > gdb -tui ./puzzlebox
///
/// is a good policy. 
///
/// Original DebugMe.java version and rhymes by Mark Snyder <msnyde14@gmu.edu>
/// C Port/Adaptation by Chris Kauffman <kauffman@umn.edu>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>

#define BUFSIZE 128
#define NSTAGES 10             
int points[NSTAGES+1] = {
  0,                           
  8,                           
  8,                           
  8,                           
  8,                           
  5,                           
  5,                           
  4,                           
  4,                           
  5,                           
  5,                           
};

int score = 0;
int max_score = 50;
char *userID = NULL;
int hash = 0;

void setup();   void end_now();
void phase01(); void phase02(); void phase03(); void phase04(); void phase05();
void phase06(); void phase07(); void phase08(); void phase09(); void phase10();

int main(int argc, char *argv[]){
  printf("========================================\n");
  printf("PROBLEM 2: Puzzlebox\n");

  if(sizeof(int)!=4 || sizeof(long)!=8){
    printf("Unexpected byte sizes of int or long\n");
    printf("      %5s %5s\n","EXPECT","ACTUAL");
    printf(" int: %5d %5lu\n",4,sizeof(int));
    printf("long: %5d %5lu\n",8,sizeof(long));
    printf("\n");
    printf("puzzlebox must be run on a 64-bit architecture. Bailing out\n");
    return 1;
  }

  if(argc < 2){
    printf("usage: %s <infile>\n",argv[0]);
    printf("  Provide a text file to read from on the command line\n");
    printf("  The first token in the input file is your Internet ID like kauf0095\n");
    printf("  Bailing out.\n");
    return 1;
  }

  setup(argv[1]);

  printf("PHASE 1: A puzzle you say? Challenge accepted!\n");
  phase01();
  score += points[1];

  printf("PHASE 2: That was cake by the ocean! Wait: the cake is a lie!\n");
  phase02();
  score+=points[2];

  printf("PHASE 3: Warm-up is over. This $#!^ just go real.\n");
  phase03();
  score+=points[3];

  printf("PHASE 4: Tired yet? Nope? There's more in phase four.\n");
  phase04();
  score+=points[4];

  printf("PHASE 5: You're doing well. But can you break through this secret technique of darkness?\n");
  phase05();
  score+=points[5];

  printf("PHASE 6: Watch out, here comes a wall of bricks! It's time for you to solve phase six.\n");
  phase06();
  score+=points[6];

  printf("PHASE 7: Next it's phase eleven! oops, seven. (off-by-4 errors don't lose credit, right?)\n");
  phase07();
  score+=points[7];

  printf("PHASE 8: You're doing great, now try phase 1000!\n");
  phase08();
  score+=points[8];

  printf("PHASE 9: Finally, the finish line; Can you solve phase nine?\n");
  phase09();
  score+=points[9];

  printf("PHASE 10: Rule #1: The doctor lies. Next time a message mentions 'finish line,' check the source code.\n");
  phase10();
  score+=points[10];

  printf("***Achievement Unlocked***\n");
  printf("gdb? Yeah you know me!\n");
  end_now();

  return 0;
}

void setup_signal_handlers();
void failure(char *msg);
void end_now();
void setup_input(char *fname);
void close_input();
char *next_input();

void setup(char *infile_name){
  setup_signal_handlers();
  setup_input(infile_name);
  userID = next_input();
  int len = strlen(userID);
  if(len != 8){
    printf("'%s' is a userID and must be 8 characters\n",
           userID);
    exit(1);
  }
  hash = 0;

  int *hash1 = (int *) (userID);   
  int *hash2 = (int *) (userID+4); 
  hash = (*hash1) ^ (*hash2);      

  if(hash < 0){
    hash = -hash;
  }
    
  printf("UserID '%s' accepted: hash value = %d\n",userID,hash);

}
  
  
#define NSIGNALS 35
char *signal_names[NSIGNALS] = {
  "",
  "SIGHUP",                         /// 1  Hangup
  "SIGINT",                         /// 2  Interrupt
  "SIGQUIT",                        /// 3  Quit
  "SIGILL",                         /// 4  Illegal Instruction
  "SIGTRAP",                        /// 5  Trace/Breakpoint Trap
  "SIGABRT",                        /// 6  Abort
  "SIGEMT",                         /// 7  Emulation Trap
  "SIGFPE (usually divide by 0)",   /// 8  Arithmetic Exception
  "SIGKILL",                        /// 9  Killed
  "SIGBUS",                         /// 10 Bus Error
  "SIGSEGV (out of bounds memory)", /// 11 Segmentation Fault
  "SIGSYS",                         /// 12 Bad System Call
  "SIGPIPE",                        /// 13 Broken Pipe
  "SIGALRM",                        /// 14 Alarm Clock
  "SIGTERM",                        /// 15 Terminated
  "SIGUSR1",                        /// 16 User Signal 1
  "SIGUSR2",                        /// 17 User Signal 2
  "SIGCHLD",                        /// 18 Child Status
  "SIGPWR",                         /// 19 Power Fail/Restart
  "SIGWINCH",                       /// 20 Window Size Change
  "SIGURG",                         /// 21 Urgent Socket Condition
  "SIGPOLL",                        /// 22 Socket I/O Possible
  "SIGSTOP",                        /// 23 Stopped (signal)
  "SIGTSTP",                        /// 24 Stopped (user)
  "SIGCONT",                        /// 25 Continued
  "SIGTTIN",                        /// 26 Stopped (tty input)
  "SIGTTOU",                        /// 27 Stopped (tty output)
  "SIGVTALRM",                      /// 28 Virtual Timer Expired
  "SIGPROF",                        /// 29 Profiling Timer Expired
  "SIGXCPU",                        /// 30 CPU time limit exceeded
  "SIGXFSZ",                        /// 31 File size limit exceeded
  "SIGWAITING",                     /// 32 All LWPs blocked
  "SIGLWP",                         /// 33 Virtual Interprocessor Interrupt for Threads Library
  "SIGAIO",                         /// 34 Asynchronous I/O
};

void handle_signals(int signum){
  char msg[BUFSIZE];
  snprintf(msg,BUFSIZE,"Fatal signal %d (%s) received",
           signum,signal_names[signum]);
  failure(msg);
}

void setup_signal_handlers(){
  for(int i=1; i<NSIGNALS; i++){
    if(i != SIGKILL && i != SIGSTOP) 
    {
      signal(i, handle_signals);
    }
  }
}

char inputs[BUFSIZE][BUFSIZE] = {};
int input_idx = -1;                
FILE *input_fh = NULL;             

void setup_input(char *fname){
  input_fh = fopen(fname,"r");
  if(input_fh == NULL){
    perror("Couldn't open input file");
    exit(1);
  }
}

void close_input(){
  if(input_fh == NULL){
    fprintf(stderr,"Input file not open\n");
    exit(1);
  }
  fclose(input_fh);
}

char *next_input(){
  input_idx++;
  int ret = fscanf(input_fh, "%s", inputs[input_idx]);
  if(ret != 1){
    fprintf(stderr, "!! No more input: assuming \"\" for input %d\n", input_idx);
    inputs[input_idx][0] = '\0';
  }
  return inputs[input_idx];
}

void failure(char *msg){
  printf("\n");
  printf("Ah ah ah, you didn't say the magic word...\n");
  printf("Failure: %s\n",msg);
  end_now();
}

void end_now(){
  printf("\nRESULTS: %d / %d points\n",score,max_score);
  close_input();
  exit(0);
}

void phase01(){
  int a = atoi(next_input());
  int b = atoi(next_input());
  int c = atoi(next_input());
    
  a += hash % 41;
  if (a<b && b>c && a<c) {
    return;                    
  }
  failure("Double debugger burger, order up!");
}
  
void phase02(){
  int a = atoi(next_input());
  int b = atoi(next_input());
  int c = atoi(next_input());
  if(a==0){
    goto FAIL2;
  }
    
  a += hash%26;
  int v = a+b;
  v *= a;
  v /= b;
  v += 14;
  if (c==v){
    return;
  }
 FAIL2:
  failure("These aren't the ints you're looking for. Move along.");

}
  
void phase03(){
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
    return;
  }

  failure("Shifty bits hit? Xor not it seems...");
}
  
void substring(char *dest, char *src, int start, int stop, int max){
  int i;
  for(i=0; i<(stop-start) && i<max; i++){
    dest[i] = src[start+i];
  }
  if(i==max){
    fprintf(stderr,"ERROR: substring reached max %d for source string '%s' start:%d end:%d\n",
            max,src,start,stop);
    exit(1);
  }
  dest[i] = '\0';
}


void phase04(){
  char *s = next_input();
  int a = atoi(next_input());
  int b = atoi(next_input());
  int c = atoi(next_input());
  int len = strlen(s);
  for(int i=0; i<len-1; i++){
    if(s[i]==s[i+1]){
      failure("I petition for less repetition!");
    }
  }
  char temp1[BUFSIZE]={}, temp2[BUFSIZE]={};
  substring(temp1, s, a, b, BUFSIZE);
  substring(temp2, s, b, c, BUFSIZE);
  int len1 = strlen(temp1);
  int len2 = strlen(temp2);
  int idx = 0;
  while(idx<len1 && idx<len2){
    if(temp1[idx] != temp2[idx]){
      break; 
    }
    idx++; 
  }
  int targ = (hash % 5)+3;
  if(idx==targ){
    return;
  }
  failure("Over here and over there, I need a certain kind of pair...");

}
  
void phase05(){
  int n = atoi(next_input());
  int m = atoi(next_input());
  int t = (hash % 30) + 21;
  int s = 0;
  while(n>1){
    if(n & 1){
      n = (n<<2) - n + 1;
    }
    else {
      n = n >> 1;
    }
    if(s == t && m == t){
      return;
    }
    s++;
  }
  failure("Seems you forgatz the essence of Collatz");
}
  
void phase06(){
  int a = atoi(next_input());
  int b = atoi(next_input());
  int c = atoi(next_input());
  int d = atoi(next_input());

  char expect[BUFSIZE] =
    "There are 10 kinds of people in the world: those who understand binary and those who don't";
  char actual[BUFSIZE] = {};
  strcpy(actual,expect);
  int slen = strlen(expect);
  int ilen = slen / sizeof(int) - 1;
  int munge1 = (hash % 211) % ilen;
  int munge2 = (hash % 311) % ilen;
  ((int *)actual)[munge1] = 0x58585858;
  ((int *)actual)[munge2] = 0x59595959;
  *(((int *)actual) + a) = b;
  *(((int *)actual) + c) = d;

  
  printf("%s\n",actual);
  if(strncmp(expect,actual,BUFSIZE) == 0){
    return;
  }

  failure("Here are hints:\n- use two ints with 4 bytes to make the message right\n- beware of endian ordering angst\n");
}

void phase07(){
  float a = atof(next_input());
  union {
    int i;
    float f;
  } flint;
  flint.i = hash;
  
  if( fabs(a-flint.f) < 1e-8 ){
    return;
  }
  char * msg =
    "Ugly cousin to the struct: if you don't know unions, then on this phase you're ...\n"
    "stuck.\n"
    "What did you think was going to rhyme with 'struct'? A curseword?\n"
    "Keep it PG: there are little bits 'n bytes with ears around here.\n"
    ;
  failure(msg);
}

void phase08() {
  int n = atoi(next_input());
  int m = atoi(next_input());
  int t = (hash % 83) + 21;
  int s = 0;
  char *msg =
    "Do you like spaghetti? Try some spaghetti! It's good, right?\n"
    "What, you prefer structured loops? How mundane.\n";
  goto LTOP;

 LEND:
  failure(msg);
 LOM1:
  n = (n<<2) - n + 1;
 LCHK:
  if(s == t && m == t){
    goto LAFT;
  }
  s++;
  goto LTOP;
 LOC1:
  if(n & 1){
    goto LOM1;
  }
  goto LEM1;
 LTOP:
  if(!(n>1)){
    goto LEND;
  }
  goto LOC1;
 LEM1:
  n = n >> 1;
  goto LCHK;
 LAFT:
  return;
}

  
unsigned long state = 1;

unsigned int pb_rand() {
  state = state * 1103515245 + 12345;
  return (unsigned int)(state/65536) % 32768;
}

void pb_srand(unsigned long seed){
  state = seed;
}

void scramble(char *str, int rounds){
  int len = strlen(str);
  for(int i=0; i<rounds; i++){
    unsigned int idx = pb_rand() % len;
    unsigned int jdx = pb_rand() % len;
    char tmp = str[idx];
    str[idx] = str[jdx];
    str[jdx] = tmp;
  }
}

char letters[BUFSIZE] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void phase09(){
  int idxs[5] = {};
  int len = strlen(letters);
  for(int i=0; i<5; i++){
    idxs[i] = atoi(next_input());
    if(idxs[i] >= len){                     
      char *msg =
        "\"My, what big ints you have, Granny!\" "
        "\"All the better to overflow your buffers my dear\"\n";
      failure(msg);
    }
  }

  long seed = (((long) hash) << 32) + ~hash;
  pb_srand(seed);                           
  scramble(letters, 100);                   
  
  char buf[BUFSIZE] = {};                   
  for(int i=0; i<5; i++){           
    buf[i] = letters[idxs[i]];              
  }

  union{
    long l;
    char s[8];
  } chong;
  chong.l = 478426194263;                   

  if(strcmp(buf,chong.s)==0){               
    return;
  }
  char *msg =
    "Where's that stripey hipster with the lame hat and cane?\n"
    "He's all spread around in there. Find him.";
  failure(msg);
}

void phase10(){

  long a = atol(next_input());
  char ans[] = "        ";
  for(int i=0; i<8; i++){
    ans[i] = (char) (a >> (7*i) & 0x7F);
  }

  char *accept = userID;
  if(strcmp(ans,accept)==0){
    printf("OMG %s, the answers were inside you the the whole time!\n",accept);
    return;
  }

  char msg[BUFSIZE] = {};
  snprintf(msg, BUFSIZE,
           "'%s'??? Not quite, try a little closer to home...\n",
           ans);

  failure(msg);
}






