#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "queens.h"
#include "coord.h"
#include "print.h"
#include "logics.h"

int     create_coord_queens(Cell** table, int size, coord** queens){
	*queens = (coord*)malloc(size*size*sizeof(coord));

	int    count = 0;  
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(table[i][j].figure == 'Q'){
				(*queens)[count].x = j;
				(*queens)[count].y = i;
				count++;
			}
		}
	}
	*queens = (coord*)realloc(*queens, count);

	return count;
}

void make_cells(Cell** table, coord* queens, int len){
	for(int i = 0; i < len;i++){
		table[queens[i].x][queens[i].y].figure = 'Q';
	}
}

void place_queens(Cell **table, int size){
	coord*   queens;
	int      n;

	n = create_coord_queens(table, size, &queens);
	q(queens, n, size-n, size);
	make_cells(table, queens, size);

	free(queens);
}
