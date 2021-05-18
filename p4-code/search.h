// Header for search algorithm problem

#ifndef SEARCH_H
#define SEARCH_H 1

// Type of nodes for linked lists and trees
typedef struct node {
  int data;                     // node data
  struct node *left;            // left branch,  NULL if not present
  struct node *right;           // right branch, NULL if not present
} node_t;

// Type of tree itself
typedef struct {
  node_t *head;                 // head of list, NULL if list empty
  int size;                     // number of nodes in tree
} list_t;


// Type of tree itself
typedef struct {
  node_t *root;                 // root of tree, NULL if tree empty
  int size;                     // number of nodes in tree
} bst_t;


// search_funcs.c
int linear_array_search(int array[], int len, int query);
int linkedlist_search(list_t *list, int len, int query);
int binary_array_search(int array[], int len, int query);
int binary_tree_search(bst_t *tree, int ignore, int query);
unsigned int pb_rand();
void pb_srand(unsigned long seed);
int *make_evens_array(int len);
list_t *make_evens_list(int len);
bst_t *make_evens_tree(int len);
node_t *tree_merge(node_t *arr[], int lo, int hi);
void list_free(list_t *list);
void bst_free(bst_t *tree);
void node_remove_all(node_t *cur);

#endif
