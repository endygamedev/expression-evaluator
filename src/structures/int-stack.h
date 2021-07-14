#ifndef _STDIO_H
#include <stdio.h>
#endif


#ifndef _STDLIB_H
#include <stdlib.h>
#endif


/* *********************************** */
/* Stack structure with integer field  */
/* *********************************** */

typedef struct IntStack {
	int top;
	unsigned int capacity;
	int *array;
} IntStack;


/* Initialize IntStack */
IntStack *create_int_stack(unsigned int capacity) {
	IntStack *s = (IntStack *)malloc(sizeof(IntStack));
	s->capacity = capacity;
	s->top = -1;
	s->array = (int *)malloc(s->capacity * sizeof(int));
	return s;
}


/* Checks for stack overflow */
int int_is_full(IntStack *s) {
	return s->top == (int)(s->capacity - 1);
}


/* Checks the stack for fullness */
int int_is_empty(IntStack *s) {
	return s->top == -1;
}


/* Push item to stack */
void int_push(IntStack *s, int item) {
	if(int_is_full(s))
		return;
	s->array[++s->top] = item;
}


/* Pop item from stack */
int int_pop(IntStack *s) {
	if(int_is_empty(s)) {
		printf("error: IntStack is empty\n");
		exit(1);
	}
	return s->array[s->top--];
}
