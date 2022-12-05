#include "game.h"

int choose_stack(player_t *player){
  int c;
  fprintf(player->out, "Choose a stack: ");
  c = -1;
  while(c < 0 || c >= NUM_STACKS){
    c = read_input(player->in);
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      fprintf(player->out, "Invalid stack. Choose again: ");
      c = -1;
    }
  }
  fprintf(player->out, "Waiting for others players...\n");
  return c;
}
