#include "game.h"

void podium(void){
  FILE *out;
  int i, j, order[num_players];
  for(i = 0; i < num_players; i++){
    order[i] = i;
  }
  for(i = 0; i < num_players; i++){
    for(j = i + 1; j < num_players; j++){
      if(players[order[i]].score < players[order[j]].score){
        order[i] += order[j];
        order[j] = order[i] - order[j];
        order[i] -= order[j];
      }
    }
  }
  for(i = 0; i < num_players; i++){
    if((out = players[order[i]].out)){
      for(j = 0; j < num_players; j++){
        fprintf(out, "Player %d: %d heads", order[j] + 1, players[order[j]].score);
      }
      fprintf(out, "You are in position %d of %d!\n", i + 1, num_players);
      fprintf(out, "Your score is %d!\n", players[order[i]].score);
    }
  }
}
