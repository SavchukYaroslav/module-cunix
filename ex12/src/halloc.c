#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_block *t_block;

#define BLOCK_SIZE sizeof(struct s_block)

#define align4(x) (((((x)-1)>>2)<<2)+4)

struct s_block {
  size_t size;
  struct s_block *next;
  struct s_block *prev;
  int free;
  void *ptr;
  char data [1];
};

t_block   base = NULL;

t_block find_block (t_block *last , size_t size){
  t_block b=base;
  while (b && !(b->free && b->size >= size )) {
    *last = b;
    b = b->next;
  }
  return (b);
}

t_block extend_heap (t_block last , size_t s){
  t_block b;
  
  b = sbrk (0);
  if (sbrk( BLOCK_SIZE + s) == (void*) -1)
    return (NULL );
  b->size = s;
  b->next = NULL;
  if (last)
    last ->next = b;
  
  b->free = 0;
  return (b);
}

void split_block (t_block b, size_t s){
  t_block new;
  new = (t_block)(b->data + s);
  new ->size = b->size - s - BLOCK_SIZE ;
  new ->next = b->next;
  new ->free = 1;
  b->size = s;
  b->next = new;
}

void     *halloc(size_t size ){
  if(size == 0)
    return NULL;
  t_block    b;
  t_block    last;
  size_t     s;
  
  s = align4(size );
 
  if (base) {
 /* First find a block */
  last = base;
  b = find_block (&last ,s);
  if (b) {
 /* can we split */
  if ((b->size - s) >= ( BLOCK_SIZE + 4))
    split_block (b,s);
    b->free =0;
  } else {
 /* No fitting block , extend the heap */
   b = extend_heap (last ,s);
  if (!b)
   return(NULL );
  }
} 
else {
 /* first time */
  b = extend_heap (NULL ,s);
  if (!b)
   return(NULL );
  base = b;
}

return(b->data );
}

t_block get_block (void *p) {
 char *tmp;
 tmp = p;
 return (p = tmp -= BLOCK_SIZE );
 }


t_block fusion(t_block b){
  if (b->next && b->next ->free ){
    b->size += BLOCK_SIZE + b->next ->size;
    b->next = b->next ->next;
    if (b->next)
      b->next ->prev = b;
  }
  return (b);
}

int valid_addr (void *p){
   if (base){
     if ( ((t_block)p)>base && p<sbrk (0)){
       return (p == ( get_block (p))->ptr );
     }
   }
   return (0);
}
void my_free(void *p){
  t_block b;

  if (valid_addr (p)){
    b = get_block (p);
    b->free = 1;
 /* fusion with previous if possible */
    if(b->prev && b->prev ->free)
    b = fusion(b->prev );
 /* then fusion with next */
    if (b->next)
      fusion(b);
    else{
      if (b->prev)
        b->prev ->next = NULL;
      else
        base = NULL;
      brk(b);
    }
  }
}

/*
int main(){
 void* a = halloc(10);
 my_free(a);
}
*/
