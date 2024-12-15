#ifndef STACK_H
#define STACK_H

#include <ctype.h>

#define T Stack_T
typedef struct T *T;

T Stack_create();
void Stack_destory(T stack);
void *Stack_pop(T stack);
void Stack_push(T stack, void *item);
size_t Stack_length(T stack);

#undef T
#endif // MACE_CELL_STACK_H