#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include "../include/export.h"
#include "../include/env.h"

/**
*Causes memory leaks
*/
static int export (int c, char *args[]){
    char *k = malloc((strlen(args[1])+1)*sizeof(char));
    char *v = malloc((strlen(args[2])+1)*sizeof(char));
    strcpy(k, args[1]);
    strcpy(v, args[2]);
    new_var(k, v);
    printf("$_>\n");
}

int export_validate(int argc, char** args){
    return 1;
}

int export_execute(int argc, char** args){
    return export(argc, args);
}
