/*
	author: Satyajith
	algorithm: bubble sort

	complexity: O(n^2)
*/

#include <stdio.h>

#define NEWLINE printf("\n");

void bubble_sort(int[], int);
void print_array(int[], int);
void swap(int&, int&);

int main(int argc, char const *argv[])
{
	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	printf("%s: ", "original array");
	print_array(arr, 12);

	bubble_sort(arr, 12);

	printf("\n%s: ", "sorted array");
	print_array(arr, 12);

	NEWLINE;
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

void bubble_sort(int arr[], int n) {

	for (int i = 0; i < n-1; ++i)		
		for (int j = 0; j < (n-i-1); ++j)
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);
}