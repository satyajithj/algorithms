// in-built sort function in C
// qsort() in the stdlib header

#include <stdio.h>
#include <stdlib.h>

int cmp_func(const void *, const void *);   // the ccompare method for the internal sort routine

int main(int argc, char const *argv[]) {

  int n = 12;
  int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};
  qsort(arr, n, sizeof(int), cmp_func);					// call to qsort
  return 0;
}

// 'a' is before 'b' if function returns a negative value
int cmp_func(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}
