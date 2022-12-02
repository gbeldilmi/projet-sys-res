#include "game.h"

int num_players;
player_t *players;
stack_t *stacks;

static char *game_dir;
static int num_humans;
static int num_bots;

static void read_args(int argc, char **argv){
  if(argc < 4){
    printf("Usage: %s <game_dir> <num_humans> <num_bots>", argv[0]);
    exit(EXIT_FAILURE);
  }
  game_dir = (char *)malloc(strlen(argv[1]) + 1);
  if(game_dir == NULL){
    printf("Error allocating memory for game_dir");
    exit(EXIT_FAILURE);
  }
  strcpy(game_dir, argv[1]);
  num_humans = atoi(argv[2]);
  num_bots = atoi(argv[3]);
  num_players = num_humans + num_bots;
  if(num_humans <= 0 || num_bots < 0 || num_players < MIN_PLAYERS || num_players > MAX_PLAYERS){
    printf("Invalid number of players");
    exit(EXIT_FAILURE);
  }
}

static void open_fifo(player_t *player){
  char path[strlen(game_dir) + 16];
  sprintf(path, "%s/%d.in", game_dir, player->id);
  player->in = fopen(path, "r");
  if(player->in == NULL){
    printf("Error opening input fifo for player %d", player->id);
    exit(EXIT_FAILURE);
  }
  sprintf(path, "%s/%d.out", game_dir, player->id);
  player->out = fopen(path, "a");
  if(player->out == NULL){
    printf("Error opening output fifo for player %d", player->id);
    exit(EXIT_FAILURE);
  }
}

static void init_players(void){
  int i;
  players = (player_t *)malloc(num_players * sizeof(player_t));
  if(players == NULL){
    printf("Error allocating memory for players");
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < num_players; i++){
    players[i].id = i;
    players[i].score = 0;
    players[i].stack.size = 0;
    players[i].stack.cards = (card_t *)malloc(NUM_CARD_PER_ROUND * sizeof(card_t));
    if(players[i].stack.cards == NULL){
      printf("Error allocating memory for player %d stack", i);
      exit(EXIT_FAILURE);
    }
    players[i].in = players[i].out = NULL;
    if(i < num_humans){
      open_fifo(&players[i]);
    }
  }
  free(game_dir);
}

static void init_stacks(void){
  int i;
  stacks = (stack_t *)malloc(NUM_STACKS * sizeof(stack_t));
  if(stacks == NULL){
    printf("Error allocating memory for stacks");
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < NUM_STACKS; i++){
    stacks[i].size = 0;
    stacks[i].cards = (card_t *)malloc(MAX_STACK_SIZE * sizeof(card_t));
    if(stacks[i].cards == NULL){
      printf("Error allocating memory for stack %d", i);
      exit(EXIT_FAILURE);
    }
  }
}

static void bye(void){
  int i;
  for(i = 0; i < num_players; i++){

  }
  
}

int main(int argc, char *argv[]){
  read_args(argc, argv);
  init_players();
  init_stacks();
  run();
  bye();
  return EXIT_SUCCESS;
}
