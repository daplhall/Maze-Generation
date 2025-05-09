#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>

#define T Stack_T
typedef struct T *T;

T Stack_create();
void Stack_destory(T stack);
void *Stack_pop(T stack);
void Stack_push(T stack, void *item);
size_t Stack_length(T stack);

#ifdef __cplusplus
}
#endif

#undef T
#endif // MACE_CELL_STACK_H