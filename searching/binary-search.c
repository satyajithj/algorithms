/*
	author: Satyajith
	algorithm: binary search (good for sorted data)

	time complexity:
		worst case - O(lg n)
*/

#include <stdio.h>

int binary_search(int[], int, int, int);
void print_array(int[], int, int);

int main(int argc, char const *argv[]) {

	const int n = 12;
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 21};	// data must be sorted

	int key = 13;

	printf("%s: ", "array");
	print_array(arr, 0, n);

	int find = binary_search(arr, key, 0, n-1);

	if (find == -1)
		printf("\n%s", "data not found!");
	else
		printf("\n%s %d", "data found at index", find+1);	// array indices in C start at 0

	return 0;
}

// print array from given start to end indices
void print_array(int arr[], int s, int e) {
	for (int i = s; i < e; ++i)
		printf("%d ", arr[i]);
}

// if found return index, else return -1
int binary_search(int arr[], int key, int s, int e) {

	if (s > e)					// no data found
		return -1;

	int middle = (s+e)/2;		// compute middle index

	if (arr[middle] == key)		// check if middle element is the key
		return middle;

	if (arr[middle] > key)
		return binary_search(arr, key, s, middle-1);		// recurse on the left half
	else
		return binary_search(arr, key, middle+1, e);		// recurse on the right half
}
