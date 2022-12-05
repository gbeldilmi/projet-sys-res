#include "game.h"

void run(void){
  pthread_t threads[num_players];
  int i, r, order[num_players];
  r = 0;
  while(!r){
    if(players[0].stack.size == 0){
      deal_cards();
    }
    for(i = 0; i < num_players; i++){
      pthread_create(&threads[i], NULL, (void *)play_1, (void *)&players[i]);
    }
    sleep(5);
    for(i = 0; i < num_players; i++){
      pthread_join(threads[i], NULL);
    }
    get_order(order);
    for(i = 0; i < num_players && !r; i++){
      play_2(&players[order[i]]);
      r = game_is_ended();
    }
  }
  podium();
}
