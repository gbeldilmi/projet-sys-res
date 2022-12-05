#include "game.h"

static void debug_cards(stack_t * s){
  int i;
  for(i = 0; i < s->size; i++){
    fprintf(stderr, "%d(%d) ", s->cards[i].value, s->cards[i].heads);
  }
}

static void debug_player(player_t *p){
  fprintf(stderr, "Player:\n\tid: %d\n\tscore: %d\n\tin: ", p->id, p->score);
  if(p->in){
    fprintf(stderr, "yes");
  }else{
    fprintf(stderr, "no");
  }
  fprintf(stderr, "\n\tout: ");
  if(p->out){
    fprintf(stderr, "yes");
  }else{
    fprintf(stderr, "no");
  }
  fprintf(stderr, "\n\tstack:\n\t\tsize: %d\n\t\tcards: ", p->stack.size);
  if(p->stack.cards){
    debug_cards(&p->stack);
  }else{
    fprintf(stderr, "no");
  }
  fprintf(stderr, "\n");
}

static void debug_stacks(){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    fprintf(stderr, "Stack %d:\n\tsize: %d\n\tcards: ", i, stacks[i].size);
    debug_cards(&stacks[i]);
    fprintf(stderr, "\n");
  }
}

void debug(void){
  int i;
  fprintf(stderr, "Game:\n\tplayers: %d\n\tstacks: %d\n\tcards: %d\n", num_players, NUM_STACKS, NUM_CARDS);
  debug_stacks();
  for(i = 0; i < num_players; i++){
    debug_player(&players[i]);
  }
}
