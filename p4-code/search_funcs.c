#include <stdlib.h>
#include "search.h"


////////////////////////////////////////////////////////////////////////////////
// SEARCH ALGORITHMS

// Search an array linearly, does not need to be sorted
int linear_array_search(int array[], int len, int query){
  for(int i=0; i<len; i++){
    if(array[i] == query ){
      return 1;
    }
  }
  return 0;
}


// Search a linked list linearly, does not need to be sorted
int linkedlist_search(list_t *list, int len, int query){
  for(node_t *n=list->head; n!=NULL; n=n->right){
    int data = n->data;
    if(data == query){
      return 1;
    }
  }
  return 0;
}

// Search sorted array using binary search
int binary_array_search(int array[], int len, int query){
  int left=0, right=len-1;
  int mid;
  while(left <= right){
    mid = (left+right)/2;
    if(query == array[mid]){
      return 1;
    }
    else if(query < array[mid]){
      right = mid-1;
    }
    else{
      left = mid+1;
    }
  }
  return 0;
}

// Search a binary search tree
int binary_tree_search(bst_t *tree, int ignore, int query){
  node_t *node = tree->root;
  while(node != NULL){
    int data = node->data;
    if(query < data){
      node = node->left;
    }
    else if(query > data){
      node =node->right;
    }
    else{
      return 1;
    }
  }
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// RANDOM NUMBER GENERATION UTILITY

// state of the random number generator for phase09 
unsigned long state = 1;

// generate a random integer
unsigned int pb_rand() {
  state = state * 1103515245 + 12345;
  return (unsigned int)(state/65536) % 32768;
}

// set seed for pb_rand()
void pb_srand(unsigned long seed){
  state = seed;
}


////////////////////////////////////////////////////////////////////////////////
// SETUP FUNCTIONS

// allocate an array with elements 0, 2, 4, ...
int *make_evens_array(int len){
  int *array = malloc(sizeof(int)*len);
  for(int i=0; i<len; i++){
    array[i] = i*2;
  }
  return array;
}


// allocate a linked list with data elements 0, 2, 4, ...
list_t *make_evens_list(int len){
  node_t **arr = malloc(sizeof(node_t*)*len);
  for(int i=0; i<len; i++){
    int *gap = malloc(1024);      // create gaps in malloc'd memory
    arr[i] = malloc(sizeof(node_t));
    free(gap);
  }

  int rounds = len * 100;
  // scramble the array so that the node memory locations are not
  // necessarily sequential. Simulates behavior of general
  // implementation when the mallocs may not all happen at once.
  for(int i=0; i<rounds; i++){
    unsigned int idx = pb_rand() % len;
    unsigned int jdx = pb_rand() % len;
    node_t *tmp = arr[idx];
    arr[idx] = arr[jdx];
    arr[jdx] = tmp;
  }

  // first node
  arr[0]->data = 0;
  arr[0]->right = arr[1];
  arr[0]->left  = NULL;

  // set the data as sorted
  for(int i=1; i<len-1; i++){
    arr[i]->data = i*2;
    arr[i]->right = arr[i+1];
    arr[i]->left  = arr[i-1];
  }
  
  // last node
  arr[len-1]->data  = (len-1)*2;
  arr[len-1]->right = NULL;
  arr[len-1]->left  = arr[len-2];

  list_t *list = malloc(sizeof(list_t));
  list->size = len;
  list->head = arr[0];
  free(arr);                                  // don't need array of pointers: in tree now

  return list;
}


// Create a binary search tree with data elements 0,2,4,... that is
// well-balanced
bst_t *make_evens_tree(int len){
  node_t **arr = malloc(sizeof(node_t*)*len);
  for(int i=0; i<len; i++){
    int *gap = malloc(1024);      // create gaps in malloc'd memory
    arr[i] = malloc(sizeof(node_t));
    free(gap);
  }

  int rounds = len * 100;
  // scramble the array so that the node memory locations are not
  // necessarily sequential. Simulates behavior of general
  // implementation when the mallocs may not all happen at once.
  for(int i=0; i<rounds; i++){
    unsigned int idx = pb_rand() % len;
    unsigned int jdx = pb_rand() % len;
    node_t *tmp = arr[idx];
    arr[idx] = arr[jdx];
    arr[jdx] = tmp;
  }

  // set the data as sorted
  for(int i=0; i<len; i++){
    arr[i]->data = i*2;
    arr[i]->left  = NULL;
    arr[i]->right = NULL;

  }

  node_t *root = tree_merge(arr, 0, len-1);   // merge the nodes into a tree
  free(arr);                                  // don't need array of pointers: in tree now

  bst_t *tree = malloc(sizeof(bst_t));
  tree->size = len;
  tree->root = root;

  return tree;
}


// Recursively merge the nodes in a sorted array of nodes into a
// balanced binary search tree
node_t *tree_merge(node_t *arr[], int lo, int hi){
  if(lo == hi){                 // 1 node remaining
    return arr[lo];             // return it
  }

  int mid = (lo+hi)/2;
  if(mid == lo){                // 2 nodes remaining
    arr[lo]->right = arr[hi]; // make left root, right child
    return arr[lo];
  }

  // recursive case
  node_t *root  = arr[mid];
  root->left  = tree_merge(arr, lo, mid-1);
  root->right = tree_merge(arr, mid+1, hi);
  return root;
}


////////////////////////////////////////////////////////////////////////////////
// CLEANUP FUNCTIONS

// use free() for arrays

// Free a linked list
void list_free(list_t *list){
  node_t *cur=list->head;
  for(int i=0; i < list->size; i++){
    node_t *n = cur;
    cur = cur->right;
    free(n);
  }
  free(list);
}
  

// Eliminate all nodes in the tree setting its contents empty. Uses
// recursive node_remove_all() function to free memory for all nodes.
void bst_free(bst_t *tree){
  node_remove_all(tree->root);
  free(tree);
  return;
}

// Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. This requires a post-order
// traversal: visit left tree, visit right tree, then free the cur
// node.
void node_remove_all(node_t *cur){
  if(cur == NULL){
    return;
  }
  node_remove_all(cur->left);
  node_remove_all(cur->right);
  free(cur);
  return;
}


