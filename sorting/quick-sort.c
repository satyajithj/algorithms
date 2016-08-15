/*
	author: Satyajith
	algorithm: quick sort

	time complexity:
		best case - O(n lg(n))
		worst case - O(n^2)
*/

#include <stdio.h>

void quick_sort(int[], int, int);		// the quick-sort routine
int partition(int[], int, int);			// the partition routine to identify the pivot's final index
void print_array(int[], int, int);		// method to print an array
void swap(int *, int *);				// method to swap elements in an array

int main(int argc, char const *argv[]) {

	int n = 12;
	int arr[] = {21, 3, 8, 2, 13, 1, 9, 4, 7, 6, 5, 11};

	printf("%s: ", "original array");
	print_array(arr, 0, n);

	quick_sort(arr, 0, n-1);

	printf("\n%s: ", "sorted array");
	print_array(arr, 0, n);

	return 0;
}

void print_array(int arr[], int s, int e) {
	for (size_t i = s ; i < e; i++)
		printf("%d ", arr[i]);
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void quick_sort(int arr[], int s, int e) {

	int p;
	if (e-s > 0) {
		p = partition(arr, s, e);		// partition and obtain the pivot's final index
		quick_sort(arr, s, p-1);		// quick-sort on the sub-arry to the left of the pivot
		quick_sort(arr, p+1, e);		// quick-sort on the sub-array to the right of the pivot
	}
}

int partition(int arr[], int s, int e) {

	int pivot = e;						// pivot element initialized as the last element of the sub-array
	int first_high = s;					// index to the first element grater than the pivot

	for (size_t i = s; i < e; i++)
		if (arr[i] < arr[pivot]) {
			swap(&arr[i], &arr[first_high]);	// elements greater than the pivot are clubbed towards the right
			first_high++;
		}

	swap(&arr[first_high], &arr[pivot]);		// place the pivot in it's righful position
	return first_high;							// return the pivot's final index
}
