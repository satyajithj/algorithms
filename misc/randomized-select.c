/**
 *	author: Satyajith
 *
 * 	program: randomized select - ith order statistic
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	N	7

int randomized_select(int*, int, int, int);		// the select method
void swap(int *, int *);						// method to swap elements in an array
int partition(int*, int, int);					// identify the pivot index
int randomized_partition(int*, int, int);		// randomly sampled element as pivot

int main(int argc, char const *argv[])
{
	int arr[N] = {3, 4, 1, 7, 5, 8, 6};
	int i = 4;	// ith smallest element
	
	int x = randomized_select(arr, 0, N-1, i);

	printf("element #%d: %d\n", i, x);
	return 0;
}

int randomized_select(int* arr, int s, int e, int i) {

	if (s == e)
		return arr[s];

	int p = randomized_partition(arr, s, e);
	int k = p-s+1;										// +1 because, indexing starts at 0 while i starts at 1

	if (k == i)
		return	arr[p];
	else if (i < k)
		return	randomized_select(arr, s, p-1, i);		// if it lies to the left, the required index is still i
	else
		return	randomized_select(arr, p+1, e, i-k);	// if it lies to the right, the required index is (i - k) 
}

/**
 * picking a randomized pivot element
 *
 * @param   arr  the array
 * @param   s    start index
 * @param   e    end index
 *
 * @return       run partition and get pivot index
 */
int randomized_partition(int* arr, int s, int e) {
	
	srand(time(NULL));
	int r = (rand() % (e-s+1)) + s;		// (e-s+1) because, e and s are start and end indices and diff is not num elements
	swap(&arr[r], &arr[e]);

	return partition(arr, s, e);
}

/**
 * swap at specified locations
 *
 * @param  a  first value
 * @param  b  second value
 */
void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

/**
 * the partition method
 *
 * @param   arr  the array
 * @param   s    start index for partition
 * @param   e    end index for partition
 *
 * @return       return index of pivot {integer}
 */
int partition(int* arr, int s, int e) {

	int pivot = e;							// pivot element initialized as the last element of the sub-array
	int first_highest = s;						// final index to the first element grater than pivot element

	for (int i = s; i < e; i++)
		if (arr[i] < arr[pivot]) {
			swap(&arr[i], &arr[first_highest]);	// elements greater than the pivot are clubbed towards the right
			first_highest++;
		}

	swap(&arr[first_highest], &arr[pivot]);		// place the pivot in it's righful position
	return first_highest;						// return the pivot's final index
}