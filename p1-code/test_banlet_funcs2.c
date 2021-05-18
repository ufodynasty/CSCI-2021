#include "banlet.h"

#define PRINT_TEST sprintf(sysbuf,"awk 'NR==(%d+1){P=1;print \"{\"} P==1 && /ENDTEST/{P=0; print \"}\"} P==1{print}' %s", __LINE__, __FILE__); \
                   system(sysbuf);

void print_int_array(int *arr, int length){
  printf("[");
  for(int i=0; i<length-1; i++){
    printf("%2d, ",arr[i]);
  }
  if(length > 0){
    printf("%2d",arr[length-1]);
  }
  printf("]");
}

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];


  if(0){}
  else if( strcmp( test_name, "print_fontified_linebreak_1" )==0 ) {
    PRINT_TEST;
    // Tests print_fontified_linebreak function with builtin font_standard
    char *string;
    string =
"apple\n\
B@N@N@\n\
Carr0^";
    print_fontified_linebreaks(string, &font_standard);
  } // ENDTEST

  else if( strcmp( test_name, "print_fontified_linebreak_2" )==0 ) {
    PRINT_TEST;
    // Tests print_fontified_linebreak function with builtin font_standard
    char *string;
    string =
"The quick brown fox\n\
jumps OVER the lazy\n\
dog.";
    print_fontified_linebreaks(string, &font_standard);
  } // ENDTEST

  else if( strcmp( test_name, "print_fontified_linebreak_3" )==0 ) {
    PRINT_TEST;
    // Tests print_fontified_linebreak function with builtin font_standard
    char *string;
    string =
" !\"#$%&'()\n\
*+,-./0123\n\
456789:;<=\n\
>?@ABCDEFG\n\
HIJKLMNOPQ\n\
RSTUVWXYZ[\n\
\\]^_`abcde\n\
fghijklmno\n\
pqrstuvwxy\n\
z{|}~";
    print_fontified_linebreaks(string, &font_standard);
  } // ENDTEST

  else if( strcmp( test_name, "load_font_1" )==0 ) {
    PRINT_TEST;
    // Tests load_font() on the font_standard.txt file
    // ALSO checks that free_font() function deallocates.
    char *font_file = "data/font_standard.txt";
    font_t *font = font_load(font_file);
    char *string =
" !\"#$%&'()\n\
*+,-./0123\n\
456789:;<=\n\
>?@ABCDEFG\n\
HIJKLMNOPQ\n\
RSTUVWXYZ[\n\
\\]^_`abcde\n\
fghijklmno\n\
pqrstuvwxy\n\
z{|}~";
    print_fontified_linebreaks(string, font);
    font_free(font);
  } // ENDTEST

  else if( strcmp( test_name, "load_font_2" )==0 ) {
    PRINT_TEST;
    // Tests load_font() on the font_mini.txt file
    // ALSO checks that free_font() function deallocates.
    char *font_file = "data/font_mini.txt";
    font_t *font = font_load(font_file);
    char *string =
" !\"#$%&'()\n\
*+,-./0123\n\
456789:;<=\n\
>?@ABCDEFG\n\
HIJKLMNOPQ\n\
RSTUVWXYZ[\n\
\\]^_`abcde\n\
fghijklmno\n\
pqrstuvwxy\n\
z{|}~";
    print_fontified_linebreaks(string, font);
    font_free(font);
  } // ENDTEST

  else if( strcmp( test_name, "load_font_3" )==0 ) {
    PRINT_TEST;
    // Tests load_font() on the font_capsonly.txt file.
    // This font does not have all ASCII codepoints defined
    // so some of the glyphs will appear as defaults / XXXs.
    char *font_file = "data/font_capsonly.txt";
    font_t *font = font_load(font_file);
    char *string =
" ! \" # $ % & ' ( )\n\
+ * , - . / 0 1 2 3\n\
4 5 6 7 8 9 : ; < =\n\
> ? @ A B C D E F G\n\
H I J K L M N O P Q\n\
R S T U V W X Y Z [\n\
\\ ] ^ _ ` a b c d e\n\
f g h i j k l m n o\n\
p q r s t u v w x y\n\
z { | } ~";
    print_fontified_linebreaks(string, font);
    font_free(font);
  } // ENDTEST

  else if( strcmp( test_name, "load_font_4" )==0 ) {
    PRINT_TEST;
    // Tests taht load_font() returns NULL if font is not found
    char *font_file = "data/no_such_font.txt.txt";
    font_t *font = font_load(font_file);
    if(font != NULL){
      printf("What the deuce just happened?\n");
    }
    else{
      printf("NULL returned correctly\n");
    }
  } // ENDTEST

  else{
    printf("No test named '%s' found\n",test_name);
    return 1;
  }
  return 0;
}
