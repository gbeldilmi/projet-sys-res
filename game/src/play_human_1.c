#include "game.h"

int play_human_1(player_t *player){
  print_state_1(player);
  return choose_card(player);
}
