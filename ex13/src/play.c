#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

//todo: fill info. Make info create, info destroy
pos_t           play(filler_t *filler, info_t *info){
  pos_t res;
  int w = filler->w;
  int h = filler->h;
  char** brd = filler->board;
  char s = filler->symbol;

  for(int i = h-1; i >= 0; i--){
    for(int j = w-1; j >= 0; j--){
        if(brd[i][j] == s){




FILE  *logger;
   logger = fopen("filler_new.log", "a");
 
   
   fprintf(logger,"My coord: %d %d\n", i, j);
   fprintf(logger,"I put: %d %d\n", i, j+1);
   fclose(logger);



          //dprintf(1, "%d %d\n", j+1, i);
          //dprintf(1, "%d %d\n", -1, -1);
          //write(1, "-1 -1", 6);
   res.x = j+1;
   res.y = i;
   return res;
        }
    }
  }
}
 /*
  FILE  *logger;
  logger = fopen("filler_new.log", "a");

  fprintf(logger,"\nFILLER VALUES: MAP:\n");
  for(int i = 0; i < filler->h; i++){
    for(int j = 0; j < filler->w; j++)
      fprintf(logger,"%c", filler->board[i][j]);
      fprintf(logger,"\n");
  }
  
  fclose(logger); 
  */
