#include "maze.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char *argv[])
{
	Maze_T maze;
	// srand(time(0));
	srand(132122);
	maze = Maze_create(3, 3);
	Maze_display(maze, '@');
	free(maze);
	return EXIT_SUCCESS;
}