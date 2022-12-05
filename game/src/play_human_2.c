#include "game.h"

int play_human_2(player_t *player){
  print_state_2(player);
  return choose_stack(player);
}
