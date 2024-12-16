#include "maze_jank.h"
#include "vstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char *argv[])
{
	// srand(time(0));
	srand(132122);

	VStack_T stack;
	char c;
	int i;
	long l;
	char *p, *s = "Hello world!";
	float f;
	double d;
	stack = VStack_create();
	VStack_push_char(stack, 'h');
	VStack_push_int(stack, 42);
	VStack_push_long(stack, 420424023);
	VStack_push_pointer(stack, s);
	VStack_push_float(stack, 1.23);
	VStack_push_double(stack, 1.23424234242);

	VStack_pop(stack, &d);
	printf("%lf\n", d);
	VStack_pop(stack, &f);
	printf("%f\n", f);
	VStack_pop(stack, &p);
	printf("%s\n", p);
	VStack_pop(stack, &l);
	printf("%ld\n", l);
	VStack_pop(stack, &i);
	printf("%d\n", i);
	VStack_pop(stack, &c);
	printf("%c\n", c);

	return EXIT_SUCCESS;
}