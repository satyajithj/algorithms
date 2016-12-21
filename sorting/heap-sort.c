/**
 * 	author: Satyajith
 * 	algorithm: heap sort algorithm on max heaps
 * 	time complexity: O(n (lg n))
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 32
#define DEBUG(str) printf("%s %s\n", "DEBUG:", str);

#define left(i) (i << 1)
#define right(i) ((i << 1) + 1)

// heap data structure
typedef struct {
  int* array;
  int heap_size;
} heap;

// method declarations
void swap(int*, int*);             // to swap integers
void max_heapify(heap*, int);      // to maintain the max-heap property
void build_heap(heap*);            // to build the heap from an array
void heap_sort(int*, int);         // run the heap sort algorithm
void print_array(int*, int, int);  // print array

// program start
int main(int argc, char const* argv[]) {
  int arr[MAX_SIZE] = {0, 2, 5, 1, 6,
                       4, 3, 9, 7, 8};  // first element is unused
  int size = 9;

  heap_sort(arr, size);  // call to heap sort
  print_array(arr, 1, 9);
  return 0;
}

// print array X, from index s to e
void print_array(int* X, int s, int e) {
  printf("\n");
  for (int i = 1; i <= e; ++i) printf("%d ", X[i]);
}

// swap integer locations
void swap(int* x, int* y) {
  int t = *x;
  *x = *y;
  *y = t;
}

// maintain max-heap property
void max_heapify(heap* A, int i) {
  int l = left(i);
  int r = right(i);
  int largest = i;

  if ((l <= A->heap_size) && (A->array[l] > A->array[i])) largest = l;
  if ((r <= A->heap_size) && (A->array[r] > A->array[largest])) largest = r;

  if (largest != i) {
    swap(&A->array[i], &A->array[largest]);  // swap the elements
    max_heapify(A, largest);                 // recursively process
  }
}

// build max-heap from given array
void build_heap(heap* A) {
  for (int i = A->heap_size / 2; i > 0; --i) {
    max_heapify(A, i);  // run max_heapify bottom-up, on all non-leaf nodes
  }
}

// the heap-sort routine
void heap_sort(int* arr, int size) {
  heap* max_heap = malloc(sizeof(heap));  // dynamically allocate heap structure
  max_heap->array = arr;
  max_heap->heap_size = size;

  build_heap(max_heap);  // construct the max-heap

  for (int i = max_heap->heap_size; i >= 2; --i) {
    swap(&max_heap->array[1], &max_heap->array[i]);
    (max_heap->heap_size)--;   // since an element is removed, size of heap
                               // reduces by 1
    max_heapify(max_heap, 1);  // since A[1] is not the largest element now
  }

  max_heap->array = NULL;
  free(max_heap);  // de-allocate memory
}