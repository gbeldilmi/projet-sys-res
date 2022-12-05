#include "game.h"

void print_cards(FILE* out, card_t *cards, int size, int id){
  int i, v, begin;
  begin = -(id != -1);
  for(i = begin; i < size; i++){
    if(i < 0){
      fprintf(out, "   ");
    }else{
      fprintf(out, "----- ");
    }
  }
  fprintf(out, "\n");
  for(i = begin; i < size; i++){
    if(i < 0){
      printf(" %c ", 'A' + id);
    }else{
      v = cards[i].value;
      if(v > 99){
        fprintf(out, "|%d| ", v);
      }else if(v > 9){
        fprintf(out, "| %d| ", v);
      }else{
        fprintf(out, "|  %d| ", v);
      }
    }
  }
  fprintf(out, "\n");
  for(i = begin; i < size; i++){
    if(i < 0){
      printf("   ");
    }else{
      v = cards[i].heads;
      fprintf(out, "|%d ¤| ", v);
    }
  }
  fprintf(out, "\n");
  for(i = begin; i < size; i++){
    if(i < 0){
      printf("   ");
    }else{
      fprintf(out, "----- ");
    }
  }
  fprintf(out, "\n");
}
