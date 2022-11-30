#include "game.h"

static player_t *player;

static int score1(card_t *card, int id_stack){
  stack_t *stack;
  int s;
  stack = stacks[id_stack];
  if(stack->size == MAX_STACK_SIZE || card->value < stack->cards[stack->size - 1].value){
    // If the stack is full or the card value is smaller than the last card of the stack
    s = -1;
  }else{
    // If the bot can put the card on the stack 
    s = NUM_CARDS - (card->value - stack->cards[stack->size - 1].value);
    s *= stack->size;
  }
  return s;
}

static int score2(card_t *card, int id_stack){
  stack_t *stack;
  int i, s;
  stack = stacks[id_stack];
  // Get the sum of the heads of the stack
  for(i = 0, s = 0; i < stack->size; i++){
    s += stack->cards[i].heads;
  }
  return s;
}

int bot2(int id_player, card_t *card){
  int i, j, *s;
  player = players[id_player];
  s = malloc(sizeof(int) * NUM_STACKS);
  // Calculate scores for each stack and choose the best
  for(i = 0; i < NUM_STACKS; i++){
    s[i] = score1(card, i);
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
    free(s);
    return j;
  }
  // Else, get the lowest penalty
  for(i = 0; i < NUM_STACKS; i++){
    s[i] = score2(card, i);
  }
  // Get the best score (lowest)
  j = 0;
  for(i = 1; i < NUM_STACKS; i++){
    if(s[i] < s[j]){
      j = i;
    }
  }
  free(s);
  return j;
}
