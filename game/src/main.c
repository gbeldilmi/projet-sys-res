#include "game.h"

/******************************************************************************
 * Global variables.                                                          *
 ******************************************************************************/
int num_players;
player_t *players;
stack_t *stacks;

/******************************************************************************
 * Static variables used to process the arguments passed to the program.      *
 ******************************************************************************/
static char *game_dir;
static int num_humans;
static int num_bots;

/******************************************************************************
 * Read the arguments of the program and initialize static variables.         *
 * -> int argc :                                                              *
 *      number of arguments.                                                  *
 * -> char **argv :                                                           *
 *      array of arguments.                                                   *
 * <- void                                                                    *
 ******************************************************************************/
static void read_args(int argc, char **argv){
  // Check the number of arguments.
  if(argc < 4){
    printf("Usage: %s <game_dir> <num_humans> <num_bots>", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Process the first argument : path to the game directory.
  game_dir = (char *)malloc(strlen(argv[1]) + 1);
  if(game_dir == NULL){
    printf("Error allocating memory for game_dir");
    exit(EXIT_FAILURE);
  }
  strcpy(game_dir, argv[1]);
  // Process the second and third arguments : numbes of human and bot players.
  num_humans = 1/*atoi(argv[2])*/; // Todo : change it when fixed //////////////
  num_bots = atoi(argv[3]);
  num_players = num_humans + num_bots;
  // Check if the number of players is valid.
  if(num_humans < 1 || num_bots < 0 || num_players < MIN_PLAYERS
      || num_players > MAX_PLAYERS){
    printf("Invalid number of players");
    exit(EXIT_FAILURE);
  }
}

/******************************************************************************
 * Open the fifos used to communicate with the player.                        *
 * -> player_t *player :                                                      *
 *      player for which the fifos will be opened.                            *
 * <- void                                                                    *
 ******************************************************************************/
static void open_fifo(player_t *player){
  char path[strlen(game_dir) + 16];
  // Open the input fifo.
  sprintf(path, "%s/%d.in", game_dir, player->id);
  player->in = fopen(path, "r");
  if(player->in == NULL){
    printf("Error opening input fifo for player %d", player->id);
    exit(EXIT_FAILURE);
  }
  // Open the output fifo.
  sprintf(path, "%s/%d.out", game_dir, player->id);
  player->out = fopen(path, "a");
  if(player->out == NULL){
    printf("Error opening output fifo for player %d", player->id);
    exit(EXIT_FAILURE);
  }
  
}

/******************************************************************************
 * Initialize the players.                                                    *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
static void init_players(void){
  int i;
  // Allocate memory for the players.
  players = (player_t *)malloc(num_players * sizeof(player_t));
  if(players == NULL){
    printf("Error allocating memory for players");
    exit(EXIT_FAILURE);
  }
  // Initialize the players
  for(i = 0; i < num_players; i++){
    // Player's id is its index in the players array.
    players[i].id = i;
    players[i].score = 0;
    // Initialize the player's stack.
    players[i].stack.size = 0;
    players[i].stack.cards = (card_t *)malloc(NUM_CARD_PER_ROUND
        * sizeof(card_t));
    if(players[i].stack.cards == NULL){
      printf("Error allocating memory for player %d stack", i);
      exit(EXIT_FAILURE);
    }
    // Initialize the fifos.
    players[i].in = players[i].out = NULL;
    if(i < num_humans){
      if(i == 0){
        players[i].in = stdin;
        players[i].out = stdout;
      }else{
        open_fifo(&players[i]);
      }
    }
  }
  // The variable game_dir is no longer needed.
  free(game_dir);
}

/******************************************************************************
 * Initialize the stacks.                                                     *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
static void init_stacks(void){
  int i;
  // Allocate memory for all the stacks.
  stacks = (stack_t *)malloc(NUM_STACKS * sizeof(stack_t));
  if(stacks == NULL){
    printf("Error allocating memory for stacks");
    exit(EXIT_FAILURE);
  }
  // Initialize the stacks and allocate memory for their cards.
  for(i = 0; i < NUM_STACKS; i++){
    stacks[i].size = 0;
    stacks[i].cards = (card_t *)malloc(MAX_STACK_SIZE * sizeof(card_t));
    if(stacks[i].cards == NULL){
      printf("Error allocating memory for stack %d", i);
      exit(EXIT_FAILURE);
    }
  }
}

/******************************************************************************
 * Free all the ressources allocated by the game.                             *
 * -> void                                                                    *
 * <- void                                                                    *
 ******************************************************************************/
static void bye(void){
  int i;
  // Free the players.
  for(i = 0; i < num_players; i++){
    // Close each file.
    if(players[i].in != NULL && players[i].in != stdin){
      fclose(players[i].in);
    }
    if(players[i].out != NULL && players[i].out != stdout){
      fclose(players[i].out);
    }
    // Free each array of cards.
    free(players[i].stack.cards);
  }
  free(players);
  // Free the stacks.
  for(i = 0; i < NUM_STACKS; i++){
    free(stacks[i].cards);
  }
  free(stacks);
}

/******************************************************************************
 * Program entry point.                                                       *
 * -> int argc :                                                              *
 *      number of arguments.                                                  *
 * -> char **argv :                                                           *
 *      array of arguments.                                                   *
 * <- int :                                                                   *
 *      exit status of the program.                                           *
 ******************************************************************************/
int main(int argc, char *argv[]){
  read_args(argc, argv);
  init_players();
  init_stacks();
  atexit(bye);
  run();
  return EXIT_SUCCESS;
}
