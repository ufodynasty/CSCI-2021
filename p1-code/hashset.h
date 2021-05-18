// hashset.h: header for hashset problem

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASHSET_H
#define HASHSET_H 1

// Type for linked list nodes in hash set
typedef struct hashnode {
  char item[128];               // string for the item in this node
  struct hashnode *table_next;  // pointer to next node at table index of this node, NULL if last node
  struct hashnode *order_next;  // pointer to next node in insert order, NULL if last item added
} hashnode_t;

// Type of hash table
typedef struct {
  int item_count;               // number of items in the table
  int table_size;               // how big is the table array
  hashnode_t **table;           // array of "buckets" which contain nodes
  hashnode_t *order_first;      // pointer to the first item node that was added
  hashnode_t *order_last;       // pointer to last item that node that was added
} hashset_t;

#define HASHSET_DEFAULT_TABLE_SIZE 5 // default size of table for main application

// functions defined in hashset_funcs.c
long  hashcode(char key[]);
int   next_prime(int num);

void  hashset_init(hashset_t *hs, int table_size);
int   hashset_add(hashset_t *hs, char item[]);
int   hashset_contains(hashset_t *hs, char key[]);
void  hashset_expand(hashset_t *hs);
void  hashset_free_fields(hashset_t *hs);

void  hashset_write_items_ordered(hashset_t *hs, FILE *out);
void  hashset_show_structure(hashset_t *hs);
void  hashset_save(hashset_t *hs, char *filename);
int   hashset_load(hashset_t *hs, char *filename);

#endif
