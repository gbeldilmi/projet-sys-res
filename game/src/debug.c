#include "game.h"

/******************************************************************************
 * Print every card of a stack.                                               *
 * -> stack_t *s :                                                            *
 *      stack to print.                                                       *
 * <- void                                                                    *
 ******************************************************************************/
static void debug_cards(stack_t * s){
  int i;
  for(i = 0; i < s->size; i++){
    fprintf(stderr, "%d(%d) ", s->cards[i].value, s->cards[i].heads);
  }
}

/******************************************************************************
 * Print every information about a player.                                    *
 * -> player_t *p :                                                           *
 *      player to print.                                                      *
 * <- void                                                                    *
 ******************************************************************************/
static void debug_player(player_t *p){
  fprintf(stderr, "Player:\n\tid: %d\n\tscore: %d\n\tin: %s\n\tout: %s\n\t"
      "stack:\n\t\tsize: %d\n\t\tcards: %s\n", p->id, p->score, (p->in) ?
      "yes" : "no", (p->out) ? "yes" : "no", p->stack.size, (p->stack.cards) ?
      "yes" : "no");
}

/******************************************************************************
 * Print every stack.                                                         *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
static void debug_stacks(void){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    fprintf(stderr, "Stack %d:\n\tsize: %d\n\tcards: ", i, stacks[i].size);
    debug_cards(&stacks[i]);
    fprintf(stderr, "\n");
  }
}

/******************************************************************************
 * Print detailed informations about the game.                                *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
void debug(void){
  int i;
  fprintf(stderr, "Game:\n\tplayers: %d\n\tstacks: %d\n\tcards: %d\n",
      num_players, NUM_STACKS, NUM_CARDS);
  debug_stacks();
  for(i = 0; i < num_players; i++){
    debug_player(&players[i]);
  }
}
