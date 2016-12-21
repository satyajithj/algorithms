/**
 *	author: Satyajith
 * 	algorithm: merge sort
 * 	time complexity: theta(n lg(n))	
 */

#include <stdio.h>

void merge_sort(int[], int, int);					//	merge sort routine
void merge(int[], int, int);						//	merge routine
void swap(int *, int *);							// swap elements

int main(int argc, char const *argv[]) {

	int n = 13;
	int arr[] = {21, 3, 8, 2, 13, 1, 9, 4, 67, 7, 6, 5, 11};

	merge_sort(arr, 0, n-1);						// call to merge sort
	return 0;
}

// the merge routine
void merge(int arr[], int s, int e) {

	const size_t size = (e-s) + 1;

	const size_t buf_size_2 = size/2;				// the order of these two statements matter, because
	const size_t buf_size_1 = size - buf_size_2;	// in merge-sort() the split is ceil(size/2) followed by
													// floor(size/2) and not the other way around ...
	int buffer_1[buf_size_1];
	int buffer_2[buf_size_2];

	for (size_t i = 0; i < buf_size_1; i++)			// copy first half to buffer_1
		buffer_1[i] = arr[s + i];
	for (size_t i = 0; i < buf_size_2; i++)			// copy second half to buffer_2
		buffer_2[i] = arr[s + buf_size_1 + i];

	size_t i = 0, j = 0, k = s;						// merge until one buffer is traversed
	while( i != buf_size_1 && j != buf_size_2) {
		if (buffer_1[i] < buffer_2[j])
			arr[k++] = buffer_1[i++];
		else
			arr[k++] = buffer_2[j++];
	}

	if (j == buf_size_2)							// add all elements until buffer_1 empties
		while (i != buf_size_1)
			arr[k++] = buffer_1[i++];

	if (i == buf_size_1)							// add all elements until buffer_2 empties
		while (j != buf_size_2)
			arr[k++] = buffer_2[j++];
}

// merge sort routine
void merge_sort(int arr[], int s, int e) {

	size_t size = (e-s);

	// base case
	if (size <= 1) {
		if (arr[e] < arr[s])
			swap(&arr[e], &arr[s]);
		return;
	}

	// recurive procedure
	merge_sort(arr, s, (s+e)/2);
	merge_sort(arr, (s+e)/2 + 1, e);
	merge(arr, s, e);
}

// swap integers pointed at a and b
void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}
