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
