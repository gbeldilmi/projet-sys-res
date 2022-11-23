#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct channel_s{
  FILE *in;
  FILE *out;
}channel_t;

typedef struct player_s{
  int id;
  int score;
  channel_t channel;
}player_t;

typedef struct card_s{
  int value;
  int heads;
}card_t;

typedef struct stack_s{
  int size;
  card_t *cards;
}stack_t;

void init();
void run();

extern char *game_dir;
extern int num_humans;
extern int num_bots;
