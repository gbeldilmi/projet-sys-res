#include "game.h"

static int score_1(stack_t *stack, card_t card){
  int s;
  if(stack->size == MAX_STACK_SIZE || card.value < stack->cards[stack->size - 1].value){
    // If the stack is full or the card value is smaller than the last card of the stack
    return -1;
  }
  // If the bot can put the card on the stack 
  s = NUM_CARDS - (card.value - stack->cards[stack->size - 1].value);
  s *= stack->size;
  return s;
}

static int score_2(stack_t *stack){
  int i, s;
  // Get the sum of the heads of the stack
  for(i = s = 0; i < stack->size; i++){
    s += stack->cards[i].heads;
  }
  return s;
}

int play_bot_2(player_t *player){
  int i, j, s[NUM_STACKS];
  // Calculate scores for each stack and choose the best
  for(i = 0; i < NUM_STACKS; i++){
    s[i] = score_1(&stacks[i], player->stack.cards[player->stack.size]);
  }
  // Get the best score (highest)
  j = 0;
  for(i = 1; i < NUM_STACKS; i++){
    if(s[i] > s[j]){
      j = i;
    }
  }
  // If the bot can play the card without getting a penalty
  if (s[j] != -1){
    return j;
  }
  // Else, get the lowest penalty
  for(i = 0; i < NUM_STACKS; i++){
    s[i] = score_2(&stacks[i]);
  }
  // Get the best score (lowest)
  j = 0;
  for(i = 1; i < NUM_STACKS; i++){
    if(s[i] < s[j]){
      j = i;
    }
  }
  return j;
}
