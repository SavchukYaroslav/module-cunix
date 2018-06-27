#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

int cell_inside_map(int x, int y, filler_t *filler, info_t *info){
    return (x < filler->w) && (x > 0) && (y < filler->h) && (y > 0);
}

int cell_is_empty(int x, int y, filler_t *filler, info_t *info){
    return filler->board[y][x] == '.';
}

int cell_is_nghbr(int x, int y, filler_t *filler, info_t *info){
    return filler->board[y][x] == filler->symbol;
}

int cell_nghbr_exist(int x, int y, filler_t *filler, info_t *info){
  if(cell_inside_map(x, y+1, filler, info) && cell_is_nghbr(x, y+1, filler, info))
        return 1;
  if(cell_inside_map(x, y-1, filler, info) && cell_is_nghbr(x, y-1, filler, info))
        return 1;
  if(cell_inside_map(x+1, y, filler, info) && cell_is_nghbr(x+1, y, filler, info))
        return 1;
  if(cell_inside_map(x-1, y, filler, info) && cell_is_nghbr(x-1, y, filler, info))
        return 1;
  return 0;
}

int can_put_figure(int x, int y, filler_t *filler, info_t *info){
    for(int i = 0; i < info->fig_h; i++){
        for(int j = 0; j < info->fig_w; j++){
          if  ((info->figure[j][i] == '*')
            && cell_inside_map(x+j, y+i, filler, info)
            && cell_is_empty(x+j, y+i, filler, info)
            && cell_nghbr_exist(x+j, y+i, filler, info)){
                return 1;
            }

        }
    }
    return 0;
}

pos_t simple_diagonal(filler_t *filler, info_t *info){
  pos_t res;
  int w = filler->w;
  int h = filler->h;
  char** brd = filler->board;
  char s = filler->symbol;

  for(int i = h-1; i >= 0; i--){
    for(int j = w-1; j >= 0; j--){
        if(brd[i][j] == s){
          res.x = j+1;
          res.y = i;
          return res;
        }
    }
  }
}


pos_t silly(filler_t *filler, info_t *info){
  pos_t res;
  int w = filler->w;
  int h = filler->h;
  char** brd = filler->board;
  char s = filler->symbol;

  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
        if(can_put_figure(j, i, filler, info)){
            res.x = j;
            res.y = i;
            return res;
        }
     }
  }
  res.x = -1;
  res.y = -1;
  return res;
  
}
pos_t         play(filler_t *filler, info_t *info){
  pos_t res;
  int w = filler->w;
  int h = filler->h;
  char** brd = filler->board;
  char s = filler->symbol;
  static int tactics = 0;

  if(tactics == -1)
    return simple_diagonal(filler, info);
  if(tactics == 0){
    return silly(filler, info);
  }
}
