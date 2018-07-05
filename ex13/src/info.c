#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/filler.h"
#include "../include/stream.h"

info_t     *create_info(){
  info_t    *info;

  info = malloc(sizeof(filler_t));
  info->fig_w = 0;
  info->fig_h = 0;
  info->figure = NULL;

  return info;
}

void          destroy_info(info_t *info){
  if (info->figure){
    for(int i = 0; i < info->fig_h; i++)
        free(info->figure[i]); 
    free(info->figure);
  }
  free(info);
}
