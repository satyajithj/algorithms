/*
	author: Satyajith
	algorithm: heap sort on a max-heap

	time complexity: O(n lg(n))
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

typedef struct {
  int Q[SIZE +1];      // the +1 is added to make it convenient computing with powers of 2
  int n;              // length of the queue
} priority_queue;

void print_array(int[], int, int);					// print the values of a 1-D array

int parent_index(int);								// compute parent index of current index
int start_child_index(int);							// compute the first child index
void pq_init(priority_queue *);						// initi the priority queue
void pq_insert(priority_queue *, int);				// insert element into the heap
void bubble_up(priority_queue *, int);				// bubble-up the new element if it is greater than the parent
void bubble_down(priority_queue *, int);			// bubble-down the root element if it is lesser than the child
void pq_swap(priority_queue *, int, int);			// swap two elements in an array
void make_heap(priority_queue *, int[], int);		// make the heap from a given array
int extract_max(priority_queue *);					// extract the max element from the max-heap (the root element) and reprocess the heap
void heap_sort(int[], int);							// the heap sort method

void print_menu();									// print the menu for allowed operations

int main(int argc, char const *argv[]) {

  int x, n = 12;
  int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};
  char choice = '\0';

  priority_queue *q = malloc(sizeof(priority_queue));

  printf("%s: ", "initial array");
  print_array(arr, 0, n);

  make_heap(q, arr, n);				// make a max-heap

  printf("\n%s: ", "initialized max-heap");
  print_array(q->Q, 1, q->n+1);

  // loop
  while (choice != 'q' && choice != 'Q') {

	  print_menu();
	  scanf(" %c", &choice);		// input choice

	  switch (choice) {
	  	case '1':
			printf("%s: ", "enter the integer");
			scanf(" %d", &x);
			pq_insert(q, x);
			printf("%s: ", "max-heap");
			print_array(q->Q, 1, q->n+1);
			break;

		case '2':
			x = extract_max(q);
			if (x != -1) {
				printf("\n%s: %d", "max element is", x);
				printf("\n%s: ", "max-heap");
				print_array(q->Q, 1, q->n+1);
			}
			else
				printf("\n%s", "WARNING! empty priority queue");
			break;

		case '3':
			heap_sort(arr, n);
			printf("\n%s: ", "sorted array (heap-sort)");
		    print_array(arr, 0, n);
			break;

		default:
			break;
	  }
  }

  free(q);									// manual de-allocation

  puts("closing program...");
  return 0;
}

// print a menu of operations
void print_menu() {
	puts("\n\nOPTIONS ---");
	puts("1 - insert");
	puts("2 - extract-max");
	puts("3 - heap-sort");
	puts("q - quit");
	printf("\n%s: ", "enter choice");
}

// method to print an entire array
void print_array(int arr[], int s, int e) {
  for (size_t i = s; i < e; i++)
    printf("%d ", arr[i]);
}

// heap sort
void heap_sort(int arr[], int n) {

	priority_queue q;
	make_heap(&q, arr, n);

	for (size_t i = 0; i < n; i++)
		arr[i] = extract_max(&q);
}

// bubble down to rearrange the heap
void bubble_down(priority_queue *q, int x) {

	int child_index = start_child_index(x);
	int max_index = x;

	for (size_t i = 0; i <= 1; i++) {
		if ((child_index + i) <= q->n)						// a check on the queue size
			if (q->Q[max_index] < q->Q[child_index+i])		// in a max-heap if the node is less than the child
				max_index = child_index +i;							// change index to max value
	}

	if (max_index != x) {
		pq_swap(q, x, max_index);							// if max is at a different index, then swap
		bubble_down(q, max_index);							// bubble_down on the swapped index location
	}
}

// extract the max element
int extract_max(priority_queue *q) {
	int max = -1;		// max value

	if (q->n == 0)
		return -1;

	else {
		max = q->Q[1];
		q->Q[1] = q->Q[q->n];
		q->n--;
		bubble_down(q, 1);
		return max;
	}
}

// method to make the max-heap from a given array
// -- O(n) procedure
void make_heap(priority_queue *q, int arr[], int n) {
	q->n = n;
	q->Q[0] = -1;

	for (size_t i = 1; i <= n; i++)
		q->Q[i] = arr[i-1];

	for (size_t i = q->n; i > 0; i--)
		bubble_down(q, i);
}

/* O(n (lg n)) procedure
void make_heap(priority_queue *q, int arr[], int n) {
  pq_init(q);
  for (size_t i = 0; i < n; i++)
    pq_insert(q, arr[i]);
}*/

// initialize the priority queue
void pq_init(priority_queue *q) {
  q->n = 0;
  q->Q[q->n] = -1;
}

// swap the positions of the elements at indices a and b
void pq_swap(priority_queue *q, int a, int b) {
  int temp;
  temp = q->Q[a];
  q->Q[a] = q->Q[b];
  q->Q[b] = temp;
}

// used for positioning the newly inserted data entry in the heap
// a max heap must have the largest element at the root
void bubble_up(priority_queue *q, int x) {
  if (parent_index(x) == -1)  return;

  if (q->Q[parent_index(x)] < q->Q[x]) {
    pq_swap(q, x, parent_index(x));
    bubble_up(q, parent_index(x));
  }
}

// insert a data entry into the max heap
void pq_insert(priority_queue *q, int x) {
  if (q->n >= SIZE + 1)
    printf("%s %d\n", "priority queue overflow! cannot insert", x);

  else {
    q->n++;
    q->Q[q->n] = x;
    bubble_up(q, q->n);
  }
}

int parent_index(int n) {
  if (n == 1) return (-1);
  else  return (n/2);
}

int start_child_index(int n) {
  return (2*n);
}
