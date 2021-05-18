// linked list functions, student version

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // for strcpy() and strcmp()
#include "list.h"

// Initialize the memory associated with the given list to emptiness
void list_init(list_t *list){
  list->head = NULL;
  list->size = 0;
  return;
}

// Returns how many nodes are in a list
int list_size(list_t *list){
  return list->size;
}

// Get a pointer to the data at the specified index. Returns NULL if
// the index is out of bounds. Uses an iterative approach.
char *list_get(list_t *list, int index){

  // ...didn't have time to write checks on whether index is in
  // bounds, add this later...
  int i = 0;
  node_t *ptr = list->head;
  while(i!=index && ptr!=NULL){
    i++;
    ptr = ptr->next;
  }
  if(!ptr) {
    return NULL;
  }
  return ptr->data;
}

// Print all elements of a list. Uses the helper function
// node_print_all() for most of the work.
void list_print_all(list_t *list){
  node_print_all(list->head, 0);
}

// Print all elements of the list preceded by their index. Uses a
// recursive approach.
void node_print_all(node_t *cur, int index){
  if(cur == NULL){              // end of the list
    return;
  }
  printf("%d: %s\n",index, cur->data); // print index and data
  node_print_all(cur->next, index+1);  // recurse on next node
  return;
}

// Insert the given data in sorted order to the given list. Makes use
// of the node_insert() function to do most of the work. Attempting to
// add duplicate data to the list will not change the list. Returns 1
// if the list is modified or 0 if not modified due to duplicate
// entries
int list_insert(list_t *list, char *new_data){
  node_t *result = node_insert(list->head, new_data);
  if(result == NULL){           // duplicate found, ignore
    return 0;                   // 0 indicates not modified
  }
  else{                         // successful insert
    list->head = result;        // head may have changed
    list->size++;               // size now larger
    return 1;                   // 1 indicates modifed
  }
}

// Add in the new_data in sorted order to the given list using
// recursion.  Uses recursion to unstitch the list then re-stitch it
// back together on a successful insert. Returns a non-null node which
// is the head of the list on success. If duplicate data is found,
// returns NULL and does not modify the list.
node_t *node_insert(node_t *cur, char *new_data){
  int diff = -1;
  if(cur != NULL){
    diff = strcmp(new_data, cur->data); // compare new_data to current
  }
  if(cur == NULL || diff < 0){                 // found insertion point
    node_t *new_node = malloc(sizeof(node_t)); // allocate
    strcpy(new_node->data, new_data);          // copy data
    new_node->next = cur;                      // link to next
    return new_node;                           // successful insert
  }
  else if(diff > 0){            // insertion point is later
    node_t *result = node_insert(cur->next, new_data);
    if(result == NULL){
      return NULL;
    }
    else{
      cur->next = result;
      return cur;
    }
  }
  else{ // diff == 0 // duplicate
    return NULL;
  }
}

// Remove all nodes associated with the list setting its size to 0
void list_clear(list_t* list){
  node_t *ptr = list->head;
  while(ptr != NULL){
    node_t *freeit = ptr;
    ptr = ptr->next;
    free(freeit);
  }
  list->head = NULL;
  list->size = 0;
  return;
}

///////////////////////////////////////////////////////////////////////////////// 

// Returns 1 if the list contains the given query and 0 otherwise.
int list_contains(list_t *list, char *query){
  node_t *ptr = list->head;
  while(ptr != NULL){
    if(!strcmp(query, ptr->data)) {
      return 1;
    }
    ptr = ptr->next;
  }
  return 0;
}
