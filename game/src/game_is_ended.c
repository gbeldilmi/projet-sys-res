#include "game.h"

int game_is_ended(void){
  int i;
  for(i = 0; i < num_players; i++){
    if(players[i].score >= MAX_SCORE){
      return 1;
    }
  }
  return 0;
}
