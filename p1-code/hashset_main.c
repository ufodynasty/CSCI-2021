#include "hashset.h"

int main(int argc, char *argv[]){
  int echo = 0;                                
  if(argc > 1 && strcmp("-echo",argv[1])==0) { 
    echo=1;
  }

  printf("Hashset Application\n");
  printf("Commands:\n");
  printf("  hashcode <item>  : prints out the numeric hash code for the given key (does not change the hash set)\n");
  printf("  contains <item>  : prints the value associated with the given item or NOT PRESENT\n");
  printf("  add <item>       : inserts the given item into the hash set, reports existing items\n");
  printf("  print            : prints all items in the hash set in the order they were addded\n");
  printf("  structure        : prints detailed structure of the hash set\n");
  printf("  clear            : reinitializes hash set to be empty with default size\n");
  printf("  save <file>      : writes the contents of the hash set to the given file\n");
  printf("  load <file>      : clears the current hash set and loads the one in the given file\n");
  printf("  next_prime <int> : if <int> is prime, prints it, otherwise finds the next prime and prints it\n");
  printf("  expand           : expands memory size of hash set to reduce its load factor\n");
  printf("  bye              : exit the program\n");
  
  char cmd[128];
  hashset_t hs;
  int success;
  hashset_init(&hs,HASHSET_DEFAULT_TABLE_SIZE);

  while(1){
    printf("HS|> ");               
    success = fscanf(stdin,"%s",cmd);
    if(success==EOF){    //If reading comands from a file, escape if the file ends without calling bye
      printf("\n");                   
      break;                          
    }

    if( strcmp("bye", cmd)==0 ){ //Escapes the program
      if(echo){
        printf("bye\n");
      }
      break;                          
    }

    else if( strcmp("hashcode", cmd)==0 ){ //Prints the hashcode of the provided string
      fscanf(stdin,"%s",cmd);            
      if(echo){
        printf("hashcode %s\n",cmd);
      }

      printf("%ld\n",hashcode(cmd));
    }

    else if( strcmp("contains", cmd)==0 ){ //Uses hashset_contains to determine if the provided string is contained within the hashset
      fscanf(stdin,"%s",cmd);            
      if(echo){
        printf("contains %s\n",cmd);
      }

      printf(hashset_contains(&hs,cmd)?"FOUND: %s\n":"NOT PRESENT\n",cmd);
    }

    else if( strcmp("add", cmd)==0 ){ //If the provided string is not in the hashset, adds it to the hashset using hashset_add
      fscanf(stdin,"%s",cmd);            
      if(echo){
        printf("add %s\n",cmd);
      }

      printf(hashset_add(&hs,cmd)?"":"Item already present, no changes made\n");
    }

    else if( strcmp("print", cmd)==0 ){ //Prints an ordered list of all elements in the hashset using hashset_write_items_ordered
      if(echo){
        printf("print\n");
      }

      hashset_write_items_ordered(&hs,stdout);
    }

    else if( strcmp("structure", cmd)==0 ){ //Prints a structured view of the hashset using hashset_show_structure
      if(echo){
        printf("structure\n");
      }

      hashset_show_structure(&hs);
    }

    else if( strcmp("clear", cmd)==0 ){ //Removes all elements from the hashset by freeing all allocated memory and initializing a new hashset
      if(echo){
        printf("clear\n");
      }

      hashset_free_fields(&hs);
      hashset_init(&hs,HASHSET_DEFAULT_TABLE_SIZE);
    }

    else if( strcmp("save", cmd)==0 ){ //Saves the hashset to a file provided by the user using hashset_save
      fscanf(stdin,"%s",cmd);            
      if(echo){
        printf("save %s\n",cmd);
      }

      hashset_save(&hs,cmd);
    }

    else if( strcmp("load", cmd)==0 ){ //Loads a hashset from a file provided by the user using hashset_load
      fscanf(stdin,"%s",cmd);            
      if(echo){
        printf("load %s\n",cmd);
      }

      printf(hashset_load(&hs,cmd)?"":"load failed\n");
    }

    else if( strcmp("next_prime", cmd)==0 ){ //Prints out the next prime number after the user provided number using next_prime
      int num;
      fscanf(stdin,"%d",&num);            
      if(echo){
        printf("next_prime %d\n",num);
      }

      printf("%d\n",next_prime(num));
    }

    else if( strcmp("expand", cmd)==0 ){ //Expands the memory used by the hashset using hashset_expand
      if(echo){
        printf("expand\n");
      }

      hashset_expand(&hs);
    }
    
    else{ //Alerts the user that they tried to use an invalid command                             
      if(echo){
        printf("%s\n",cmd);
      }
      printf("unknown command %s\n",cmd);
    }
  }  

  
  hashset_free_fields(&hs);                      
  return 0;
}