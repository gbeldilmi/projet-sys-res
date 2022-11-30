#include "game.h"

int num_players;
player_t *players;
stack_t *stacks;

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
  path = (char *)malloc(strlen(game_dir) + 16);
  suffix = (char *)malloc(16);
  sprintf(suffix, "/%d.in", id);
  strcpy(path, game_dir);
  strcat(path, suffix);
  channel->in = fopen(game_dir, "r");
  sprintf(suffix, "/%d.out", id);
  strcpy(path, game_dir);
  strcat(path, suffix);
  channel->out = fopen(game_dir, "w");
  free(path);
  free(suffix);
  return channel;
}

static player_t *new_player(int id_channel){
  player_t *player;
  player = (player_t *)malloc(sizeof(player_t));
  player->score = 0;
  player->channel = open_channel(id_channel);
  player->stack = (stack_t *)malloc(sizeof(stack_t));
  player->stack->cards = (card_t *)malloc(NUM_CARD_PER_ROUND * sizeof(card_t));
  player->stack->size = 0;
  return player;
}

static stack_t *new_stack(){
  stack_t *stack;
  stack = (stack_t *)malloc(sizeof(stack_t));
  stack->cards = (card_t *)malloc(MAX_STACK_SIZE * sizeof(card_t));
  stack->size = 0;
  return stack;
}

static void bye(){
  int i;
  for(i = 0; i < num_players; i++){
    free(players[i].stack->cards);
    free(players[i].stack);
    if(players[i].channel){
      fclose(players[i].channel->in);
      fclose(players[i].channel->out);
      free(players[i].channel);
    }
  }
  free(players);
  for(i = 0; i < NUM_STACKS; i++){
    free(stacks[i].cards);
  }
  free(stacks);
}

int main(int argc, char *argv[]){
  int i;
  if(read_args(argc, argv)){
    return 1;
  }
  players = (player_t *)malloc(num_players * sizeof(player_t));
  for(i = 0; i < num_players; i++){
    players[i] = *(new_player((i < num_humans) ? i : -1));
  }
  stacks = (stack_t *)malloc(NUM_STACKS * sizeof(stack_t));
  for(i = 0; i < NUM_STACKS; i++){
    stacks[i] = *(new_stack());
  }
  run();
  bye();
  return 0;
}
