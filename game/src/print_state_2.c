#include "game.h"

void print_state_2(player_t *player){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_cards(player->out, stacks[i].cards, stacks[i].size, i);
  }
  fprintf(player->out, "\n");
  print_cards(player->out, player->stack.cards + player->stack.size, 1, -1);
}
