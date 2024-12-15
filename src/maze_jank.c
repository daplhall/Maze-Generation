#include "maze.h"
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T Maze_T

static struct Coords {
	int i;
	int j;
};

static struct Cell {
	struct Cell *connected[4];
	struct Coords coords;
	bool visited;
};

struct T {
	struct Cell *cells;
	int rows;
	int cols;
};

static int generate(struct T *);
static struct Cell *find_neighbor(struct Cell *const, struct T *);
static struct Coords coords_to_canvas(struct Coords);
static char *draw(struct T *, char *, int, int);

struct T *
Maze_create(int rows, int cols)
{
	struct T *maze;
	struct Cell *cells;
	int i, len = rows * cols;
	if ((maze = malloc(sizeof(*maze))) == NULL) {
		printf("Error: malloc failed in maze create\n");
		exit(1);
	}
	maze->rows = rows;
	maze->cols = cols;
	if ((maze->cells = calloc(len, sizeof(struct Cell))) == NULL) {
		printf("Error: malloc failed in maze create\n");
		exit(1);
	}
	cells = maze->cells;
	for (int i = 0; i < maze->rows; ++i) {
		for (int j = 0; j < maze->cols; ++j) {
			cells->coords.i = i;
			cells->coords.j = j;
			cells++;
		}
	}
	generate(maze);
	return maze;
}

void
Maze_destroy(struct T *maze)
{
	free(maze->cells);
	free(maze);
}

void
Maze_display(struct T *maze, char wall)
{
	int height = 2 * maze->rows + 1, width = 2 * maze->cols + 1;
	int i;
	char *canvas, *c;
	if ((canvas = malloc((height * width + 1) * sizeof(char))) == NULL) {
		printf("Error: calloc in maze_display didnt work");
		exit(0);
	}
	for (i = 0; i < height * width; ++i)
		canvas[i] = wall;
	canvas[i] = '\0';
	canvas = draw(maze, canvas, height, width);
	for (c = canvas, i = 1; *c; ++i) {
		if (i % (width + 1) == 0) {
			putchar('\n');
		} else {
			putchar(*c++);
		}
	}
	free(canvas);
}

static char *
draw(struct T *maze, char *canvas, int height, int width)
{
	struct Cell *cell;
	int len = maze->cols * maze->rows;

	for (cell = maze->cells; len; --len, ++cell) {
		struct Cell **neigh;
		struct Coords canva_coords;
		int i, j, k;

		canva_coords = coords_to_canvas(cell->coords);
		i = canva_coords.i;
		j = canva_coords.j;
		canvas[j + width * i] = ' ';
		for (neigh = cell->connected, k = 4; *neigh && k;
		     --k, ++neigh) {
			int i_ = i + (*neigh)->coords.i - cell->coords.i;
			int j_ = j + (*neigh)->coords.j - cell->coords.j;
			canvas[j_ + width * i_] = ' ';
		}
	}
	canvas[height * width] = '\0';
	return canvas;
}

static struct Coords
coords_to_canvas(struct Coords coords)
{
	struct Coords new_coords;
	new_coords.i = 2 * coords.i + 1;
	new_coords.j = 2 * coords.j + 1;
	return new_coords;
}

static int
generate(struct T *maze)
{
	Stack_T stack;
	struct Cell *cell, *neigh;

	stack = Stack_create();
	Stack_push(stack, maze->cells);
	while ((cell = Stack_pop(stack)) != NULL) {
		cell->visited = true;
		neigh = find_neighbor(cell, maze);
		if (neigh) {
			int i;
			for (i = 0; cell->connected[i]; ++i)
				;
			cell->connected[i] = neigh;
			Stack_push(stack, cell);
			Stack_push(stack, neigh);
		}
	}
	Stack_destory(stack);
}

// returns null if no non visited neighbors else return pointer
/*
	There is a problem in here eg. that in a 3x3 2,0 points to 1,2 because
	they are next to one another in the data. This implementation needs to
	be update such that the norm: |sum(temp.coords - cell.coords)| <= 1
	and temp is within maze->cells + len
	this should fix the bug, however i fell the general structure of this
	implementation is heavly flawed, so i will rewrite it
*/
static struct Cell *
find_neighbor(struct Cell *const cell, struct T *maze)
{
	struct Cell *temp, *cells = maze->cells;
	struct Cell *neigh[4], **c = neigh;
	float r;
	int rows = maze->rows, cols = maze->rows;
	int i, n = 0, len = rows * cols;

	temp = cell + cols;
	if (temp < maze->cells + len && temp->coords.i < maze->rows &&
	    !temp->visited) {
		*c++ = temp;
		++n;
	}
	temp = cell + 1;
	if (temp < maze->cells + len && temp->coords.j > cell->coords.j &&
	    !temp->visited) {
		*c++ = temp;
		++n;
	}
	temp = cell - cols;
	if (temp >= maze->cells && temp->coords.i >= 0 && !temp->visited) {
		*c++ = temp;
		++n;
	}
	temp = cell - 1;
	if (temp >= maze->cells && temp->coords.j >= 0 && !temp->visited) {
		*c++ = temp;
		++n;
	}
	if (!n)
		return NULL;
	r = rand() / (double)(RAND_MAX + 1);
	i = (n * r);
	return neigh[i];
}