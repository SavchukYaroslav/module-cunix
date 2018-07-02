#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/stream.h"

static int stage = 0;
int cell_inside_map(int x, int y, filler_t *filler){
    return (x < filler->w) && (x >= 0) && (y < filler->h) && (y >= 0);
}

int cell_is_empty(int x, int y, filler_t *filler){
    return filler->board[y][x] == '.';
}

int cell_is_nghbr(int x, int y, filler_t *filler){
    return filler->board[y][x] == filler->symbol;
}

int cell_is_enemy(int x, int y, filler_t *filler){
    return (filler->board[y][x] != filler->symbol)
         &&(filler->board[y][x] != '.');
}

int cell_nghbr_exist(int x, int y, filler_t *filler){
  if(cell_inside_map(x, y+1, filler) && cell_is_nghbr(x, y+1, filler))
        return 1;
  if(cell_inside_map(x, y-1, filler) && cell_is_nghbr(x, y-1, filler))
        return 1;
  if(cell_inside_map(x+1, y, filler) && cell_is_nghbr(x+1, y, filler))
        return 1;
  if(cell_inside_map(x-1, y, filler) && cell_is_nghbr(x-1, y, filler))
        return 1;
  return 0;
}

int cell_enemy_exist(int x, int y, filler_t *filler){
  if(cell_inside_map(x, y+1, filler) && cell_is_enemy(x, y+1, filler))
        return 1;
  if(cell_inside_map(x, y-1, filler) && cell_is_enemy(x, y-1, filler))
        return 1;
  if(cell_inside_map(x+1, y, filler) && cell_is_enemy(x+1, y, filler))
        return 1;
  if(cell_inside_map(x-1, y, filler) && cell_is_enemy(x-1, y, filler))
        return 1;
  return 0;
}


int can_put_figure(int x, int y, filler_t *filler, info_t *info){
      int neigh_found;
      
      neigh_found = 0;

      for(int i = 0; i < info->fig_h; i++){
        for(int j = 0; j < info->fig_w; j++){
          if  (info->figure[i][j] == '*'){
             if(!cell_inside_map(x+j, y+i, filler))
               return 0;
             if(!cell_is_empty(x+j, y+i, filler))
                return 0;
             if(cell_nghbr_exist(x+j, y+i, filler))
                neigh_found = 1;
          }
        }
      }
      return neigh_found;
  }

int enemy_near(int x, int y, filler_t* filler, info_t* info){
  for(int i = 0; i < info->fig_h; i++){
        for(int j = 0; j < info->fig_w; j++){
             if(cell_enemy_exist(x+j, y+i, filler))
                return 1;
          }
   }
  return 0;
}
  
 // return cell_enemy_exist(


pos_t silly_direction(filler_t *filler, info_t *info, int dir){
  pos_t res;
  int w = filler->w;
  int h = filler->h;

  if(dir == 1){
    for(int j = w-1; j >= 0; j--){
      for(int i = 0; i < h; i++){
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

  else if(dir == 0){
    for(int j = 0; j < w; j++){
      for(int i = 0; i < h; i++){
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

  else if(dir == 2){
    for(int i = h-1; i >= 0; i--){
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


 else if(dir == 3){ 
     for(int i = 0; i < h; i++){
       for(int j = w-1; j >= 0; j--){
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

  else if(dir == 4){ 
     for(int j = w-1; j >= 0; j--){
       for(int i = h-1; i >= 0; i--){
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


  else{

      int possib_found;
      pos_t possible;

      possib_found = 0;
      possible.x = -1;
      possible.y = -1;


     for(int j = w-1; j >= 0; j--){
       for(int i = h-1; i >= 0; i--){
          if(can_put_figure(j, i, filler, info)){
              if(enemy_near(j, i, filler, info)){
                res.x = j;
                res.y = i;
                return res;
              }
              else{
                  if(!possib_found){
                    possible.x = j;
                    possible.y = i;

                    possib_found = 1;
                  }
              }
           }
        }
    }

    if(possib_found)
        return possible;

    res.x = -1;
    res.y = -1;
    return res;
   }

}

int elem_is_wall(filler_t *filler, int x, int y){
 if((x == 0) || (y == 0) ||
     (x == filler->w - 1) || (y == filler->h - 1))
      return 1;
  else
      return 0; 
}

int wall_reached(filler_t *filler, info_t *info, pos_t pos){
  for(int i = 0; i < info->fig_h; i++){
    for(int j = 0; j < info->fig_w; j++){
      if(info->figure[i][j] == '*'){
        if(elem_is_wall(filler, pos.x+j, pos.y+i))
          return 1;
       }
     }
  }
  return 0;
    return elem_is_wall(filler, pos.x, pos.y);
}

pos_t    make_diagonals(filler_t *filler, info_t *info){
    pos_t      res;
    static int dir = 0;

    res = silly_direction(filler, info, dir);
    
    if(res.x < 0) // no matches found
      return res;
    
    if(wall_reached(filler, info, res) || enemy_near(res.x, res.y, filler, info)){
    
      if(dir <= 4)
        dir++;
      }
    return res;
}

int set_dir(filler_t *filler, info_t *info){
    pos_t my;
    
    my = silly_direction(filler, info, 0);
    if(my.y < filler->h/3){
      if(my.x < 2*(filler->w/3))
        return 4;
    }

    if(my.y > 2*(filler->h/3)){
      if(my.x < 2*(filler->w/3))
        return 1;
    }
    
    return -1;
}

pos_t    leave_edge(filler_t *filler, info_t *info){
  static int first_turn = 1;
  static int dir;
  pos_t res;

  if(first_turn){
    dir = set_dir(filler, info);
    first_turn = 0; 
  }

  if(dir == -1){
    stage = 1;
    return make_diagonals(filler, info); 
  }
  else{
    res = silly_direction(filler, info, dir);

    if(wall_reached(filler, info, res))
      stage = 1;
  
    return res;
  }
}

pos_t    play(filler_t *filler, info_t *info){
    if(stage == 0)//Leave edge
        return leave_edge(filler, info);
    else
     return make_diagonals(filler, info);
}
