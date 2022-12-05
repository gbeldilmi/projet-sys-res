#include "game.h"

void bye(void){
  int i;
  for(i = 0; i < num_players; i++){
    if(players[i].in != NULL){
      fclose(players[i].in);
    }
    if(players[i].out != NULL){
      fclose(players[i].out);
    }
    free(players[i].stack.cards);
  }
  free(players);
  for(i = 0; i < NUM_STACKS; i++){
    free(stacks[i].cards);
  }
  free(stacks);
}
