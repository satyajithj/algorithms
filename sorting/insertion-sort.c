/*
	author: Satyajith
	algorithm: insertion sort

	time complexity: O(n^2)
*/

#include <stdio.h>

#define NEWLINE printf("\n");

void insertion_sort(int[], int);
void print_array(int[], int);

int main(int argc, char const *argv[])
{
	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	printf("%s: ", "original array");
	print_array(arr, 12);

	insertion_sort(arr, 12);

	printf("\n%s: ", "sorted array");
	print_array(arr, 12);

	NEWLINE;
	return 0;
}

void print_array(int arr[], int n) {
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

void insertion_sort(int arr[], int n) {
	int key, j;

	for (int i = 1; i < n; ++i)
	{
		key = arr[i];
		for (j = i-1; j >= 0; --j)
		{
			if (arr[j] > key)
				arr[j+1] = arr[j];
			else
				break;
		}
		arr[j+1] = key;
	}
}
