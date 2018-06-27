#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/filler.h"
#include "../include/stream.h"

#define READ_BUF_SIZE 64

 ssize_t readall(int fd, void * data, size_t count) {

   ssize_t bytesRead;

   char * dataPtr = data;

   size_t total = 0;

   while (count) {

    bytesRead = read(fd, dataPtr, count);

    /* we should check bytesRead for < 0 to return errors

      properly, but this is just sample code! */

    dataPtr += bytesRead;

    count -= bytesRead;

    total += bytesRead;

   }


   return total;

}

int     read_int(char delim){
  int       res;
  char      char_buf[1];
  int       bytesRead;
  char      str[2] = "\0";
  stream_t  *int_stream;

  int_stream = stream_init();

  bytesRead = read(0, char_buf, 1);
  while(char_buf[0] != delim){
    str[0] = char_buf[0];
    stream_append(int_stream, str);
    bytesRead = read(0, char_buf, 1);
  }
  res = atoi(int_stream->str);
  stream_destroy(int_stream);
  return res;
}

char**    read_map(int h, int w){
  char   char_buf[1];
  char   **map = (char**) malloc(h * sizeof(char*));
  for(int i = 0; i < h; i++){
    map[i] = (char*) malloc(w * sizeof(char));
    readall(0, map[i], w); // read horisontal line
    read(0, char_buf, 1); // read \n
  }
  return map;
}

char     read_symbol(){
  char res;
  int bytesRead;

  char   char_buf[1];
  bytesRead = read(0, char_buf, 1); //read my symbol
  res = char_buf[0];
  bytesRead = read(0, char_buf, 1); //read /n

  return res;
}


void     read_inp(stream_t* stream){
  char symbol;
  int w;
  int h;
  int fig_w;
  int fig_h;
  char** board;
  char** figure;

  char   buf[READ_BUF_SIZE];
  char   char_buf[1];
  int bytesRead;
  char str[2] = "\0";
  stream_t* int_stream;

  symbol = read_symbol();
  printf("SYMBOL: %c\n", symbol);

  w = read_int(' ');
  printf("WIDTH %d\n", w);

  h = read_int('\n');
  printf("HEIGHT %d\n", h);



  board = read_map(h, w);
    for(int i = 0; i < h; i++){
      for(int j = 0; j < w; j++)
        printf("%c ", board[i][j]);
      printf("\n");
    }

  FILE  *logger;
  logger = fopen("filler_new.log", "a");
  // fprintf(logger,"buffer: empty");

  fprintf(logger,"\n");
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++)
      fprintf(logger,"%c", board[i][j]);
      fprintf(logger,"\n");
  }
  fclose(logger); 
}