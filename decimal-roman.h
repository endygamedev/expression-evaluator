#ifndef N
#define N 256
#endif



#ifndef _STDLIB_H
#include <stdlib.h>
#endif


#ifndef _STRING_H
#include <string.h>
#endif


/* ******************** */
/* Working with numbers */
/* ******************** */

/* Gets decimal value from roman number */
int get_value(char roman_char) {
	switch(roman_char) {
		case 'I': return 1; break;
		case 'V': return 5; break;
		case 'X': return 10; break;
		case 'L': return 50; break;
		case 'C': return 100; break;
		case 'D': return 500; break;
		case 'M': return 1000; break;
		case 'Z': return 0; break;
		default: printf("error: bad input value %c\n", roman_char); exit(1);
	}
}


/* Convert roman number to decimal form */
int roman_to_decimal(char *roman_num) {

	int decimal_num = 0, i = 0;
	int len = strlen(roman_num);
	int num1, num2;

	while(i < len) {
		num1 = get_value(roman_num[i]);
		if(i + 1 < len) {
			num2 = get_value(roman_num[i+1]);
			if(num1 >= num2) {
				decimal_num += num1;
				i++;
			} else {
				decimal_num += num2 - num1;
				i += 2;
			}
		} else {
			decimal_num += num1;
			i++;
		}
	}
	return decimal_num;
}


/* Convert decimal number to roman form */
char *decimal_to_roman(int num) {

	if(num == 0)
		return "Z";

	int n = abs(num), i = 0;
	char *s = (char *)malloc(sizeof(char) * N);
	int decimal[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

	while(n) {
		while(n/decimal[i]) {
			strcat(s, roman[i]);
			n -= decimal[i];
		}
		i++;
	}

	if(num < 0) {
		char *m = (char *)malloc(sizeof(char)*N);
		strcat(m, "-");
		strcat(m, s);
		return m;
	} else {
		return s;
	}
}
