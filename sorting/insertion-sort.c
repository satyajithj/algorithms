/**
 * 	author: Satyajith
 * 	algorithm: insertion sort
 * 	time complexity: O(n^2)
 */

#include <stdio.h>

void insertion_sort(int[], int);

int main(int argc, char const *argv[])
{
	int n = 12;
	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	insertion_sort(arr, n);
	return 0;
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
