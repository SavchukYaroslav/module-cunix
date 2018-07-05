#ifndef _HALLOC_H_
#define _HALLOC_H_ 
#define align4(x) (((((x) -1) > >2) < <2)+4)
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>   
#include <stddef.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
   

void *halloc(size_t size);
void free(void *ptr);


#endif
