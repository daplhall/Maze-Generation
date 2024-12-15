#include "coords.h"
#include "maze.h"
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T      Maze_T
#define NNEIGH 4

struct Cell {
	struct Cell *connected[NNEIGH];
	struct Coords coords;
	bool visited;
};

struct T {
	struct Cell *cells;
	int rows;
	int cols;
};

static struct Coords
coords_to_canvas(struct Coords coords)
{
	struct Coords new_coords;
	new_coords.i = 2 * coords.i + 1;
	new_coords.j = 2 * coords.j + 1;
	return new_coords;
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
		for (neigh = cell->connected, k = NNEIGH; *neigh && k;
		     --k, ++neigh) {
			int ih = i + (*neigh)->coords.i - cell->coords.i;
			int jh = j + (*neigh)->coords.j - cell->coords.j;
			canvas[jh + width * ih] = ' ';
		}
	}
	canvas[height * width] = '\0';
	return canvas;
}

// returns null if no non visited neighbors else return pointer
/*
	There is a problem in here eg. that in a 3x3 2,0 points to 1,2 because
	they are next to one another in the data. This implementation needs to
	be update such that the norm:
	1. |sum(temp.coords - cell.coords)| <= 1
	2. temp is within maze->cells + len
*/

static int
try_add_neighbor(struct Cell *temp, struct Cell *cell, int *n, struct Cell **c)
{
	struct Coords path;
	path = Coords_sub(temp->coords, cell->coords);
	if ((int)Coords_norm(path) == 1 && !temp->visited) {
		*c = temp;
		(*n)++;
		return 1;
	}
	return 0;
}

static struct Cell *
find_neighbor(struct Cell *const cell, struct T *maze)
{
	struct Cell **c, *neigh[NNEIGH], *temp;
	int cols, len;
	int n = 0;
	c = neigh;
	cols = maze->cols;
	len = maze->rows * cols;

	temp = cell + cols;
	if (temp < maze->cells + len)
		if (try_add_neighbor(temp, cell, &n, c))
			++c;
	temp = cell + 1;
	if (temp < maze->cells + len)
		if (try_add_neighbor(temp, cell, &n, c))
			++c;
	temp = cell - cols;
	if (temp >= maze->cells)
		if (try_add_neighbor(temp, cell, &n, c))
			++c;
	temp = cell - 1;
	if (temp >= maze->cells)
		if (try_add_neighbor(temp, cell, &n, c))
			++c;
	if (!n)
		return NULL;
	n *= rand() / (double)(RAND_MAX + 1);
	return neigh[n];
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

static char *
canvas_create(int height, int width)
{
	char *canvas;
	if ((canvas = malloc((height * width + 1) * sizeof(char))) == NULL) {
		printf("Error: calloc in maze_display didnt work");
		exit(0);
	}
	return canvas;
}

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
	int i, height, width;
	char *canvas, *c;
	height = 2 * maze->rows + 1;
	width = 2 * maze->cols + 1;
	canvas = canvas_create(height, width);
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
