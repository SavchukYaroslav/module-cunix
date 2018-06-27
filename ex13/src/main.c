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



    FILE  *logger;
     logger = fopen("filler_new.log", "a");


  fprintf(logger,"\nFIGURE VALUES:\n");
    for(int i = 0; i < info->fig_h; i++){
      for(int j = 0; j < info->fig_w; j++)
        fprintf(logger,"%c", info->figure[i][j]);
        fprintf(logger,"\n");
    }
fclose(logger);




    destroy_info(info);
    info = NULL;
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
