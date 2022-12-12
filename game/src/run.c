#include "game.h"

/******************************************************************************
 * Check if the game is ended.                                                *
 * -> void                                                                    *
 * <- int :                                                                   *
 *      1 if the game is ended, 0 otherwise.                                  *
 ******************************************************************************/
static int game_is_ended(void){
  int i;
  // Check if a player has reached the maximum score.
  for(i = 0; i < num_players; i++){
    if(players[i].score >= MAX_SCORE){
      return 1;
    }
  }
  return 0;
}

/******************************************************************************
 * Get the order of the players who will play by the value of chosen cards.   *
 * -> int *order :                                                            *
 *      array which will contain the order of the players, it must be         *
 *      allocated before calling this function and have a size of at least    *
 *      the number of players.                                                *
 * <- void                                                                    *
 ******************************************************************************/
static void get_order(int *order){
  int i, j;
  // Initialize the order array by the id of the players.
  for(i = 0; i < num_players; i++){
    order[i] = i;
  }
  // Sort the order array, the player with the lowest value will be first.
  for(i = 0; i < num_players; i++){
    for(j = i + 1; j < num_players; j++){
      if(players[order[i]].stack.cards[players[order[i]].stack.size].value
          > players[order[j]].stack.cards[players[order[j]].stack.size].value){
        order[i] += order[j];
        order[j] = order[i] - order[j];
        order[i] -= order[j];
      }
    }
  }
}

/******************************************************************************
 * Play the first part of the turn for a player.                              *
 * -> void *p :                                                             *
 *      player who will play.                                                 *
 * <- void                                                                    *
 ******************************************************************************/
static void play_1(void *p){
  player_t *player;
  card_t card;
  int chosen;
  // Get the player.
  player = (player_t *)p;
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
static void play_2(player_t *player){
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

/******************************************************************************
 * Get the podium of the players and print it for each player.                *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
static void podium(void){
  FILE *out;
  int i, j, order[num_players];
  // Initialize the order array by the id of the players.
  for(i = 0; i < num_players; i++){
    order[i] = i;
  }
  // Sort the array, the player with the highest score will be in last position.
  for(i = 0; i < num_players; i++){
    for(j = i + 1; j < num_players; j++){
      if(players[order[i]].score < players[order[j]].score){
        order[i] += order[j];
        order[j] = order[i] - order[j];
        order[i] -= order[j];
      }
    }
  }
  // Print the podium for each (human) player.
  for(i = 0; i < num_players; i++){
    if((out = players[order[i]].out)){
      for(j = num_players - 1; j >= 0; j--){
        fprintf(out, "Player %d: %d heads\n", order[j] + 1, players[order[j]].score);
      }
      fprintf(out, "You are in position %d of %d !\n", num_players - i, num_players);
      fprintf(out, "Your score is %d !\n", players[i].score);
    }
  }
}

/******************************************************************************
 * Run the game until it is ended.                                            *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
void run(void){
  pthread_t threads[num_players];
  int i, r, order[num_players];
  r = 0;
  while(!r){
    // If players have no cards, deal new cards.
    if(players[0].stack.size == 0){
      deal_cards();
    }
    // Play the first phase for every player at the same time.
    for(i = 0; i < num_players; i++){
      pthread_create(&threads[i], NULL, (void *)play_1, (void *)&players[i]);
    }
    // Wait for the end of the first phase.
    for(i = 0; i < num_players; i++){
      pthread_join(threads[i], NULL);
    }
    // Get the order to play the second phase.
    get_order(order);
    // Play the second phase for every player.
    for(i = 0; i < num_players && !r; i++){
      play_2(&players[order[i]]);
      // Check after each turn if the game is ended.
      r = game_is_ended();
    }
  }
  // Display the podium at the end of the game.
  podium();
}
