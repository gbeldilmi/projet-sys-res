#include "game.h"

void play_1(void *arg){
  player_t *player;
  card_t card;
  int chosen;
  player = (player_t *)arg;
  chosen = (player->out == NULL) ? play_bot_1(player) : play_human_1(player);
  card = player->stack.cards[chosen];
  player->stack.cards[chosen] = player->stack.cards[player->stack.size - 1];
  player->stack.cards[player->stack.size - 1] = card;
  player->stack.size--;
}
