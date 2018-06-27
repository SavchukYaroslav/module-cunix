#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

//todo: fill info. Make info create, info destroy
int main(){
  filler_t    *filler;

  filler = create_filler();

  while(1){
    read_inp(filler);
    break;	
  }
  //Test log
  FILE  *logger;
  logger = fopen("filler_new.log", "a");

  fprintf(logger,"\nFILLER VALUES: MAP:\n");
  for(int i = 0; i < filler->h; i++){
    for(int j = 0; j < filler->w; j++)
      fprintf(logger,"%c", filler->board[i][j]);
      fprintf(logger,"\n");
  }

  // fprintf(logger,"\nFIGURE:\n");
  // for(int i = 0; i < fig_h; i++){
  //   for(int j = 0; j < fig_w; j++)
  //     fprintf(logger,"%c", figure[i][j]);
  //     fprintf(logger,"\n");
  // }
  fclose(logger); 
  destroy_filler(filler);

}