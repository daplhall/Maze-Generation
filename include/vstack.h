#ifndef STACKV_H
#define STACKV_H

#include <ctype.h>

#define T Vstack_T
typedef struct T *T;

T VStack_create();
void VStack_destory(T stack);
void *VStack_pop(T stack);
void VStack_push(T stack, void *item);
size_t VStack_length(T stack);

#undef T
#endif // MACE_CELL_STACK_H