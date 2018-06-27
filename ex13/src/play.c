#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

//todo: fill info. Make info create, info destroy
int main(){
  filler_t    *filler;
  info_t      *info;
  filler = create_filler();
  info = create_info();
  while(1){
    read_inp(filler, info);
    destroy_info(info);
    info = NULL;
    break;	
  }
  destroy_filler(filler);
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
