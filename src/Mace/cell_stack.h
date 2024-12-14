#ifndef MACE_CELL_STACK_H
#define MACE_CELL_STACK_H

#include "cell.h"
#include <ctype.h>

#define T Mace_Stack_T
typedef struct T *T;

T Mace_stack_create();
void Mace_stack_destory(T);
struct Mace_Cell *Mace_stack_pop(T);
void Mace_stack_push(T, struct Mace_Cell *);
size_t Mace_stack_length(T);

#undef T
#endif // MACE_CELL_STACK_H