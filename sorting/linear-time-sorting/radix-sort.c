/**
 * 	@author Satyajith
 * 	
 * 	Radix Sort
 */

#include <stdio.h>
#include <math.h>

#define	N	7		// total numbers
#define	K	9		// digit range
#define	D	3		// digits

#define	DEBUG(str, i)	printf("DEBUG: %s - %d\n", str, i)

void radix_sort(int*, int*);					// radix sort method
void count_sort_digit(int*, int*, int);			// count sort method
void print_array(int*, int, int);				// print the array

int main(int argc, char const *argv[])
{
	int A[N] = {329, 457, 657, 839, 436, 720, 355};
	int B[N];

	radix_sort(A, B);
	print_array(B, 0, N);

	return 0;
}

/**
 * print the given array 
 *
 * @param  A  the integer array
 * @param  s  start index
 * @param  e  end index
 */
void print_array(int* X, int s, int e) {

	printf("\n");
	for (int i = s; i < e; ++i)
		printf("%d ", X[i]);
}

/**
 * radix sort method
 *
 * @param  A  original array
 * @param  B  output array
 */
void radix_sort(int *A, int* B) {

	int i;
	for (int d = 0; d < D; ++d) {
		// DEBUG("RM", d);
		count_sort_digit(A, B, d);
		
		for (i = 0; i < N; ++i)
			A[i] = B[i];					// to prevent the change of order
	}
}

/**
 * count sort on a digit algorithm
 *
 * @param  A  the integer array
 */
void count_sort_digit(int* A, int* B, int d) {

	int C[K+1], i, temp = 0;
	int PLACE = pow(10, d);

	for (i = 0; i < K+1; ++i)
		C[i] = 0;							// initialize counts to 0

	for (i = 0; i < N; ++i)
		C[ (A[i] / PLACE) % 10 ]++;			// C[j] now contains number of elements = j, in A

	for (i = 1; i < K+1; ++i)
		C[i] += C[i-1];						// C[j] now contains number of elements <= j, in A

	// DEBUG("UPDATE", 0);
	for (i = N-1; i >= 0; --i) {
		temp = (A[i] / PLACE) % 10;
		B[C[temp] - 1] = A[i];
		C[temp] -= 1;
	}
}