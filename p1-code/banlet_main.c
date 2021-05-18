// PROVIDED: Makes use of functions provided in banlet_funcs.c to
// print messages in a "fontified" fashion. This program should not
// require modification.
#include "banlet.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s '<message>'\n",argv[0]);
    printf("       %s <fontfile> '<message>'\n",argv[0]);
    printf("Note: When passing embedded \n characters, use the syntax $'msg' as in\n");
    printf("        %s $'HELLO\nWORLD\n!!!'\n",argv[0]);
    printf("      as this properly embeds newlines");
    return 1;
  }

  char *msg = argv[1];               // default to message being first argument
  font_t *font = &font_standard;     // default to built in standard font

  if(argc == 3){                     // if 3 arguments provided
    font = font_load(argv[1]);       // load a font
    if(font == NULL){
      printf("ERROR: Couldn't open font file\n");
      return 1;
    }
    msg = argv[2];                   // message is 3rd argument
  }

  print_fontified_linebreaks(msg, font);

  if(font != &font_standard){
    font_free(font);
  }

  return 0;
}
    
