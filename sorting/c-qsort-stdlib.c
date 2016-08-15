#include <stdio.h>
#include <stdlib.h>

void print_array(int[], int);               // print the array elements
int cmp_func(const void *, const void *);   // the ccompare method for the internal sort routine

int main(int argc, char const *argv[]) {

  int n = 12;
  int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

  printf("%s: ", "original array");
	print_array(arr, 12);

  qsort(arr, 12, sizeof(int), cmp_func);    // in the stdlib header

  printf("\n%s: ", "sorted array");
	print_array(arr, 12);

  return 0;
}

void print_array(int arr[], int n) {
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

int cmp_func(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}
