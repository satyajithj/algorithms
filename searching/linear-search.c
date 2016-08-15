/*
	author: Satyajith
	algorithm: linear search (good for unsorted data)

	time complexity:
		worst case - O(n)
*/

#include <stdio.h>

int linear_search(int[], int, int);
void print_array(int[], int, int);

int main(int argc, char const *argv[]) {

	const int n = 12;
	int arr[] = {21, 3, 8, 2, 13, 1, 9, 4, 7, 6, 5, 11};

	int x = 13;

	printf("%s: ", "array");
	print_array(arr, 0, n);

	int find = linear_search(arr, x, n);

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
int linear_search(int arr[], int x, int n) {
	for (size_t i = 0; i < n; i++)
		if (arr[i] == x)
			return i;

	return -1;
}
