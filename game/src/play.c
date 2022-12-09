#include "game.h"

/******************************************************************************
 * Play the first part of the turn for a player.                              *
 * -> void *arg :                                                             *
 *      player who will play.                                                 *
 * <- void                                                                    *
 ******************************************************************************/
void play_1(void *arg){
  player_t *player;
  card_t card;
  int chosen;
  // Get the player.
  player = (player_t *)arg;
  // Get the card chosen by the player.
  chosen = (player->out) ? play_human_1(player) : play_bot_1(player);
  // Place the card chosen by the player at the end of the stack.
  card = player->stack.cards[chosen];
  player->stack.cards[chosen] = player->stack.cards[player->stack.size - 1];
  player->stack.cards[player->stack.size - 1] = card;
  // Decrease the size of the stack by one.
  player->stack.size--;
  // Wait for the other players.
  if(player->out){
    fprintf(player->out, "Waiting for others players...\n");
  }
}

/******************************************************************************
 * Play the second part of the turn for a player.                             *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- void                                                                    *
 ******************************************************************************/
void play_2(player_t *player){
  stack_t *cs;
  int i, sh;
  // Get the stack chosen by the player.
  cs = &stacks[(player->out) ? play_human_2(player) : play_bot_2(player)];
  // Add the card at the end of the stack to the chosen stack.
  if(cs->size < MAX_STACK_SIZE && cs->cards[cs->size -1].value
      < player->stack.cards[player->stack.size].value){
    // If the card can fit in the stack, add it.
    cs->cards[cs->size] = player->stack.cards[player->stack.size];
    cs->size++;
  }else{
    // If the card can't fit in the stack, add the number of heads to the 
    // player's score and put the card at the as the first card of the stack.
    sh = 0;
    for(i = 0; i < cs->size; i++){
      sh += cs->cards[i].heads;
    }
    player->score += sh;
    cs->cards[0] = player->stack.cards[player->stack.size];
    cs->size = 1;
    // Print the number of heads taken by the player and wait.
    if(player->out){
      fprintf(player->out, "You got %d heads!\n", sh);
      fprintf(player->out, "Waiting for others players...\n");
    }
  }
}
