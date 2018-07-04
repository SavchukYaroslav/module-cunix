#include "../include/halloc.h"
#define ALIGN(size) (((((size)-1)>>3)<<3)+8)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) 

void *halloc(size_t size) {
  if( (size != 0) && (size < 100000))
  {
    size_t blk_size = ALIGN(size + SIZE_T_SIZE);
    //printf("before header:%p\n",sbrk(0));
    size_t *header = sbrk(blk_size);
    //printf("after header:%p\n",header);
    //printf("return:%p\n",header + SIZE_T_SIZE);
    return (void *)header + SIZE_T_SIZE;
  }
  else
  {
    return (NULL);
  }
}

void free(void *ptr) {
  if(ptr != NULL)
  {
    size_t *header = ptr - SIZE_T_SIZE;
    //printf("%p\n",header);
    *header = *header & ~*header;
    // printf("%p\n",header);
 
  }
}

/*
int main()
{
  halloc(33);
//  test_small();
  // printf("%d\n",sbrk(0));
  // printf("%d\n",sbrk(1)); 
  // printf("%d",sbrk(2));
}
*/

