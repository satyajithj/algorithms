/**
 *	author: satyajith
 *	program: doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG(str) printf("DEBUG: %s\n", str)

// Node structure
typedef struct Node Node;
struct Node {
	int data;
	Node* prev;
	Node* next;
};

// linked list structure
typedef struct {
	Node* head;
} LinkedList;

// function declaration
LinkedList* init_list();				// initialize linked list
Node* list_search(LinkedList*, int);	// search the list for given integer
void list_insert(LinkedList*, int);		// insert new node to list
void list_delete(LinkedList*, int);		// delete element from list if it exists

int main(int argc, char const* argv[]) {
	// sample linked list program
	LinkedList* llist = init_list();

	int arr[5] = {3, 1, 4, 7, 6};

	// insert array elements into linked list
	for (int i = 0; i < 5; ++i)
		list_insert(llist, arr[i]);

	// do something ...

	for (int i = 0; i < 5; ++i)
		list_delete(llist, arr[i]);

	free(llist);
	return 0;
}

// initialize a linked list structure and return
LinkedList* init_list() {
	LinkedList* l = (LinkedList*) malloc(sizeof(LinkedList));
	l->head = NULL;
	return l;
}

// search list for data 'k'
Node* list_search(LinkedList* l, int k) {
	Node* x = l->head;
	while (x != NULL && x->data != k)	// loop terminates when data matches
		x = x->next;
	return x;
}

// insert node 'x' in list 'l'
void list_insert(LinkedList* l, int k) {
	// allocate a new node
	Node* x = (Node*) malloc(sizeof(Node));
	x->data = k;
	x->prev = x->next = NULL;

	// add to front of list
	x->next = l->head;

	if (l->head != NULL)
		l->head->prev = x;

	l->head = x;	   // point head to 'x'
	x->prev = NULL;	// since it is the head
}

// delete from list if element exists
void list_delete(LinkedList* l, int k) {
	// this function can be simplified if a
	// sentinel (dummy node) is used to close the list
	Node* x = list_search(l, k);
	// if it is not the head node
	if (x->prev != NULL)
		x->prev->next = x->next;
	// if it is the head node
	else
		l->head = x->next;
	// if 'x' is not head and x->next is not NULL
	// then x->next->prev need to set to x->prev
	// which can also be NULL if it was the head
	if (x->next != NULL)
		x->next->prev = x->prev;

	free(x);
}