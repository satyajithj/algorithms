/**
 *	author: satyajith
 *	program: randomized quick sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 12

void quick_sort(int[], int, int);			  // the quick-sort routine
int randomized_partition(int *, int, int);	// random pivot selection
int partition(int[], int, int);				  // identify the pivot index
void swap(int *, int *);					  // method to swap elements in an array
void print_array(int *, int, int);			  // print array

int main(int argc, char const *argv[]) {
	int arr[N] = {21, 3, 8, 2, 13, 1, 9, 4, 7, 6, 5, 11};
	quick_sort(arr, 0, N - 1);

	print_array(arr, 0, N - 1);
	return 0;
}

// print array X from index s to e
void print_array(int *X, int s, int e) {
	printf("\n");
	for (int i = s; i <= e; ++i)
		printf("%d ", X[i]);
}

// method to swap integers
void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// the quick sort method
void quick_sort(int arr[], int s, int e) {
	int p;
	if (e - s > 0) {
		p = randomized_partition(arr, s, e);	// partition and compute pivot's final index
		quick_sort(arr, s, p - 1);				// quick-sort on the sub-arry to the left of pivot
		quick_sort(arr, p + 1, e);				// quick-sort on the sub-array to the right of the pivot
	}
}

// random pivot selection
int randomized_partition(int *arr, int s, int e) {
	srand(time(NULL));
	int r = (rand() % (e - s + 1)) + s;	// (e-s+1) because, e and s are start and
	swap(&arr[r], &arr[e]);

	return partition(arr, s, e);
}

int partition(int arr[], int s, int e) {
	int pivot = e;		   // pivot element initialized as the last element
	int first_high = s;	// index to the first element grater than the pivot

	for (int i = s; i < e; i++)
		if (arr[i] < arr[pivot]) {
			swap(&arr[i], &arr[first_high]);	// elements greater than the pivot are
			// pushed right
			first_high++;
		}

	swap(&arr[first_high],
		 &arr[pivot]);	// place the pivot in it's righful position
	return first_high;	// return the pivot's final index
}
