#include "game.h"

static int read_args(int argc, char **argv)
{
  int num_players;
  if(argc < 4){
    printf("Usage: %s <game_dir> <num_humans> <num_bots>", argv[0]);
    return 1;
  }
  game_dir = (char *)malloc(strlen(argv[1]) + 1);
  strcpy(game_dir, argv[1]);
  num_humans = atoi(argv[2]);
  num_bots = atoi(argv[3]);
  num_players = num_humans + num_bots;
  if(num_humans <= 0 || num_bots < 0 || num_players < 2 || num_players > 10){
    printf("Invalid number of players");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]){
  if(read_args(argc, argv)){
    return 1;
  }
  init();
  run();
  return 0;
}
