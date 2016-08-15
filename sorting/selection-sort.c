/*
	author: Satyajith
	algorithm: selection sort

	time complexity: O(n^2)
*/

#include <stdio.h>

void selection_sort(int[], int);
void print_array(int[], int);
void swap(int&, int&);

int main(int argc, char const *argv[])
{
	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	printf("%s: ", "original array");
	print_array(arr, 12);

	selection_sort(arr, 12);

	printf("\n%s: ", "sorted array");
	print_array(arr, 12);

	return 0;
}

void print_array(int arr[], int n) {
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void selection_sort(int arr[], int n) {
	int min_index;

	for (int i = 0; i < n; ++i)
	{	min_index = i;

		for (int j = i+1; j < n; ++j)
			if (arr[j] < arr[min_index])
				min_index = j;

		swap(arr[min_index], arr[i]);	// swap the minimum and arr[i]
	}
}
