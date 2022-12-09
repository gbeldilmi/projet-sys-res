#include "game.h"

/******************************************************************************
 * Get the number of heads of a card.                                         *
 * -> int value :                                                             *
 *      value of the card.                                                    *
 * <- int :                                                                   *
 *      number of heads of the card.                                          *
 ******************************************************************************/
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

/******************************************************************************
 * Initialize the deck of cards, it will be randomized.                       *
 * -> stack_t *deck :                                                         *
 *      deck of cards which will be initialized.                              *
 * <- void                                                                    *
 ******************************************************************************/
static void init_deck(stack_t *deck){
  card_t c;
  int i, j;
  deck->size = NUM_CARDS;
  deck->cards = (card_t *)malloc(NUM_CARDS * sizeof(card_t));
  // Check if the memory allocation was successful.
  if(deck->cards == NULL){
    printf("Error allocating memory for the deck of cards");
    exit(EXIT_FAILURE);
  }
  // Initialize the deck with the values of the cards.
  for(i = 1; i <= NUM_CARDS; i++){
    deck->cards[i].value = i;
    deck->cards[i].heads = f_heads(i);
  }
  // Randomize the deck.
  for(i = 0; i < NUM_CARDS; i++){
    j = rand() % NUM_CARDS;
    c = deck->cards[i];
    deck->cards[i] = deck->cards[j];
    deck->cards[j] = c;
  }
}

/******************************************************************************
 * Deal the cards to the players and the stacks.                              *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
void deal_cards(void){
  stack_t deck;
  int i, j;
  init_deck(&deck);
  // Deal cards to the players.
  for(i = 0; i < NUM_CARD_PER_ROUND; i++){
    for(j = 0; j < num_players; j++){
      players[j].stack.cards[i] = deck.cards[i * num_players + j];
      players[j].stack.size++;
    }
  }
  // Next cards will be set to stacks.
  for(i = 0; i < NUM_STACKS; i++){
    stacks[i].cards[0] = deck.cards[NUM_CARD_PER_ROUND * num_players + i];
    stacks[i].size = 1;
  }
  // Free the deck.
  free(deck.cards);
}
