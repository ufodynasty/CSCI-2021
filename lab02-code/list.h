/* List Functions */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct node_struct {
  char data[128];
  struct node_struct *next;
} node_t;

typedef struct {
  node_t *head;
  int size;
} list_t;

void list_init(list_t *list);
// Initialize the memory associated with the given list to emptiness

int list_size(list_t *list);
// Returns how many nodes are in a list

char *list_get(list_t *list, int index);
// Get a pointer to the data at the specified index. Returns NULL if
// the index is out of bounds. Uses an iterative approach.

void list_print_all(list_t *list);
// Print all elements of a list. Uses the helper function
// node_print_all() for most of the work.

void node_print_all(node_t *cur, int index);
// Print all elements of the list preceded by their index. Uses a
// recursive approach.

int list_insert(list_t *list, char *new_data);
// Insert the given data in sorted order to the given list. Makes use
// of the node_insert() function to do most of the work. Attempting to
// add duplicate data to the list will not change the list. Returns 1
// if the list is modified or 0 if not modified due to duplicate
// entries

node_t *node_insert(node_t *cur, char *new_data);
// Insert in the new_data in sorted order to the given list using
// recursion.  Uses recursion to unstitch the list then re-stitch it
// back together on a successful insert. Returns a non-null node which
// is the head of the list on success. If duplicate data is found,
// returns NULL and does not modify the list.

void list_clear(list_t* list);
// Remove all nodes associated with the list setting its size to 0

////////////////////////////////////////////////////////////////////////////////

int list_contains(list_t *list, char *query);
// Returns 1 if the list contains the given query and 0 otherwise.
// NOT YET IMPLEMENTED

#endif
