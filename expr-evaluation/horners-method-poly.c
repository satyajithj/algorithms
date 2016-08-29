/*
	author: Satyajith
	description: Horner's method for evaluation of a polynomial

	time-complexity:	theta(n) -- linear
*/

#include <stdio.h>

double horners_method(double[], int, double);

int main(int argc, char const *argv[]) {

	int n = 7;
	double coeff[] = {1.2, 3.6, 4.8, 2.7, 8.8, 7.65, 3.15};		// a6, a5, ..., a0
	double x = 5;

	double value = horners_method(coeff, n-1, x);
	printf("the value of the evaluated polynomial for x = %lf is %lf\n", x, value);
	return 0;
}

// recursive evaluation
double horners_method(double coeff[], int n, double x) {
	if (n == 0)	return coeff[0];
	return coeff[n] + x * horners_method(coeff, n-1, x);
}
