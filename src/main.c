#include "maze.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char *argv[])
{
	int t;
	t = time(0);
	srand(t);

	Maze_T maze;
	maze = Maze_create(6, 24);
	Maze_solution(maze, '@', '*');
	// Maze_display(maze, '@');
	Maze_destroy(maze);
	return EXIT_SUCCESS;
}