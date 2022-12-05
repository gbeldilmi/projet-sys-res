#include "game.h"

void play_2(player_t *player){
  stack_t *cs;
  int i, sh;
  cs = &stacks[(player->out == NULL) ? play_bot_2(player) : play_human_2(player)];
  if(cs->size < MAX_STACK_SIZE){
    cs->cards[cs->size] = player->stack.cards[player->stack.size];
    cs->size++;
  }else{
    sh = 0;
    for(i = 0; i < cs->size; i++){
      sh += cs->cards[i].heads;
    }
    player->score += sh;
    cs->cards[0] = player->stack.cards[player->stack.size];
    cs->size = 1;
    if(player->out){
      fprintf(player->out, "You got %d heads!\n", sh);
    }
  }
}
