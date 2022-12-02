#include "game.h"

static void print_stack(FILE *out, stack_t *stack, int id){
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

static void print_stacks(FILE *out){
  int i;
  for(i = 0; i < NUM_STACKS; i++){
    print_stack(out, &stacks[i], i);
  }
}

static void print_card(FILE *out, card_t card){
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

static int choose_stack(player_t *player){
  int c;
  fprintf(player->out, "Choose a stack: ");
  c = -1;
  while(c < 0 || c >= NUM_STACKS){
    c = fgetc(player->in);
    if(c >= 'a' && c <= 'z'){
      c -= 'a';
    }else if(c >= 'A' && c <= 'Z'){
      c -= 'A';
    }else{
      fprintf(player->out, "Invalid stack. Choose again: ");
      c = -1;
    }
  }
  fprintf(player->out, "Waiting for others players...\n");
  return c;
}

int human2(player_t *player){
  print_stacks(player->out);
  print_card(player->out, player->stack.cards[player->stack.size]);
  return choose_stack(player);
}
