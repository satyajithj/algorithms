/**
 *	@author	Satyajith
 *
 *	optimal routine to simultaneously determine min and max from
 *	a set of elements; uses (3*floor(n/2)) comparisons rather than
 *	the straight forward 2 comparisons every element 
 */

#include <stdio.h>

#define	N	10

int main(int argc, char const *argv[])
{
	int arr[N] = {3, 4, 1, 7, 21, 5, 9, 8, 6, 0};

	int max, min;

	// if N is even compare first 2 elements and initialize max and min
	if (N > 0 && N % 2 == 0) {
		if (arr[1] > arr[0]) {
			max = arr[1];
			min = arr[0];
		} else {
			max = arr[0];
			min = arr[1];
		}
	} else {
		max = min = arr[0];	// else, initialize first element as max and min
	}

	int i = (N % 2) ? 2 : 1;
	int end = (N - 1);

	for (i = 0; i < end; ++i)
	{
		if (arr[i] > arr[i+1]) {
			if (arr[i] > max)
				max = arr[i];
			if (arr[i+1] < min)
				min = arr[i+1];
		} else {
			if (arr[i+1] > max)
				max = arr[i+1];
			if (arr[i] < min)
				min = arr[i];
		}
	}

	printf("min: %d and max: %d\n", min, max);
	return 0;
}