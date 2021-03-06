#ifndef N
#define N 256
#endif


#ifndef _STDIO_H
#include <stdio.h>
#endif


#ifndef _STDLIB_H
#include <stdlib.h>
#endif


#ifndef _STRING_H
#include <string.h>
#endif


#include "structures/int-stack.h"
#include "structures/char-stack.h"
#include "decimal-roman.h"


/* *********************** */
/* Working with expression */
/* *********************** */

/* Distributes the order of operations */
int precedence(char operator) {
	if(operator == '+' || operator == '-')
		return 1;
	if(operator == '*' || operator == '/')
		return 2;
	if(operator < 0)
		return 3;
	return -1;
}


/* Apply operator to numbers */
void apply_operator(IntStack **stack, char operator) {
	if(operator < 0 ) {
		int x = int_pop(*stack);
		switch(-operator) {
			case '+': int_push(*stack, x); break;
			case '-': int_push(*stack, -x); break;
		}
	} else {
		int y = int_pop(*stack);
		int x = int_pop(*stack);
		if(operator == '/' && y == 0) {
			printf("error: division by zero");
			exit(1);
		}
		switch(operator) {
			case '+': int_push(*stack, x + y); break;
			case '-': int_push(*stack, x - y); break;
			case '*': int_push(*stack, x * y); break;
			case '/': int_push(*stack, x / y); break;
		}
	}
}


/* Checks if an operator is unary */
int is_unary(char c) {
	return c == '+' || c == '-';
}


/* Checks if a character is an operator */
int is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/'; 
}


/* Checks if a character is delimiter */
int is_delimiter(char c) {
	return c == ' ' || c == '\t' || c == '\v';
}


/* Checks if a character is number */
int is_number(char c) {
	return strchr("IVXLCDMZ", c) != NULL ? 1 : 0;
}


/* Checks for brackets match */
void check_brackets(char *expression) {

	int open_brackets = 0, close_brackets = 0;
	int len = strlen(expression);

	for(int i = 0; i < len; i++) {
		if(expression[i] == '(')
			open_brackets++;
		else if(expression[i] == ')')
			close_brackets++;
	}

	if(open_brackets != close_brackets) {
		printf("error: number of opening brackets not equal to number of closing brackets");
		exit(1);
	}
}


/* Evaluates an expression */
char *evaluate(char *expression) {
	
	check_brackets(expression);
	IntStack *values = create_int_stack(N);
	CharStack *ops = create_char_stack(N);
	int i, len = strlen(expression);
	int may_be_unary = 0, break_point = 0;

	for(i = 0; i < len; i++) {
		if(is_delimiter(expression[i])) {	/* Current char from expression is delimiter */
			continue;
		} else if(expression[i] == '(') {	/* Current char from expression is open bracket */
			char_push(ops, expression[i]);
			may_be_unary = 1;
		} else if(is_number(expression[i])) {	/* Current char from expression is roman number */
			char val[N] = "";
			while(i < len && is_number(expression[i])) {
				strncat(val, &expression[i], 1);
				i++;
			}
			int_push(values, roman_to_decimal(val));
			i--;
			may_be_unary = 0;
		} else if(expression[i] == ')') {	/* Current char from expression is close bracket*/
			while(!char_is_empty(ops) && char_peek(ops) != '(') {
				char op = char_pop(ops);
				apply_operator(&values, op);
			}
			if(!char_is_empty(ops))
				char_pop(ops);
			may_be_unary = 0;
		} else if(is_operator(expression[i])) {	/* Current char from expression is operator */
			char current_operator = expression[i];
			if(may_be_unary && is_unary(current_operator))
				current_operator = -current_operator;
			while(!char_is_empty(ops) && (
						(current_operator >= 0 && precedence(char_peek(ops)) >= precedence(current_operator)) ||
						(current_operator < 0 && precedence(char_peek(ops)) > precedence(current_operator))
						)) {
				char op = char_pop(ops);
				apply_operator(&values, op);
			}
			char_push(ops, current_operator);
			may_be_unary = 1;
		} else {	/* Current char from expression is unacceptable value for expression */
			printf("error: bad input value %c\n", expression[i]);
			break_point = 1;
			break;
		}
	}

	while(!char_is_empty(ops) && !break_point) {
		char op = char_pop(ops);
		apply_operator(&values, op);
	}

	if(!break_point)
		return decimal_to_roman(int_pop(values));
	else
		exit(1);
}
