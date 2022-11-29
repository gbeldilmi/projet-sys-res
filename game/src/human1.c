#include "game.h"

static player_t *player;
static int in, out;

static void print_stack(stack_t *stack){
  int i, j, l;
  l = stack->size;
  for(i = 0; i < l; i++){
    dprintf(out, "----- ");
  }
  dprintf(out, "\n");
  j = stack->cards[i].value;
  for(i = 0; i < l; i++){
    if(j < 9){
      dprintf(out, "|  %d| ", j);
    }else if(j < 99){
      dprintf(out, "| %d| ", j);
    }else{
      dprintf(out, "|%d| ", j);
    }
  }
  dprintf(out, "\n");
  j = stack->cards[i].heads;
  for(i = 0; i < l; i++){
    dprintf(out, "|%d ¤| ", j);
  }
  dprintf(out, "\n");
  for(i = 0; i < l; i++){
    dprintf(out, "----- ");
  }
  dprintf(out, "\n");
}

static void print_stacks(){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_stack(stacks[i]);
  }
  dprintf(out, "\n\n");
  print_stack(player->stack);
  for(i = 0; i < player->stack->size; i++){
    dprintf(out, "-%c- ", 'A' + i);
  }
}

static int choose_card(){
  int c;
  dprintf(out, "Choose a card: ");
  c = -1;
  while(c < 0 || c >= player->stack->size){
    read(in, &c, sizeof(char));
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      dprintf(out, "Invalid card. Choose again: ");
      c = -1;
    }
  }
  return c;
}

int human1(int id_player){
  player = players[id_player];
  in = player->channel->in;
  out = player->channel->out;
  print_stacks();
  return choose_card();
}
