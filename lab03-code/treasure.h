#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int row, col;                 // position of treasure
  char description[128];        // string describing treasure
} treasureloc_t;

typedef struct {
  int height, width;            // overall size of map
  int ntreasures;               // length of locations array
  treasureloc_t *locations;     // array of locations
} treasuremap_t;


void treasuremap_print(treasuremap_t *tm);
treasuremap_t *treasuremap_load(char *file_name);
void treasuremap_free(treasuremap_t *tmap);

