#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

int main(){
  filler_t    *filler;
  info_t      *info;
  filler = create_filler();
  //info = create_info();
  FILE  *logger;
  
  logger = fopen("filler_new.log", "w");
  fprintf(logger,"Start");
  fclose(logger);
  int ctr = 0;
  while(1){
    info = create_info();
  logger = fopen("filler_new.log", "a");

  fprintf(logger,"New interationi-%d\n", ctr++);
  
    read_inp(filler, info);

    play(filler, info);

    destroy_info(info);
    info = NULL;
    fprintf(logger, "End of iteration\n");
    fclose(logger);
  }
 logger = fopen("filler_new.log", "a");

  fprintf(logger,"Exit\n");
  fclose(logger);
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
