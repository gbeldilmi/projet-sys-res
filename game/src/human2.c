#include "game.h"

static player_t *player;
static FILE *in, *out;

static void print_stack(stack_t *stack, int id){
  int i, j, l;
  l = stack->size;
  for(i = -1; i < l; i++){
    if(i == -1){
      fprintf(out, "   ");
    }else{
      fprintf(out, "----- ");
    }
  }
  fprintf(out, "\n");
  j = stack->cards[i].value;
  for(i = -1; i < l; i++){
    if(i == -1){
      printf(" %c ", 'A' + id);
    }else{
      if(j < 9){
        fprintf(out, "|  %d| ", j);
      }else if(j < 99){
        fprintf(out, "| %d| ", j);
      }else{
        fprintf(out, "|%d| ", j);
      }
    }
  }
  fprintf(out, "\n");
  j = stack->cards[i].heads;
  for(i = -1; i < l; i++){
    if(i == -1){
      printf("   ");
    }else{
      fprintf(out, "|%d ¤| ", j);
    }
  }
  fprintf(out, "\n");
  for(i = -1; i < l; i++){
    if(i == -1){
      printf("   ");
    }else{
      fprintf(out, "----- ");
    }
  }
  fprintf(out, "\n");
}

static void print_stacks(){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_stack(&stacks[i], i);
  }
}

static void print_card(card_t card){
  fprintf(out, "   ----- \n   |");
  if(card.value < 9){
    fprintf(out, "  %d", card.value);
  }else if(card.value < 99){
    fprintf(out, " %d", card.value);
  }else{
    fprintf(out, "%d", card.value);
  }
  fprintf(out, "| \n   |%d ¤| \n   ----- \n", card.heads);
}

static int choose_stack(){
  int c;
  fprintf(out, "Choose a stack: ");
  c = -1;
  while(c < 0 || c >= NUM_STACKS){
    c = fgetc(in);
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      fprintf(out, "Invalid stack. Choose again: ");
      c = -1;
    }
  }
  fprintf(out, "Waiting for others players...\n");
  return c;
}

int human2(int id_player){
  player = &players[id_player];
  in = player->channel->in;
  out = player->channel->out;
  print_stacks();
  print_card(player->stack->cards[player->stack->size]);
  return choose_stack();
}
