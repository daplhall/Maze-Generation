#ifndef COORDS_H
#define COORDS_H

#ifdef __cplusplus
extern "C" {
#endif

#define T Coords

struct T {
	int i;
	int j;
};

struct T Coords_add(struct T lhs, struct T rhs);
struct T Coords_sub(struct T lhs, struct T rhs);
double Coords_norm(struct T x);

#ifdef __cplusplus
}
#endif

#undef T
#endif // COORDS_H