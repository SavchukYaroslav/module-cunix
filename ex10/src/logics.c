#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "queens.h"
#include "coord.h"
#include "print.h"

int     can_put_queen(coord* queens, int queens_num, int x, int y){
	for(int i = 0; i < queens_num; i++){
		if((queens[i].x == x) ||
				(queens[i].y == y) ||
				(abs(queens[i].x - x) == abs(queens[i].y - y)))
			return 0;
	}
	return 1;
}

coord**    place_queen(coord* queens, int queens_num, int size, int* ways_to_place_q){
	int counter;
	coord** res;

	res = calloc(64, sizeof(coord*));
	counter = 0;
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			if(can_put_queen(queens, queens_num, x, y)){
				coord* new_queens = malloc((queens_num+1)*sizeof(coord));
				memcpy(new_queens, queens, queens_num*sizeof(coord));
				new_queens[queens_num].x = x;
				new_queens[queens_num].y = y;
				print_queens(new_queens, queens_num+1, size);
				res[counter++] = new_queens;
			}
		}
	}

	*ways_to_place_q = counter;
	if(counter == 0)
		res = NULL;
	else
		res = realloc(res, counter*sizeof(coord*));

	return res;
}

void free_queens(coord** queens, int num){
	for(int i = 0; i < num; i++){
		free(queens[i]);
	}
}

coord** q(coord* queens, int num, int put_num, int size){

	int prev_placement_ways = 1;
	coord** prev_placement = &queens;

	for (int i = 0; i < put_num; i++){

		int cur_placement_ways = 0;
		coord** cur_placement = NULL;

		for(int j = 0; j < prev_placement_ways; j++){
			int one_placement_ways;
			coord** one_placement = place_queen(prev_placement[j], num+i, size, &one_placement_ways);
			if(one_placement_ways == 0){
				continue;
			}

			coord** new_cur_placement = realloc(cur_placement, (cur_placement_ways + one_placement_ways)*sizeof(coord*));
			cur_placement = new_cur_placement;
			memcpy(cur_placement + cur_placement_ways, one_placement, one_placement_ways*sizeof(coord*));

			cur_placement_ways += one_placement_ways;
		}

		prev_placement_ways = cur_placement_ways;
		prev_placement = cur_placement;

		if(!prev_placement){
			return NULL;
		}
	}
	return prev_placement;
}

