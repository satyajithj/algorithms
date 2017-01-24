/**
 * 	author:	satyajith
 * 	algorithm: inversion counting
 * 	time complexity: theta(n lg(n))
 */

#include <stdio.h>

int count_inv(int[], int, int);	//	merge sort routine
int merge(int[], int, int);		   //	merge routine
void swap(int *, int *);		   // swap elements

int main(int argc, char const *argv[]) {
	int n = 10;
	int arr[] = {5, 2, 10, 8, 1, 9, 4, 3, 6, 7};
	int inv_counts = count_inv(arr, 0, n - 1);

	printf("number of inversions is: %d", inv_counts);
	return 0;
}

int merge(int arr[], int s, int e) {
	const int size = (e - s) + 1;

	const int buf_size_2 =
		size / 2;	// the order of these two statements matter, because
	const int buf_size_1 =
		size - buf_size_2;	// in merge-sort() the split is ceil(size/2) followed by

	// floor(size/2) and not the other way around ...
	int buffer_1[ buf_size_1 ];
	int buffer_2[ buf_size_2 ];

	for (int i = 0; i < buf_size_1; i++)	// copy first half to buffer_1
		buffer_1[ i ] = arr[ s + i ];
	for (int i = 0; i < buf_size_2; i++)	// copy second half to buffer_2
		buffer_2[ i ] = arr[ s + buf_size_1 + i ];

	int i = 0, j = 0, k = s;	// merge until one buffer is traversed
	int inv_count = 0;
	while (i != buf_size_1 && j != buf_size_2) {
		if (buffer_1[ i ] < buffer_2[ j ]) {
			arr[ k++ ] = buffer_1[ i++ ];
			inv_count += j;
		} else
			arr[ k++ ] = buffer_2[ j++ ];
	}

	if (j == buf_size_2)	// add all elements until buffer_1 empties
		while (i != buf_size_1) {
			arr[ k++ ] = buffer_1[ i++ ];
			inv_count += buf_size_2;
		}

	if (i == buf_size_1)	// add all elements until buffer_2 empties
		while (j != buf_size_2)
			arr[ k++ ] = buffer_2[ j++ ];

	return inv_count;
}

int count_inv(int arr[], int s, int e) {
	int size = (e - s);

	// base case
	if (size <= 1) {
		if (arr[ e ] < arr[ s ]) {
			swap(&arr[ e ], &arr[ s ]);
			return 1;	// an inversion if 1st element greater than the second at base
						 // case
		}
		return 0;
	}

	// recurive procedure
	int c1 = count_inv(arr, s, (s + e) / 2);
	int c2 = count_inv(arr, (s + e) / 2 + 1, e);
	int c3 = merge(arr, s, e);

	return (c1 + c2 + c3);
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}
