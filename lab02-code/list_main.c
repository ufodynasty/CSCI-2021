// SOLUTION: main function for a linked list manager

#include <stdio.h>
#include <string.h>
#include "list.h"

int main(int argc, char *argv[]){
  int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
  if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
    echo=1;
  }

  printf("Linked List Demo\n");
  printf("Commands:\n");
  printf("  print:          shows the current contents of the list\n");
  printf("  clear:          eliminates all elements from the list\n");
  printf("  exit:           exit the program\n");
  printf("  insert thing:   inserts the given string into the list\n");
  printf("  get index:      get the item at the given index\n");
  printf("  contains thing: determine if the given thing is in the list\n");
  printf("                  (NOT YET IMPLEMENTED)\n");
  
  char cmd[128];
  list_t list;
  int success;
  list_init(&list);

  while(1){
    printf("list> ");                 // print prompt
    success = fscanf(stdin,"%s",cmd); // read a command
    if(success==EOF){                 // check for end of input
      printf("\n");                   // found end of input
      break;                          // break from loop
    }

    if( strcmp("exit", cmd)==0 ){     // check for exit command
      if(echo){
        printf("exit\n");
      }
      break;                          // break from loop
    }

    else if( strcmp("insert", cmd)==0 ){ // insertion
      fscanf(stdin,"%s",cmd);            // read string to insert
      if(echo){
        printf("insert %s\n",cmd);
      }

      success = list_insert(&list, cmd); // call list function
      if(!success){                      // check for success
        printf("insert failed\n");
      }
    }

    else if( strcmp("get", cmd)==0 ){     // get command
      int index;
      fscanf(stdin,"%d",&index);          // read an integer
      if(echo){
        printf("get %d\n",index);
      }

      char *ith = list_get(&list, index); // call list function
      if(ith == NULL){                    // check for success
        printf("out of bounds\n");
      }
      else {
        printf("%d: %s\n",index,ith);
      }
    }

    else if( strcmp("clear", cmd)==0 ){   // clear command
      if(echo){
        printf("clear\n");
      }
      list_clear(&list);
    }

    else if( strcmp("print", cmd)==0 ){   // print command
      if(echo){
        printf("print\n");
      }
      list_print_all(&list);
    }

    else if(strcmp("contains", cmd)==0){  // contains command
      fscanf(stdin, "%s", cmd);           // read string to search for
      if(echo){
        printf("contains %s\n",cmd);
      }

      success = list_contains(&list, cmd);
      if(success){
        printf("'%s' is present\n",cmd);
      }
      else{
        printf("not found\n");
      }
    }

    else{                                 // unknown command
      if(echo){
        printf("%s\n",cmd);
      }
      printf("unknown command %s\n",cmd);
    }
  }  

  // end main while loop
  list_clear(&list);                      // clean up the list
  return 0;
}
