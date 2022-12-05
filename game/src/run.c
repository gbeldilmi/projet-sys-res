#include "game.h"

void run(void){
  pthread_t threads[num_players];
  int i, r, chosen[num_players], order[num_players];
  r = 0;
  while(!r){
    if(players[0].stack.size == 0){
      deal_cards();
      fprintf(stderr, "Dealing cards\n");
      debug();
    }
    for(i = 0; i < num_players; i++){
      pthread_create(&threads[i], NULL, (void *)play_1, (void *)&players[i]);
    }
    for(i = 0; i < num_players; i++){
      pthread_join(threads[i], (void **)&chosen[i]);
    }
    sort_cards(chosen, order);
    for(i = 0; i < num_players && !r; i++){
      play_2(&players[order[i]], chosen[order[i]]);
      r = game_is_ended();
    }
  }
  podium();
}
