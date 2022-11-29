#include "game.h"

static int *chosen_cards;

static int win(){
  int i;
  for(i = 0; i < num_players; i++){
    if(players[i]->score >= MAX_SCORE){
      return 1;
    }
  }
  return 0;
}

static void play1(void *arg){
  int id_player;
  id_player = (int)arg;
  chosen_cards[id_player] = (players[id_player]->channel == NULL) ? bot1(id_player) : human1(id_player);
}

void run(){
  pthread_t *threads;
  int i;
  threads = (pthread_t *)malloc(num_players * sizeof(pthread_t));
  chosen_cards = (int *)malloc(num_players * sizeof(int));
  while(!win()){
    if(players[0]->stack->size == 0){
      deal();
    }
    for(i = 0; i < num_players; i++){
      pthread_create(&threads[i], NULL, (void *)play1, (void *)i);
    }
    for(i = 0; i < num_players; i++){
      pthread_join(threads[i], NULL);
    }
    
    // play round

    // print cards state
    
    // ask cards to players

    // print cards state

    // play cards

    // update scores

    // print cards state

  }
  free(threads);
  free(chosen_cards);
}
