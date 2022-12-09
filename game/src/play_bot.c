#include "game.h"

/******************************************************************************
 * Get the score of a stack in function of the number of heads in it.         *
 * -> stack_t *stack :                                                        *
 *      stack to get the score.                                               *
 * <- int :                                                                   *
 *      score of the stack.                                                   *
 ******************************************************************************/
static int f_head(stack_t *stack){
  int i, s;
  // More the number of heads is high, more the score is high
  for(i = 0, s = 0; i < stack->size; i++){
    s += stack->cards[i].heads;
  }
  return s * NUM_CARDS;
}

/******************************************************************************
 * Get the score of a stack in function of the value of the last card in it.  *
 * -> stack_t *stack :                                                        *
 *      stack to get the score.                                               *
 * -> int id_card :                                                           *
 *      id of the card to add to the stack.                                   *
 * <- int :                                                                   *
 *      score of the stack.                                                   *
 ******************************************************************************/
static int f_number(stack_t *stack, int id_card){
  // More the difference between the value of the last card in the stack and
  // the value of the card to add is high, more the score is high.
  return stack->cards[id_card].value - stack->cards[stack->size - 1].value;
}

/******************************************************************************
 * Calculate the score of a stack
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * -> stack_t *stack :                                                        *
 *      stack to get the score.                                               *
 * -> int id_card :                                                           *
 *      id of the card to add to the stack.                                   *
 * <- int :                                                                   *
 *      score of the stack.                                                   *
 ******************************************************************************/
static int score(player_t *player, stack_t *stack, int id_card){
  if(player->stack.cards[id_card].value < stack->cards[stack->size - 1].value 
      || stack->size == MAX_STACK_SIZE){
    // If the card can't fit in the stack.
    return f_head(stack);
  } else {
    // If the card can fit in the stack.
    return f_number(stack, id_card);
  }
}

/******************************************************************************
 * Make the bot choose a card to play.                                        *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- int :                                                                   *
 *      id of the stack chosen by the player.                                 *
 ******************************************************************************/
int play_bot_1(player_t *player){
  int i, j, bs, bc, plays[player->stack.size][NUM_STACKS];
  // Calculate the score of each play : plays[id_card][id_stack] = score.
  for(i = 0; i < player->stack.size; i++){
    for(j = 0; j < NUM_STACKS; j++){
      plays[i][j] = score(player, &stacks[j], i);
    }
  }
  // Choose best play (lowest score).
  bs = plays[0][0];
  bc = 0;
  for(i = 0; i < player->stack.size; i++){
    for(j = (i == 0); j < NUM_STACKS; j++){
      if(plays[i][j] < bs){
        bs = plays[i][j];
        bc = i;
      }
    }
  }
  return bc;
}

/******************************************************************************
 * Make the bot choose a stack to play.                                       *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- int :                                                                   *
 *      id of the stack chosen by the player.                                 *
 ******************************************************************************/
int play_bot_2(player_t *player){
  int i, bs, bc, plays[NUM_STACKS];
  // Calculate the score of each play : plays[id_stack] = score.
  for(i = 0; i < NUM_STACKS; i++){
    plays[i] = score(player, &stacks[i], player->stack.size);
  }
  // Choose best play (lowest score).
  bs = plays[0];
  bc = 0;
  for(i = 1; i < NUM_STACKS; i++){
    if(plays[i] < bs){
      bs = plays[i];
      bc = i;
    }
  }
  return bc;
}
