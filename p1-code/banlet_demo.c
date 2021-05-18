// banlet_demo.c: shows some syntax patterns to access parts of the
// font_t and glyph_t data in banlet.

#include "banlet.h"

int main(int argc, char *argv[]){
  font_t *font = &font_standard; // builtin font
  printf("Standard font has %d rows\n",
         font->height);

  int codepoint = 'A';          // ASCII code 65
  printf("Width of codepoint %d in font is: %d\n",
         codepoint,
         font->glyphs[codepoint].width);

  printf("Row 0 of glyph is: %s\n",
         font->glyphs[codepoint].data[0]);

  printf("Row 1 of glyph is: %s\n",
         font->glyphs[codepoint].data[1]);

  printf("Row 2 of glyph is: %s\n",
         font->glyphs[codepoint].data[2]);
  return 0;
}
