/*
	author: Satyajith
	algorithm: square root - bisection method

	slow convergence
*/

#include <stdio.h>
#include <math.h>

double square_root(double);

int main(int argc, char const *argv[]) {

	double x, r;
	printf("%s: ", "enter number to compute square root");
	scanf(" %lf", &x);

	if (x < 0)
		printf("%s", "square root is not defined for negative numbers");
	else
		printf("%s %lf %s: %lf", "square root of", x, "is", square_root(x));

	return 0;
}

double square_root(double x) {

	double epsilon = 0.00001;
	double l = 0, r = x, m = x;
	double check = abs(m*m - x);

	while (check > epsilon) {
		m = (l+r)/2;
		if (m*m > x)	r = m;			// here we reduce the search interval by half
		else	l = m;					// and here too ...
		check = abs(m*m - x);
	}

	return m;
}
