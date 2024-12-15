#include "coords.h"
#include <math.h>

#define T Coords

struct T
Coords_add(struct T lhs, struct T rhs)
{
	return (struct T){lhs.i + rhs.i, lhs.j + rhs.j};
}

struct T
Coords_sub(struct T lhs, struct T rhs)
{
	return (struct T){lhs.i - rhs.i, lhs.j - rhs.j};
}

double
Coords_norm(struct T coor)
{
	return sqrtf(pow(coor.i, 2) + pow(coor.j, 2));
}