#include "game.h"

static int get_heads(int value){
  int heads, tens, units;
  heads = 0;
  tens = value - (value % 10) / 10;
  units = value % 10;
  if(units == 5){
    heads += 2;
  }
  if(units == 0){
    heads += 3;
  }
  if(tens == units){
    heads += 5;
  }
  if(heads == 0){
    heads = 1;
  }
  return heads;
}

static stack_t *new_deck(){
  stack_t *deck;
  int i, j;
  deck = malloc(sizeof(stack_t));
  deck->size = NUM_CARDS;
  deck->cards = malloc(NUM_CARDS * sizeof(card_t));
  for(i = 1; i <= NUM_CARDS; i++){
    deck->cards[i].value = i;
    deck->cards[i].heads = get_heads(i);
  }
  for(i = 0; i < NUM_CARDS; i++){
    j = rand() % NUM_CARDS;
    card_t temp = deck->cards[i];
    deck->cards[i] = deck->cards[j];
    deck->cards[j] = temp;
  }
  return deck;
}

void deal(){
  int i, j;
  stack_t *deck;
  deck = new_deck();
  for(i = 0; i < num_players; i++){
    if(players[0]->stack == NULL){
      players[i]->stack = malloc(sizeof(stack_t));
      players[i]->stack->cards = malloc(NUM_CARD_PER_ROUND * sizeof(card_t));
    }
    players[i]->stack->size = NUM_CARD_PER_ROUND;
  }
  for(i = 0; i < NUM_CARD_PER_ROUND; i++){
    for(j = 0; j < num_players; j++){
      players[j]->stack->cards[i] = deck->cards[i * num_players + j];
    }
  }
  free (deck->cards);
  free (deck);
}
