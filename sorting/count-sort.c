/**
 * 	author: satyajith
 * 	algorithm: count sort
 * 	time complexity: O(n)
 *  
 *  assumption: range of the integers is known in advance
 */

#include <stdio.h>

#define N 8
#define K 5

void count_sort(int*, int*);			// count sort method
void print_array(int*, int, int);		// print the array

int main(int argc, char const *argv[])
{
	int A[N] = {2, 5, 3, 0, 2, 3, 0, 3};
	int B[N];

	count_sort(A, B);
	print_array(B, 0, 8);

	return 0;
}

// print the array X from index s to e
void print_array(int* X, int s, int e) {

	printf("\n");
	for (int i = s; i < e; ++i)
		printf("%d ", X[i]);
}

// count sort routine
void count_sort(int* A, int* B) {

	int C[K+1], i;
	for (i = 0; i < K+1; ++i)
		C[i] = 0;					// initialize counts to 0

	for (i = 0; i < N; ++i)
		C[A[i]]++;					// C[j] now contains number of elements = j, in A

	for (i = 1; i < K+1; ++i)
		C[i] += C[i-1];				// C[j] now contains number of elements <= j, in A

	for (i = N-1; i >= 0; --i) {
		B[C[A[i]] - 1] = A[i];
		C[A[i]] -= 1;
	}
}