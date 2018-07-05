#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "queens.h"
#include "coord.h"

/*
 * Returns 1 if the cell with coordinates <x,y> contains 
 * a queen.
 */
int coords_of_queen(coord* queens, int num, int x, int y){
	for(int i = 0; i < num; i++){
		if((queens[i].x == x) && (queens[i].y == y))
			return 1;
	}
	return 0;
}

/* 
 * Creates a 2d board that contains queens
 */
Cell** create_board2d(coord* queens, int queens_num, int size){
	if(size == 0)
		return NULL;
	Cell** board2d = calloc(size, sizeof(Cell*));
	for(int x = 0; x < size; x++){
		board2d[x] = calloc(size, sizeof(Cell));
		for(int y = 0; y < size; y++){
			if(coords_of_queen(queens, queens_num, x, y))
				board2d[x][y].figure = 'Q';
			else
				board2d[x][y].figure = '-';
		}
	}
	return board2d;
}

void free_board2d(Cell** queens, int size){
	for(int x = 0; x < size; x++){
		free(queens[x]);
	}
	free(queens);
}
void print_queens(coord* queens, int queens_num, int size){
	Cell** board2d = create_board2d(queens, queens_num, 8);
	printf("  0 1 2 3 4 5 6 7\n");
	for(int y = 0; y < size; y++){
		printf("%d ", y);
		for(int x = 0; x < size; x++){
			printf("%c ", board2d[x][y].figure);
		}
		printf("\n");
	}
	free_board2d(board2d, size);
}
