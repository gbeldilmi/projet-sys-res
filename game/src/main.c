#include "game.h"

static char *game_dir;
static int num_humans;
static int num_bots;

static int read_args(int argc, char **argv){
  if(argc < 4){
    printf("Usage: %s <game_dir> <num_humans> <num_bots>", argv[0]);
    return 1;
  }
  game_dir = (char *)malloc(strlen(argv[1]) + 1);
  strcpy(game_dir, argv[1]);
  num_humans = atoi(argv[2]);
  num_bots = atoi(argv[3]);
  num_players = num_humans + num_bots;
  if(num_humans <= 0 || num_bots < 0 || num_players < MIN_PLAYERS || num_players > MAX_PLAYERS){
    printf("Invalid number of players");
    return 1;
  }
  return 0;
}

static channel_t *open_channel(int id){
  channel_t *channel;
  char *path, *suffix;
  if(id < 0 || id >= num_players){
    return NULL;
  }
  channel = (channel_t *)malloc(sizeof(channel_t));
  path = (char *)malloc(strlen(game_dir) + 10);
  suffix = (char *)malloc(10);
  sprintf(suffix, "/%d.in", id);
  strcpy(path, game_dir);
  strcat(path, suffix);
  channel->in = open(game_dir, O_RDONLY);
  sprintf(suffix, "/%d.out", id);
  strcpy(path, game_dir);
  strcat(path, suffix);
  channel->out = open(game_dir, O_WRONLY);
}

static player_t *new_player(int id_channel){
  player_t *player;
  player = malloc(sizeof(player_t));
  player->score = 0;
  player->channel = open_channel(id_channel);
  player->stack = malloc(sizeof(stack_t));
  player->stack->cards = malloc(NUM_CARD_PER_ROUND * sizeof(card_t));
  player->stack->size = 0;
}

int main(int argc, char *argv[]){
  int i;
  if(read_args(argc, argv)){
    return 1;
  }
  players = malloc(num_players * sizeof(player_t));
  for(i = 0; i < num_players; i++){
    players[i] = new_player((i < num_humans) ? i : -1);
  }
  run();
  return 0;
}
