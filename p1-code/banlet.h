// Header for deltas problem
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BANLET_H
#define BANLET_H 1

#define MAX_HEIGHT 10                // max height in chars for glyphs
#define MAX_WIDTH  20                // max width  in chars for glyphs
#define NUM_ASCII_GLYPHS 128         // number of glyphs in a font

typedef struct {                     // type associated with individual glyphs
  int codepoint;                     // ASCII codepoint, e.g. 65 for 'A' etc.
  int width;                         // width of the glyph
  char data[MAX_HEIGHT][MAX_WIDTH];  // 2D array of data for glyph, rows should be \0-terminated strings
} glyph_t;

typedef struct {                     // type associated with a font
  int height;                        // height of all glyphs in the font
  glyph_t *glyphs;                   // array of glyphs with length NUM_ASCII_GLYPHS for each ASCII codepoint
} font_t;

extern font_t font_standard;         // font defined in banlet_font_standard.c

// banlet_funcs.c
void string_replace_char(char *str, char old, char new);
int count_linebreaks(char *msg);
int *find_linebreaks(char *msg, int *nbreaks);
void print_fontified(char *msg, int length, font_t *font);
void print_fontified_linebreaks(char *msg, font_t *font);
void glyph_init(glyph_t *glyph, int codepoint);
font_t *font_load(char *filename);
void font_free(font_t *font);

#endif
