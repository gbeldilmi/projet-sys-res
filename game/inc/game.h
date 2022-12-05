#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

#define MIN_PLAYERS 2
#define MAX_PLAYERS 10
#define MAX_SCORE 66
#define NUM_CARDS 104
#define NUM_CARD_PER_ROUND 10
#define NUM_STACKS 4
#define MAX_STACK_SIZE 5

typedef struct card_s{
  int value;
  int heads;
}card_t;

typedef struct stack_s{
  int size;
  card_t *cards;
}stack_t;

typedef struct player_s{
  int id;
  int score;
  FILE *in;
  FILE *out;
  stack_t stack;
}player_t;

void bye(void);
int choose_card(player_t *player);
int choose_stack(player_t *player);
void deal_cards(void);
void debug(void);
int game_is_ended(void);
void get_order(int *order);
void play_1(void *arg);
void play_2(player_t *player);
int play_bot_1(player_t *player);
int play_bot_2(player_t *player);
int play_human_1(player_t *player);
int play_human_2(player_t *player);
void podium(void);
void print_cards(FILE* out, card_t *cards, int size, int id);
void print_state_1(player_t *player);
void print_state_2(player_t *player);
int read_input(FILE *in);
void run(void);

extern int num_players;
extern player_t *players;
extern stack_t *stacks;
