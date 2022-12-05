#include "game.h"

void get_order(int *order){
  int i, j;
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
