#include <stdio.h>
#include <stdlib.h>
long ten_pow(int n){
  long res = 1;
  for(int i = 0; i < n; i++){
    res = res*10;
  }
  return res;
}

char* my_itoa(int nmbr){
  if(nmbr == 0){
    char* zero = malloc(sizeof(char));*zero = '0';
    return zero; 
  }
  char* str = calloc(12, sizeof(char));
  str[11] = '\0';
  int sign = 1;

  if(nmbr < 0){
    sign = -1;
    nmbr = nmbr*(-1);
  }
  int i = 0;
  for(long a = nmbr; a!=0 ;i++){
    int k = ten_pow(i+1);
    int r = a % k;
    a = a-r;
    r = r/(k/10);
    str[10-i] = '0'+r;
  }
  if(i == 10)
    str[1] = '1';
  if(sign == -1)
    str[10-i] = '-';
  else
    i--;
  char* res = &str[10-i];
  return res;
}
