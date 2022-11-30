#include "game.h"

static int *chosen_cards, *players_order;

static int win(){
  int i;
  for(i = 0; i < num_players; i++){
    if(players[i].score >= MAX_SCORE){
      return 1;
    }
  }
  return 0;
}

static void play1(void *arg){
  int id_player;
  id_player = *((int *)arg);
  chosen_cards[id_player] = (players[id_player].channel == NULL) ? bot1(id_player) : human1(id_player);
}

static void sort_cards(){
  stack_t *ps;
  card_t a, b;
  int i, j, k;
  for(i = 0; i < num_players; i++){
    ps = players[i].stack;
    a = ps->cards[chosen_cards[i]];
    b = ps->cards[ps->size - 1];
    ps->cards[chosen_cards[i]] = b;
    ps->cards[ps->size - 1] = a;
    ps->size--;
  }
  // get the order of the players who will play by the value of the card (lowest first)
  for(i = 0; i < num_players; i++){
    players_order[i] = i;
  }
  for(i = 0; i < num_players; i++){
    for(j = i + 1; j < num_players; j++){
      if(players[players_order[i]].stack->cards[players[players_order[i]].stack->size].value
          > players[players_order[j]].stack->cards[players[players_order[j]].stack->size].value){
        k = players_order[i];
        players_order[i] = players_order[j];
        players_order[j] = k;
      }
    }
  }
}

static void play2(int id_player, int id_card){
  int cs, i, sh;
  cs = (players[id_player].channel == NULL) ? bot2(id_player) : human2(id_player);
  if(stacks[cs].size < MAX_STACK_SIZE){
    stacks[cs].cards[stacks[cs].size] = players[id_player].stack->cards[id_card];
    stacks[cs].size++;
  }else{
    sh = 0;
    for(i = 0; i < stacks[cs].size; i++){
      sh += stacks[cs].cards[i].heads;
    }
    players[id_player].score += sh;
    stacks[cs].cards[0] = players[id_player].stack->cards[id_card];
    stacks[cs].size = 1;
    if(players[id_player].channel){
      fprintf(players[id_player].channel->out, "You got %d heads!\n", sh);
    }
  }
}

static void podium(){
  FILE *out;
  int i, j, k;
  for(i = 0; i < num_players; i++){
    players_order[i] = i;
  }
  for(i = 0; i < num_players; i++){
    for(j = i + 1; j < num_players; j++){
      if(players[players_order[i]].score < players[players_order[j]].score){
        k = players_order[i];
        players_order[i] = players_order[j];
        players_order[j] = k;
      }
    }
  }
  for(i = 0; i < num_players; i++){
    if(players[players_order[i]].channel){
      out = players[players_order[i]].channel->out;
      for(j = 0; j < num_players; j++){
        fprintf(out, "Player %d: %d heads", players_order[j], players[players_order[j]].score);
      }
      fprintf(out, "You are in position %d of %d!\n", i + 1, num_players);
      fprintf(out, "Your score is %d!\n", players[players_order[i]].score);
    }
  }
}

void run(){
  pthread_t *threads;
  int i, w;
  threads = (pthread_t *)malloc(num_players * sizeof(pthread_t));
  chosen_cards = (int *)malloc(num_players * sizeof(int));
  players_order = (int *)malloc(num_players * sizeof(int));
  w = 0;
  while(!w){
    if(players[0].stack->size == 0){
      deal();
    }
    for(i = 0; i < num_players; i++){
      pthread_create(&threads[i], NULL, (void *)play1, (void *)&i);
    }
    for(i = 0; i < num_players; i++){
      pthread_join(threads[i], NULL);
    }
    sort_cards();
    for(i = 0; i < num_players && !w; i++){
      play2(players_order[i], chosen_cards[players_order[i]]);
      w = win();
    }
  }
  podium();
  free(threads);
  free(chosen_cards);
  free(players_order);
}
