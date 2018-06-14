#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int my_atoi(const char *nptr){
  int n = strlen(nptr);
  int res = 0;
  int mult = 1;
  char c;
  int i = n-1;

  while ((i>=0) && (('0'>nptr[i])||(nptr[i]>'9')))
    i--;
  for(; i>=0 ; i--){
    c = nptr[i];
    if((c == '-') || !(('0' <= c)&&( c <= '9')))
      break;
    res = res + mult*(c - '0' );
    mult = mult*10;
  }
  return c == '-'?-res:res;
}
