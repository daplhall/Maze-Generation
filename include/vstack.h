#ifndef STACKV_H
#define STACKV_H

#include <ctype.h>

#define T VStack_T
typedef struct T *T;

enum VStack_item_type {
	STACK_CHAR = 0,
	STACK_INT,
	STACK_LONG,
	STACK_POINTER,
	STACK_FLOAT,
	STACK_DOUBLE
};

T VStack_create();
void VStack_destory(T stack);
void VStack_pop(T stack, void *out);
void VStack_push(T stack, void *item, enum VStack_item_type type);
void VStack_push_char(T stack, char item);
void VStack_push_int(T stack, int item);
void VStack_push_long(T stack, long item);
void VStack_push_pointer(T stack, void *item);
void VStack_push_float(T stack, float item);
void VStack_push_double(T stack, double item);
size_t VStack_length(T stack);

#undef T
#endif // MACE_CELL_STACK_H