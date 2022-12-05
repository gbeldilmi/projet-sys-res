#include "game.h"

int choose_card(player_t *player){
  int c;
  fprintf(player->out, "Choose a card: ");
  c = -1;
  while(c < 0 || c >= player->stack.size){
    c = read_input(player->in);
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      fprintf(player->out, "Invalid card. Choose again: ");
      c = -1;
    }
  }
  fprintf(player->out, "Waiting for others players...\n");
  return c;
}
