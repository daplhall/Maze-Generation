#include "maze.h"
#include "coords.h"
#include "stack.h"
#include "valstack.h"
#include <assert.h>
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

static void
draw_cells(struct T *maze, char *canvas, int height, int width)
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
}

static void
draw_solution(Stack solution, char path, char *canvas, int height, int width)
{
	struct Cell *cell, *prev = NULL;
	bool start = true;

	while ((cell = Stack_pop(solution)) != NULL) {
		int i, j;
		struct Coords canva_coord;
		canva_coord = coords_to_canvas(cell->coords);
		i = canva_coord.i;
		j = canva_coord.j;
		if (start) {
			canvas[j + width * i] = 'E';
			start = false;
		} else if (Stack_length(solution) == 0) {
			canvas[j + width * i] = 'S';
		} else {
			canvas[j + width * i] = path;
		}
		if (prev) {
			struct Coords diff;
			int di, dj;

			diff = Coords_sub(prev->coords, cell->coords);
			di = i + diff.i;
			dj = j + diff.j;
			canvas[dj + width * di] = path;
			// fill connection
		}
		prev = cell;
	}
}

static int
try_add_neighbor(
    struct Cell *const temp, struct Cell *const cell, int *n, struct Cell **c)
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
find_neighbor(struct Cell *const cell, struct T *const maze)
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

static void
generate(struct T *maze)
{
	Stack stack;
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
			neigh->connected[0] = cell;
			Stack_push(stack, cell);
			Stack_push(stack, neigh);
		}
	}
	Stack_destory(stack);
}

Stack
solve(struct T *maze, struct Cell *const end)
{
	Valstack visited_stack;
	Stack cell_stack;
	struct Cell *cell;

	visited_stack = Valstack_create();
	cell_stack = Stack_create();

	Valstack_push_int(visited_stack, 0);
	Stack_push(cell_stack, maze->cells);
	while ((cell = Stack_pop(cell_stack)) != NULL) {

		int i;
		Valstack_pop(visited_stack, &i);
		if (cell == end)
			return cell_stack;
		if (i > 3 || cell->connected[i] == NULL)
			continue;
		Valstack_push_int(visited_stack, i + 1);
		Stack_push(cell_stack, cell);
		Valstack_push_int(visited_stack, 1);
		Stack_push(cell_stack, cell->connected[i]);
	}
	assert(0);
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

static void
canvas_fill(char *canvas, char fillament, int height, int width)
{
	int i;

	for (i = 0; i < height * width; ++i)
		canvas[i] = fillament;
	canvas[i] = '\0';
}
static void
canvas_display(char *canvas, int width)
{
	char *c;
	int i;
	for (c = canvas, i = 1; *c; ++i) {
		if (i % (width + 1) == 0) {
			putchar('\n');
		} else {
			putchar(*c++);
		}
	}
}

struct T *
Maze_create(int rows, int cols)
{
	struct T *maze;
	struct Cell *cells;
	int len = rows * cols;
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
	int height, width;
	char *canvas;

	height = 2 * maze->rows + 1;
	width = 2 * maze->cols + 1;
	canvas = canvas_create(height, width);
	canvas_fill(canvas, wall, height, width);
	draw_cells(maze, canvas, height, width);
	canvas_display(canvas, width);
	free(canvas);
}

void
Maze_solution(struct T *maze, char wall, char path)
{
	Stack solution;
	int height, width;
	char *canvas;

	height = 2 * maze->rows + 1;
	width = 2 * maze->cols + 1;
	canvas = canvas_create(height, width);
	canvas_fill(canvas, wall, height, width);
	draw_cells(maze, canvas, height, width);
	if ((solution = solve(
		 maze, maze->cells + maze->rows * maze->cols - 1)) == NULL) {
		printf("Error: No solution found in maze_solutuon\n");
	} else {
		draw_solution(solution, path, canvas, height, width);
	}
	canvas_display(canvas, width);
	free(canvas);
}