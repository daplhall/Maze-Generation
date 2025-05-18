/*
	Another impelemnation of this is where the type value is not stored
	in the element but rather in the stack, so the stack is 1 type

*/
#include "stack.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define T Stack

struct elem {
	void *item;
	struct elem *link;
};

struct T {
	struct elem *head;
	size_t count;
};

struct T *
Stack_create()
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
Stack_destory(struct T *stack)
{
	assert(stack);
	for (struct elem *next, *head = stack->head; head; head = next) {
		next = head->link;
		free(head);
	}
	free(stack);
}

void *
Stack_pop(struct T *stack)
{
	struct elem *e;
	void *item;

	assert(stack);
	if (stack->count < 1)
		return NULL;
	e = stack->head;
	stack->head = e->link;
	stack->count--;
	item = e->item;
	free(e);
	return item;
}

void
Stack_push(struct T *stack, void *item)
{
	struct elem *e;

	if ((e = malloc(sizeof(*e))) == NULL) {
		printf("Error: malloc failed in stack push");
		exit(1);
	}
	e->item = item;
	e->link = stack->head;
	stack->head = e;
	stack->count++;
}

size_t
Stack_length(struct T *stack)
{
	return stack->count;
}