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
	maze = Maze_create(15, 35);
	Maze_display(maze, '@');
	Maze_destroy(maze);
	return EXIT_SUCCESS;
}