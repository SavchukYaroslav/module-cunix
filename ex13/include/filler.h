#ifndef _FILLER_H_
#define _FILLER_H_


typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  stream_s
{
  char          *str;
  unsigned int  size;
  unsigned int  limit;
} 
              stream_t;

typedef struct  filler_s
{
  char           symbol;
  int            w; //board width
  int            h; //board height
  char         **board; //not freed till the end of the game
  char         **prev_board; //not freed till the end of the game
}               filler_t;

/* My types */
typedef struct  info_s
{
  int            fig_w;
  int            fig_h;  
  char         **figure;
}               info_t;



/*Functions for game logic*/
// void            start_game(filler_t *filler);
// pos_t           play(req_t *core, filler_t *filler);

/*Functions for printing*/
void            print_pos(pos_t p);

//Reading
void     read_inp(filler_t   *filler);

//Filler
filler_t     *create_filler();
void          destroy_filler(filler_t *filler);


#endif // _FILLER_H_