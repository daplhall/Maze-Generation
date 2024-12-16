#include "vstack.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define T VStack_T

struct elem {
	union {
		double item_lf;
		float item_f;
		void *item_p;
		long item_ld;
		int item_d;
		char item_c;
	};
	enum VStack_item_type type;
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
	assert(stack->count > 0);
	e = stack->head;
	stack->head = e->link;
	stack->count--;
	switch (e->type) {
	case VSTACK_CHAR:
		*(char *)out = e->item_c;
		break;
	case VSTACK_INT:
		*(int *)out = e->item_d;
		break;
	case VSTACK_LONG:
		*(long *)out = e->item_ld;
		break;
	case VSTACK_POINTER:
		*(void **)out = e->item_p;
		break;
	case VSTACK_FLOAT:
		*(float *)out = e->item_f;
		break;
	case VSTACK_DOUBLE:
		*(double *)out = e->item_lf;
		break;
	}
	free(e);
}

void
VStack_push(struct T *stack, void *item, enum VStack_item_type type)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}
	switch (type) {
	case VSTACK_CHAR:
		e->type = type;
		e->item_c = *(char *)item;
		break;
	case VSTACK_INT:
		e->type = type;
		e->item_d = *(int *)item;
		break;
	case VSTACK_LONG:
		e->type = type;
		e->item_ld = *(long *)item;
		break;
	case VSTACK_POINTER:
		e->type = type;
		e->item_p = *(void **)item;
		break;
	case VSTACK_FLOAT:
		e->type = type;
		e->item_f = *(float *)item;
		break;
	case VSTACK_DOUBLE:
		e->type = type;
		e->item_lf = *(double *)item;
		break;
	}
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}
void
VStack_push_char(T stack, char item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VSTACK_CHAR;
	e->item_c = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
VStack_push_int(T stack, int item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VSTACK_INT;
	e->item_d = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
VStack_push_long(T stack, long item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VSTACK_LONG;
	e->item_ld = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
VStack_push_pointer(T stack, void *item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VSTACK_POINTER;
	e->item_p = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
VStack_push_float(T stack, float item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VSTACK_FLOAT;
	e->item_f = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

void
VStack_push_double(T stack, double item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}

	e->type = VSTACK_DOUBLE;
	e->item_lf = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

size_t
VStack_length(struct T *stack)
{
	return stack->count;
}