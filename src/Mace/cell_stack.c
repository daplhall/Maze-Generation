#include "Mace/cell_stack.h"
#include "cell.h"
#include "cell_stack.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define T Mace_Stack_T

struct elem {
	struct Mace_Cell *cell;
	struct elem *link;
};

struct T {
	struct elem *head;
	size_t count;
};

struct T *
Mace_stack_create()
{
	struct T *stack;
	if ((stack = malloc(sizeof(*stack))) == NULL) {
		printf("Error: malloc failed in stack create");
		exit(1);
	}
	stack->head = NULL;
	stack->count = 0;
}

void
Mace_stack_destory(struct T *stack)
{
	assert(stack);
	for (struct elem *next, *head = stack->head; head; head = next) {
		next = head->link;
		free(head);
	}
	free(stack);
}

struct Mace_Cell *
Mace_stack_pop(struct T *stack)
{
	struct elem *e;
	struct Mace_Cell *cell;

	assert(stack && stack->count);
	e = stack->head;
	stack->head = e->link;
	stack->count--;
	cell = e->cell;
	free(e);
	return cell;
}

void
Mace_stack_push(struct T *stack, struct Mace_Cell *cell)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}
	e->cell = cell;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

size_t
Mace_stack_length(struct T *stack)
{
	return stack->count;
}