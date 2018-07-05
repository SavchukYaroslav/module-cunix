#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "block.h"

t_block   base = NULL;

size_t align8(size_t x)
{
	return ((((x-1)>>3)<<3)+8);
}

t_block      find_block (t_block *last , size_t size)
{
  t_block b;

	b = base;
  while (b && !(b->free && b->size >= size )) 
	{
    *last = b;
    b = b->next;
  }

  return b;
}

t_block    new_chunk (t_block last , size_t s)
{
  t_block    b;
  
  b = sbrk (s);
  if(sbrk(BLOCK_SIZE + s) == (void*)-1)
    return (NULL );

  b->size = s;
  b->next = NULL;
  b->free = 0;
	
	if (last)
	{
    last->next = b;
		b->prev = last;
	}

  return b;
}

void      split_block (t_block b, size_t s)
{
  t_block     new;

  new = (t_block)(b->data + s);
  new ->size = b->size - s - BLOCK_SIZE ;
  new ->next = b->next;
  new ->free = 1;
	new->prev = b;
  b->size = s;
  b->next = new;
}

void      *halloc(size_t size)
{
  t_block    b;
  size_t     s;
	
	if(size == 0)
    return NULL;
	  
  s = align8(size);
 
  if (base)
	{
  	b = find_block (&base, s);

		if (b)
		{
    	if ((b->size - s) >= ( BLOCK_SIZE + sizeof(size_t)))
      	split_block (b,s);
    	b->free =0;
  	} 
  	else 
		{
			t_block last;

			last = base;
			while(last->next)
				last = last->next;

  		b = new_chunk(last, s);
  		if (!b)
   			return NULL;
  	}
	} 
	else 
	{
  	b = new_chunk (NULL ,s);
  	if (!b)
   		return NULL;
  	base = b;
	}

  return b->data;
}

t_block      get_block (void *p) 
{
  return p - BLOCK_SIZE; 
}

t_block     merge(t_block b)
{
  if(b->next && b->next->free)
	{
    b->size += BLOCK_SIZE + b->next->size;
    b->next = b->next->next;

    if(b->next)
      b->next->prev = b;
  }

  return b;
}

int     ptr_is_valid (void *p)
{
return ((base)
			 &&(p > (void*) base)
			 &&(p < sbrk(0))
       &&(p == (get_block (p))));
}

void my_free(void *p)
{
  t_block     b;

  if (ptr_is_valid (p))
	{
    b = get_block (p);
    b->free = 1;

    if(b->prev && b->prev->free)
    	b = merge(b->prev);

    if (b->next)
      merge(b);
    else
		{
      if (b->prev)
        b->prev->next = NULL;
      else
        base = NULL;
      brk(b);
    }
  }
}
