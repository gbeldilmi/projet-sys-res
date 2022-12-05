#include "game.h"

int read_input(FILE *in){
  int i, c;
  do
  {
    i = fgetc(in);
  }while(isspace(i));
  do{
    c = fgetc(in);
    if(c != '\n'){
      i = c;
    }
  }while(c != '\n');
  return i;
}
