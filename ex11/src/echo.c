#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include "../include/echo.h"

// static int ls(int c, char *v[]){
    
// }

//         struct dirent *pDirent;
//         DIR *pDir;

//         if (c < 2) {
//             printf ("$_>Usage: ls <dirname>\n");
//             return 1;
//         }

//         pDir = opendir (v[1]);
//         if (pDir == NULL) {
//             printf ("$_>Cannot open directory '%s'\n", v[1]);
//             return 1;
//         }

//         printf("$_>");
//         while ((pDirent = readdir(pDir)) != NULL) {
//             if(strcmp(pDirent->d_name, ".") && strcmp(pDirent->d_name, ".."))
//                 printf ("%s ", pDirent->d_name);
//         }
//         printf("\n");
//         closedir (pDir);
//         return 1;
// }
static int ls(int c, char *v[]){
    printf("$_> Echo worked\n");
}

int echo_validate(int argc, char** args){
    return 1;
}

int echo_execute(int argc, char** args){
    return ls(argc, args);
}
