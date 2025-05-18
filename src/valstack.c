#include "valstack.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define T Valstack

struct elem {
	union {
		double item_lf;
		float item_f;
		void *item_p;
		long item_ld;
		int item_d;
		char item_c;
	};
	enum Valstack_item_type type;
	struct elem *link;
};

struct T {
	struct elem *head;
	size_t count;
};

struct T *
Valstack_create()
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
Valstack_destory(struct T *stack)
{
	assert(stack);
	for (struct elem *next, *head = stack->head; head; head = next) {
		next = head->link;
		free(head);
	}
	free(stack);
}

void
Valstack_pop(struct T *stack, void *out)
{
	struct elem *e;

	assert(stack);
	assert(stack->count > 0);
	e = stack->head;
	stack->head = e->link;
	stack->count--;
	switch (e->type) {
	case VALSTACK_CHAR:
		*(char *)out = e->item_c;
		break;
	case VALSTACK_INT:
		*(int *)out = e->item_d;
		break;
	case VALSTACK_LONG:
		*(long *)out = e->item_ld;
		break;
	case VALSTACK_POINTER:
		*(void **)out = e->item_p;
		break;
	case VALSTACK_FLOAT:
		*(float *)out = e->item_f;
		break;
	case VALSTACK_DOUBLE:
		*(double *)out = e->item_lf;
		break;
	}
	free(e);
}

void
Valstack_push(struct T *stack, void *item, enum Valstack_item_type type)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}
	switch (type) {
	case VALSTACK_CHAR:
		e->type = type;
		e->item_c = *(char *)item;
		break;
	case VALSTACK_INT:
		e->type = type;
		e->item_d = *(int *)item;
		break;
	case VALSTACK_LONG:
		e->type = type;
		e->item_ld = *(long *)item;
		break;
	case VALSTACK_POINTER:
		e->type = type;
		e->item_p = *(void **)item;
		break;
	case VALSTACK_FLOAT:
		e->type = type;
		e->item_f = *(float *)item;
		break;
	case VALSTACK_DOUBLE:
		e->type = type;
		e->item_lf = *(double *)item;
		break;
	}
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}
void
Valstack_push_char(T stack, char item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VALSTACK_CHAR;
	e->item_c = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
Valstack_push_int(T stack, int item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VALSTACK_INT;
	e->item_d = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
Valstack_push_long(T stack, long item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VALSTACK_LONG;
	e->item_ld = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
Valstack_push_pointer(T stack, void *item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VALSTACK_POINTER;
	e->item_p = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
Valstack_push_float(T stack, float item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VALSTACK_FLOAT;
	e->item_f = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
Valstack_push_double(T stack, double item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VALSTACK_DOUBLE;
	e->item_lf = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

size_t
Valstack_length(struct T *stack)
{
	return stack->count;
}