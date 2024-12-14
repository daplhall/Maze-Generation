#ifndef MACE_CELL_H
#define MACE_CELL_H

#include <stdbool.h>

struct Mace_Coords {
	int i;
	int j;
};

struct Mace_Cell {
	struct Mace_Coords connected[4];
	struct Mace_Coords coords;
	bool visited;
};

#endif // MACE_CELL_H