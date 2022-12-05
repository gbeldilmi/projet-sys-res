#include "game.h"

int play_1(void *arg){
  player_t *player;
  player = (player_t *)arg;
  return (player->out == NULL) ? play_bot_1(player) : play_human_1(player);
}
