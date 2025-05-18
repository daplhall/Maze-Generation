#ifndef VALSTACK_H
#define VALSTACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>

#define T Valstack
typedef struct T *T;

enum Valstack_item_type {
	VALSTACK_CHAR = 0,
	VALSTACK_INT,
	VALSTACK_LONG,
	VALSTACK_POINTER,
	VALSTACK_FLOAT,
	VALSTACK_DOUBLE
};

T Valstack_create();
void Valstack_destory(T stack);
void Valstack_pop(T stack, void *out);
void Valstack_push(T stack, void *item, enum Valstack_item_type type);
void Valstack_push_char(T stack, char item);
void Valstack_push_int(T stack, int item);
void Valstack_push_long(T stack, long item);
void Valstack_push_pointer(T stack, void *item);
void Valstack_push_float(T stack, float item);
void Valstack_push_double(T stack, double item);
size_t Valstack_length(T stack);

#undef T

#ifdef __cplusplus
}
#endif
#endif // MACE_CELL_STACK_H