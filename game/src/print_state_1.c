#include "game.h"

void print_state_1(player_t *player){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_cards(player->out, stacks[i].cards, stacks[i].size, -1);
  }
  fprintf(player->out, "\n");
  print_cards(player->out, player->stack.cards, player->stack.size, -1);
  for(i = 0; i < player->stack.size; i++){
    fprintf(player->out, "-%c- ", 'A' + i);
  }
}
