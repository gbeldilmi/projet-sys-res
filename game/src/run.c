#include "game.h"

static int win(){
  int i;
  for(i = 0; i < num_players; i++){
    if(players[i].score >= MAX_SCORE){
      return 1;
    }
  }
  return 0;
}

static int play1(void *arg){
  player_t *player;
  player = (player_t *)arg;
  return (player->out == NULL) ? bot1(player) : human1(player);
}

static void sort_cards(int *chosen, int *order){
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

static void play2(player_t *player, int id_card){
  stack_t *cs;
  int i, sh;
  cs = &stacks[(player->out == NULL) ? bot2(player) : human2(player)];
  if(cs->size < MAX_STACK_SIZE){
    cs->cards[cs->size] = player->stack.cards[id_card];
    cs->size++;
  }else{
    sh = 0;
    for(i = 0; i < cs->size; i++){
      sh += cs->cards[i].heads;
    }
    player->score += sh;
    cs->cards[0] = player->stack.cards[id_card];
    cs->size = 1;
    if(player->out){
      fprintf(player->out, "You got %d heads!\n", sh);
    }
  }
}

static void podium(int *order){
  FILE *out;
  int i, j;
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

void run(void){
  pthread_t threads[num_players];
  int i, r, chosen[num_players], order[num_players];
  r = 0;
  while(!r){
    if(players[0].stack.size == 0){
      deal();
    }
    for(i = 0; i < num_players; i++){
      pthread_create(&threads[i], NULL, (void *)play1, (void *)&players[i]);
    }
    for(i = 0; i < num_players; i++){
      pthread_join(threads[i], (void **)&chosen[i]);
    }
    sort_cards(chosen, order);
    for(i = 0; i < num_players && !r; i++){
      play2(&players[order[i]], chosen[order[i]]);
      r = win();
    }
  }
  podium(order);
}
