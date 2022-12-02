#include "game.h"

static void print_stack(FILE* out, stack_t *stack){
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

static void print_stacks(player_t *player){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_stack(player->out, &stacks[i]);
  }
  fprintf(player->out, "\n\n");
  print_stack(player->out, &player->stack);
  for(i = 0; i < player->stack.size; i++){
    fprintf(player->out, "-%c- ", 'A' + i);
  }
}

static int choose_card(player_t *player){
  int c;
  fprintf(player->out, "Choose a card: ");
  c = -1;
  while(c < 0 || c >= player->stack.size){
    c = fgetc(player->in);
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      fprintf(player->out, "Invalid card. Choose again: ");
      c = -1;
    }
  }
  fprintf(player->out, "Waiting for others players...\n");
  return c;
}

int human1(player_t *player){
  print_stacks(player);
  return choose_card(player);
}
