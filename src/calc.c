/* Name: Roman expression evaluator */
/* Author: Egor Bronnikov */
/* Last edited: 14-07-2021 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expression.h"


#define N 256


void tests();	/* Runs tests */
void input();	/* One line expression input */
void multi_input();	/* Multi line expression input */


int main(void) {
	/* tests(); */
	/* input(); */
	multi_input();
	return 0;
}


/* *********** */
/* Multi input */
/* *********** */

void multi_input() {
	
	char *array[N];
	int i = 0;
	printf("To finish entering expressions just type - 'end'\n\n");

	while(1) {
		char *expression = (char *)malloc(sizeof(char)*N);
		if(i)
			while(getchar() != '\n');
		printf("Enter %d expression: ", i+1);
		scanf("%255[^\n]", expression);
		if(strcmp(expression, "end")) {
			array[i] = expression;
			i++;
		} else 
			break;
	}

	if(i) {
		printf("\nAnswers:\n");
		for(int j = 0; j < i; j++) {
			printf("Answer to %d expression: %s\n", j+1, evaluate(array[j]));
			free(array[j]);
		}
	} else {
		printf("\nerror: no expressions were given\n");
	}
}


/* ************ */
/* Unit testing */
/* ************ */

void tests() {
	if(!strcmp(evaluate("I+X"), "XI"))
		printf("Test 1 - PASSED!\n");
	else 
		printf("Test 1 - FAILED!\nResult: %s\n", evaluate("I+X"));
	
	if(!strcmp(evaluate("I+X*(X+X-X+V)/V"), "XXXI"))
		printf("Test 2 - PASSED!\n");
	else 
		printf("Test 2 - FAILED!\nResult: %s\n", evaluate("I+X*(X+X-X+V)/V"));
	
	if(!strcmp(evaluate("I-X*(XX+V)/V"), "-XLIX"))
		printf("Test 3 - PASSED!\n");
	else 
		printf("Test 3 - FAILED!\nResult: %s\n", evaluate("I-X*(XX+V)/V"));
	
	if(!strcmp(evaluate("I*-II"), "-II"))
		printf("Test 4 - PASSED!\n");
	else 
		printf("Test 4 - FAILED!\nResult: %s\n", evaluate("I*-II"));
	
	if(!strcmp(evaluate("I---II"), "-I"))
		printf("Test 5 - PASSED!\n");
	else 
		printf("Test 5 - FAILED!\nResult: %s\n", evaluate("I---II"));
}


/* ***** */
/* Input */
/* ***** */

void input() {
	char *expression = (char *)malloc(sizeof(char)*N);
	printf("Enter expression: ");
	scanf("%255[^\n]", expression);
	printf("\nAnswer: %s\n", evaluate(expression));
	free(expression);
}
