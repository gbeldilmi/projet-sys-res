#include "game.h"

/******************************************************************************
 * Draw the cards of a stack.                                                 *
 * -> FILE *out :                                                             *
 *      file where the cards will be drawn.                                   *
 * -> card_t *cards :                                                         *
 *      array of cards to print.                                              *
 * -> int size :                                                              *
 *      size of the array of cards.                                           *
 * -> int id :                                                                *
 *      id of the stack, -1 if it must not be printed.                        *
 * <- void                                                                    *
 ******************************************************************************/
static void print_cards(FILE *out, card_t *cards, int size, int id){
  int i, v, begin;
  begin = -(id != -1);
  for(i = begin; i < size; i++){
    if(i < 0){
      fprintf(out, "   ");
    }else{
      fprintf(out, "----- ");
    }
  }
  fprintf(out, "\n");
  // Print the value of the cards.
  for(i = begin; i < size; i++){
    if(i < 0){
      fprintf(out, " %c ", 'A' + id);
    }else{
      v = cards[i].value;
      if(v > 99){
        fprintf(out, "|%d| ", v);
      }else if(v > 9){
        fprintf(out, "| %d| ", v);
      }else{
        fprintf(out, "|  %d| ", v);
      }
    }
  }
  fprintf(out, "\n");
  // Print the number of heads of the cards.
  for(i = begin; i < size; i++){
    if(i < 0){
      fprintf(out, "   ");
    }else{
      v = cards[i].heads;
      fprintf(out, "|%d ¤| ", v);
    }
  }
  fprintf(out, "\n");
  for(i = begin; i < size; i++){
    if(i < 0){
      fprintf(out, "   ");
    }else{
      fprintf(out, "----- ");
    }
  }
  fprintf(out, "\n");
}

/******************************************************************************
 * Print the state of the game for the first part of the turn.                *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- void                                                                    *
 ******************************************************************************/
static void print_state_1(player_t *player){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_cards(player->out, stacks[i].cards, stacks[i].size, -1);
  }
  fprintf(player->out, "\n");
  print_cards(player->out, player->stack.cards, player->stack.size, -1);
  for(i = 0; i < player->stack.size; i++){
    fprintf(player->out, "-%c- ", 'A' + i);
  }
  fprintf(player->out, "\n");
}

/******************************************************************************
 * Print the state of the game for the second part of the turn.               *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- void                                                                    *
 ******************************************************************************/
static void print_state_2(player_t *player){
  int i;
  // Print the stacks.
  for(i = 0; i < NUM_STACKS; i++){
    print_cards(player->out, stacks[i].cards, stacks[i].size, i);
  }
  fprintf(player->out, "\n");
  // Print the player's card to play.
  print_cards(player->out, player->stack.cards + player->stack.size, 1, -1);
  fprintf(player->out, "\n");
}

/******************************************************************************
 * Get character written by the player.                                       *
 * -> FILE *in :                                                              *
 *     file from which the character will be read.                            *
 * <- int :                                                                   *
 *     character readed.                                                      *
 ******************************************************************************/
static int read_input(FILE *in){
  int c;
  do{
    c = fgetc(in);
    // Ignore spaces.
    if(isspace(c)){
      c = -1;
    }
  }while(c == -1);
  return c;
}

/******************************************************************************
 * Choose a card or a stack.                                                  *
 * -> player_t *player :                                                      *
 *      player who will choose.                                               *
 * -> int part :                                                              *
 *      the part of the game, 0 for the card and 1 for the stack.             *
 * <- int :                                                                   *
 *      index of the card or the stack chosen.                                *
 ******************************************************************************/
static int choose(player_t *player, int part){
  char obj[6];
  int c;
  // Define the object to choose.
  if(part == 0){
    strcpy(obj, "card");
  }else{
    strcpy(obj, "stack");
  }
  // Choose the card or the stack.
  fprintf(player->out, "Choose a %s: ", obj);
  c = -1;
  while(c < 0 || (part == 0 && c >= player->stack.size)
      || (part == 1 && c >= NUM_STACKS)){
    c = read_input(player->in);
    // If the character is valid, convert it to an index.
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      // If the character is not valid, ask again.
      fprintf(player->out, "Invalid %s. Choose again: ", obj);
      c = -1;
    }
    // If the index is valid, check if the card or the stack exists.
    if(c != -1 && ((part == 0 && c >= player->stack.size)
        || (part == 1 && c >= NUM_STACKS))){
      fprintf(player->out, "Invalid %s. Choose again: ", obj);
      c = -1;
    }
  }
  return c;
}

/******************************************************************************
 * Ask the player which card he wants to play.                                *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- int :                                                                   *
 *      id of the card chosen by the player.                                  *
 ******************************************************************************/
int play_human_1(player_t *player){
  print_state_1(player);
  return choose(player, 0);
}

/******************************************************************************
 * Ask the player which stack he wants to play.                               *
 * -> player_t *player :                                                      *
 *      player who will play.                                                 *
 * <- int :                                                                   *
 *      id of the stack chosen by the player.                                 *
 ******************************************************************************/
int play_human_2(player_t *player){
  print_state_2(player);
  return choose(player, 1);
}
