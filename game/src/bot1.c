#include "game.h"

static player_t *player;
static int **plays;

static int f_head(int id_stack){
  int i, s;
  // more there are heads in the stack, more the score is high
  for(i = 0, s = 0; i < stacks[id_stack].size; i++){
    s += stacks[id_stack].cards[i].heads;
  }
  return s * 10;
}

static int f_number(int id_stack, int id_card){
  int s;
  if(stacks[id_stack].size == 0){
    // if the stack is empty
    s = 0;
  }else{
    s = stacks[id_stack].cards[id_card].value - stacks[id_stack].cards[stacks[id_stack].size - 1].value;
    s *= stacks[id_stack].size;
  }
  return s;
}

static int score(int id_card, int id_stack){
  if(player->stack->cards[id_card].value < stacks[id_stack].cards[stacks[id_stack].size - 1].value
      || stacks[id_stack].size == MAX_STACK_SIZE){
    return f_head(id_stack);
  } else {
    return f_number(id_stack, id_card);
  }
}

int bot1(int id_player){
  int i, j, best_score, best_card, best_stack;
  player = &players[id_player];
  // Allocate memory for plays
  // plays[id_card][id_stack] = score
  plays = malloc(player->stack->size * sizeof(int *));
  for(i = 0; i < player->stack->size; i++){
    plays[i] = malloc(NUM_STACKS * sizeof(int));
    for(j = 0; j < NUM_STACKS; j++){
      plays[i][j] = score(i, j);
    }
  }
  // Eventually make an average or median of scores for each card
  //////////////////////////////////////////////////////////////////////////////
  // Choose best play (lowest score)
  best_score = 99999;
  best_card = best_stack = -1;
  for(i = 0; i < player->stack->size; i++){
    for(j = 0; j < NUM_STACKS; j++){
      if(plays[i][j] < best_score){
        best_score = plays[i][j];
        best_card = i;
        best_stack = j;
      }
    }
  }
  // Free memory
  for(i = 0; i < player->stack->size; i++){
    free(plays[i]);
  }
  free(plays);
  return best_card;
}
