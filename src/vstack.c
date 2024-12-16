#include "stack.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define T Stack_T

enum item_type {
	STACK_CHAR = 0,
	STACK_INT,
	STACK_LONG,
	STACK_POINTER,
	STACK_FLOAT,
	STACK_DOUBLE
};

struct elem {
	union {
		double item_lf;
		float item_f;
		void *item_p;
		long item_ld;
		int item_d;
		char item_c;
	};
	enum item_type type;
	struct elem *link;
};

struct T {
	struct elem *head;
	size_t count;
};

struct T *
VStack_create()
{
	struct T *stack;
	if ((stack = malloc(sizeof(*stack))) == NULL) {
		printf("Error: malloc failed in stack create");
		exit(1);
	}
	stack->head = NULL;
	stack->count = 0;
	return stack;
}

void
VStack_destory(struct T *stack)
{
	assert(stack);
	for (struct elem *next, *head = stack->head; head; head = next) {
		next = head->link;
		free(head);
	}
	free(stack);
}

void
VStack_pop(struct T *stack, void *out)
{
	struct elem *e;

	assert(stack);
	assert(stack->count < 1);
	e = stack->head;
	stack->head = e->link;
	stack->count--;
	switch (e->type) {
	case STACK_CHAR:
		*(char *)out = e->item_c;
		break;
	case STACK_INT:
		*(int *)out = e->item_d;
		break;
	case STACK_LONG:
		*(long *)out = e->item_ld;
		break;
	case STACK_POINTER:
		*(void **)out = e->item_p;
		break;
	case STACK_FLOAT:
		*(char *)out = e->item_f;
		break;
	case STACK_DOUBLE:
		*(char *)out = e->item_lf;
		break;
	}
	free(e);
}

void
VStack_push(struct T *stack, void *item, enum item_type type)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}
	switch (type) {
	case STACK_CHAR:
		e->type = type;
		e->item_c = *(char *)item;
		break;
	case STACK_INT:
		e->type = type;
		e->item_d = *(int *)item;
		break;
	case STACK_LONG:
		e->type = type;
		e->item_ld = *(long *)item;
		break;
	case STACK_POINTER:
		e->type = type;
		e->item_p = *(void **)item;
		break;
	case STACK_FLOAT:
		e->type = type;
		e->item_f = *(float *)item;
		break;
	case STACK_DOUBLE:
		e->type = type;
		e->item_lf = *(double *)item;
		break;
	}
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

size_t
VStack_length(struct T *stack)
{
	return stack->count;
}