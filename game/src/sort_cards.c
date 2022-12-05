#include "game.h"

void sort_cards(int *chosen, int *order){
  stack_t *ps;
  card_t c;
  int i, j;
  for(i = 0; i < num_players; i++){
    ps = &players[i].stack;
    c = ps->cards[chosen[i]];
    ps->cards[chosen[i]] = ps->cards[ps->size - 1];
    ps->cards[ps->size - 1] = c;
    ps->size--;
  }
  // get the order of the players who will play by the value of the card (lowest first)
  for(i = 0; i < num_players; i++){
    order[i] = i;
  }
  for(i = 0; i < num_players; i++){
    for(j = i + 1; j < num_players; j++){
      if(players[order[i]].stack.cards[players[order[i]].stack.size].value
          > players[order[j]].stack.cards[players[order[j]].stack.size].value){
        order[i] += order[j];
        order[j] = order[i] - order[j];
        order[i] -= order[j];
      }
    }
  }
}
