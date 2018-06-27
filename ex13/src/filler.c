#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/filler.h"
#include "../include/stream.h"

filler_t     *create_filler(){
  filler_t    *filler;

  filler = malloc(sizeof(filler_t));
  filler->symbol = '!';
  filler->w = 0;
  filler->h = 0;
  filler->board = NULL;
  filler->prev_board = NULL;

  return filler;
}
//todo: remove whole board
void          destroy_filler(filler_t *filler){
  if (filler->board){
    for(int i = 0; i < filler->h; i++)
          free(filler->board[i]); //todo: remove whole board
     free(filler->board);
  }

  if (filler->prev_board){
    for(int i = 0; i < filler->h; i++)
          free(filler->prev_board[i]); //todo: remove whole board
    free(filler->prev_board);
  }
  free(filler);
}

