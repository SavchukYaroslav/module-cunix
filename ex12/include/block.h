#ifndef BLOCK_H_
#define BLOCK_H_

#include <stddef.h>

typedef struct s_block     *t_block;

#define BLOCK_SIZE sizeof(struct s_block)

struct      s_block {
	size_t            size;
	struct s_block   *next;
	struct s_block   *prev;
	int               free;
	char              data[1];
};


#endif
