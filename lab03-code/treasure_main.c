// treasure_main.c: reads treasure map files and prints their
// contents.  TODO sections need to be completed. See the treasure.h
// file for the fields of the treasure_t struct.

#include "treasure.h"

// PROVIDED AND COMPLETE: Main routine which accepts a command line
// argument which is a treasure map file to open and print
int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <treasure_file.tm>\n",argv[0]);
    return 1;
  }

  char *file_name = argv[1];
  printf("Loading treasure map from file '%s'\n", file_name);

  treasuremap_t *tmap = treasuremap_load(file_name);
  if(tmap == NULL){
    printf("Loading failed, bailing out\n");
    return 1;
  }

  printf("\n");
  treasuremap_print(tmap);

  printf("\n");
  printf("Deallocating map\n");
  treasuremap_free(tmap);

  return 0;
}

// REQUIRED: Opens `file_name` and parse its contents to construct a
// treasuremap_t.  Files the following format (with no # commenting)
// 
// 7 5 3                # rows cols ntreasures
// 0 2 Death_Crystals   # treasure at row 0, col 2, description given
// 4 1 Mega_Seeds       # treasure at row 4, col 1, description given
// 6 3 Flurbo_stash     # treasure at row 6, col 3, description given
//
// Allocates heap space for the treasuremap_t and, after reading the
// height/width from the file, reads number of treasures and allocates
// an array of treasureloc_t structs for subsequent file
// contents. Iterates through the file reading data into the
// structs. Closes the file and returns a pointer to the treasuremap_t
// struct.
//
// NOTE: This code is incomplete and requires the TODO items mentioned
// in comments to be completed.
treasuremap_t *treasuremap_load(char *file_name){
  printf("Reading map from file '%s'\n",file_name);

  FILE *file_handle = fopen(file_name, "r");

  // TODO: Check if the file fails to open and return NULL if so.
  if(file_handle == NULL){
    printf("Couldn't open file '%s', returning NULL\n",
           file_name);

    // TODO: return failure value
    return NULL;
  }

  printf("Allocating map struct\n");

  // TODO: Determine byte size for treasuremap_t struct
  treasuremap_t *tmap = malloc(sizeof(treasuremap_t));

  fscanf(file_handle,"%d %d", &tmap->height, &tmap->width);
  printf("Map is %d by %d\n", tmap->height, tmap->width);

  // TODO: read in the number of treasures
  fscanf(file_handle,"%d", &tmap->ntreasures);

  // TODO: print message like '4 treasures on the map'
  printf("%d treasures on the map\n", tmap->ntreasures);


  printf("Allocating array of treasure locations\n");

  // TODO: allocate array of treasure
  tmap->locations = malloc(tmap->ntreasures * sizeof(treasureloc_t));

  printf("Reading treasures\n");

  // Read in each treasures from the file
  for(int i=0; i < tmap->ntreasures; i++){

    fscanf(file_handle, "%d", &tmap->locations[i].row);

    // TODO: read in the column location for this treasure
    fscanf(file_handle, "%d", &tmap->locations[i].col);

    // TODO: read in the description for this treasure
    fscanf(file_handle, "%s", tmap->locations[i].description);

    printf("Treasure at %d %d called '%s'\n",
           tmap->locations[i].row,
           tmap->locations[i].col,
           tmap->locations[i].description);
  }    

  printf("Completed file, closing\n");
  fclose(file_handle);

  printf("Returning pointer to heap-allocated treasure_t\n");
  return tmap;
}

// REQUIRED: De-allocate the space assoated with a treasuremap_t.
// free()'s the `map` field and then free()'s the struct itself.
// 
// NOTE: This code is incomplete and requires the TODO items mentioned
// in comments to be completed.
void treasuremap_free(treasuremap_t *tmap){
  // De-allocate locations array
  free(tmap->locations);

  // TODO: the tmap struct
  free(tmap);

  return;
}


// PROVIDED AND COMPLETE: Print out the treasure map; uses local
// printspace[][] array from the header which is unsafe but simpler to
// implement for small maps than dynamic allocation.
void treasuremap_print(treasuremap_t *tm){
  char printspace[128][128] = {};

  printf("==TREASURE MAP==\n");

  for(int i=0; i<tm->height; i++){
    int j;
    for(j=0; j<tm->width; j++){
      printspace[i][j] = '.';
    }
    printspace[i][j] = '\0';
  }
  
  for(int i=0; i<tm->ntreasures; i++){
    int row = tm->locations[i].row;
    int col = tm->locations[i].col;
    printspace[row][col] = 'A' + i;
  }
      
  for(int i=0; i<tm->height; i++){
    printf("%s\n",printspace[i]);
  }

  printf("================\n");

  for(int i=0; i<tm->ntreasures; i++){
    printf("%c: %s\n",'A'+i,tm->locations[i].description);
  }

  return;
}

