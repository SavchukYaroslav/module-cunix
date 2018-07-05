#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

int main(){
  filler_t    *filler;
  info_t      *info;
  pos_t        pos;
  
  filler = create_filler();
  
  while(1){
    info = create_info();

    read_inp(filler, info);

    pos = play(filler, info);
    
    print_pos(pos);

    destroy_info(info);
    info = NULL;
  }
  destroy_filler(filler);
}
