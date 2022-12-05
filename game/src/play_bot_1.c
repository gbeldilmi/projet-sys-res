#include "game.h"

static int f_head(stack_t *stack){
  int i, s;
  // more there are heads in the stack, more the score is high
  for(i = 0, s = 0; i < stack->size; i++){
    s += stack->cards[i].heads;
  }
  return s * 10;
}

static int f_number(stack_t *stack, int id_card){
  int s;
  if(stack->size == 0){
    // if the stack is empty
    s = 0;
  }else{
    s = stack->cards[id_card].value - stack->cards[stack->size - 1].value;
    s *= stack->size;
  }
  return s;
}

static int score(player_t *player, stack_t *stack, int id_card){
  if(player->stack.cards[id_card].value < stack->cards[stack->size - 1].value
      || stack->size == MAX_STACK_SIZE){
    return f_head(stack);
  } else {
    return f_number(stack, id_card);
  }
}

int play_bot_1(player_t *player){
  int i, j, bs, bc, plays[player->stack.size][NUM_STACKS];
  // plays[id_card][id_stack] = score
  for(i = 0; i < player->stack.size; i++){
    for(j = 0; j < NUM_STACKS; j++){
      plays[i][j] = score(player, &stacks[i], j);
    }
  }
  // Eventually make an average or median of scores for each card
  //////////////////////////////////////////////////////////////////////////////
  // Choose best play (lowest score)
  bs = 99999;
  bc = -1;
  for(i = 0; i < player->stack.size; i++){
    for(j = 0; j < NUM_STACKS; j++){
      if(plays[i][j] < bs){
        bs = plays[i][j];
        bc = i;
      }
    }
  }
  return bc;
}
