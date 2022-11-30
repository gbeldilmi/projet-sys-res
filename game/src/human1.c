#include "game.h"

static player_t *player;
static FILE *in, *out;

static void print_stack(stack_t *stack){
  int i, j, l;
  l = stack->size;
  for(i = 0; i < l; i++){
    fprintf(out, "----- ");
  }
  fprintf(out, "\n");
  j = stack->cards[i].value;
  for(i = 0; i < l; i++){
    if(j < 9){
      fprintf(out, "|  %d| ", j);
    }else if(j < 99){
      fprintf(out, "| %d| ", j);
    }else{
      fprintf(out, "|%d| ", j);
    }
  }
  fprintf(out, "\n");
  j = stack->cards[i].heads;
  for(i = 0; i < l; i++){
    fprintf(out, "|%d ¤| ", j);
  }
  fprintf(out, "\n");
  for(i = 0; i < l; i++){
    fprintf(out, "----- ");
  }
  fprintf(out, "\n");
}

static void print_stacks(){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_stack(&stacks[i]);
  }
  fprintf(out, "\n\n");
  print_stack(player->stack);
  for(i = 0; i < player->stack->size; i++){
    fprintf(out, "-%c- ", 'A' + i);
  }
}

static int choose_card(){
  int c;
  fprintf(out, "Choose a card: ");
  c = -1;
  while(c < 0 || c >= player->stack->size){
    read(in, &c, sizeof(char));
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      fprintf(out, "Invalid card. Choose again: ");
      c = -1;
    }
  }
  fprintf(out, "Waiting for others players...\n");
  return c;
}

int human1(int id_player){
  player = &players[id_player];
  in = player->channel->in;
  out = player->channel->out;
  print_stacks();
  return choose_card();
}
