#include "game.h"

static int f_heads(int value){
  int heads, tens, units;
  heads = 0;
  tens = value / 10;
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

static void init_deck(stack_t *deck){
  card_t c;
  int i, j;
  deck->size = NUM_CARDS;
  deck->cards = (card_t *)malloc(NUM_CARDS * sizeof(card_t));
  if(deck->cards == NULL){
    printf("Error allocating memory for the deck of cards");
    exit(EXIT_FAILURE);
  }
  for(i = 1; i <= NUM_CARDS; i++){
    deck->cards[i].value = i;
    deck->cards[i].heads = f_heads(i);
  }
  for(i = 1; i <= NUM_CARDS; i++){
    fprintf(stderr, "%d(%d) ", deck->cards[i].value, deck->cards[i].heads);
  }
  fprintf(stderr, "\n");
  // randomize deck
  for(i = 0; i < NUM_CARDS; i++){
    j = rand() % NUM_CARDS;
    c = deck->cards[i];
    deck->cards[i] = deck->cards[j];
    deck->cards[j] = c;
  }
  for(i = 1; i <= NUM_CARDS; i++){
    fprintf(stderr, "%d(%d) ", deck->cards[i].value, deck->cards[i].heads);
  }
}

void deal_cards(void){
  stack_t deck;
  int i, j;
  init_deck(&deck);
  for(i = 0; i < NUM_CARD_PER_ROUND; i++){
    for(j = 0; j < num_players; j++){
      players[j].stack.cards[i] = deck.cards[i * num_players + j];
      players[j].stack.size++;
    }
  }
  for(i = 0; i < NUM_STACKS; i++){
    stacks[i].cards[0] = deck.cards[NUM_CARD_PER_ROUND * num_players + i];
    stacks[i].size = 1;
  }
  free(deck.cards);
}
