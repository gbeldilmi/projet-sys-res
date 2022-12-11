#pragma once

/******************************************************************************
 * Includes                                                                   *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

/******************************************************************************
 * Defines                                                                    *
 ******************************************************************************/
#define MIN_PLAYERS 2
#define MAX_PLAYERS 10
#define MAX_SCORE 66
#define NUM_CARDS 104
#define NUM_CARD_PER_ROUND 10
#define NUM_STACKS 4
#define MAX_STACK_SIZE 5

/******************************************************************************
 * Structures                                                                 *
 ******************************************************************************/
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

/******************************************************************************
 * Function prototypes                                                        *
 ******************************************************************************/
void deal_cards(void);
void debug(void);
int play_bot_1(player_t *);
int play_bot_2(player_t *);
int play_human_1(player_t *);
int play_human_2(player_t *);
void run(void);

/******************************************************************************
 * Global variables                                                           *
 ******************************************************************************/
extern int num_players;
extern player_t *players;
extern stack_t *stacks;
