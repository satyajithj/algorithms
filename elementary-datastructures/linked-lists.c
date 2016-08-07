/*
	author: Satyajith
	
	data-structure: singly linked-lists

	operations: search, insert, delete
*/

#include <stdio.h>
#include <stdlib.h>

// structure definition
typedef struct list {
	int data;
	struct list* next;
} list;

// routines used on linked list
list* search_list(list*, int);	// routine to search
list* insert_node(list**);		// routine to insert a new node
list* pred_node(list*, int);	// to find the predecessor node
void delete_node(list*);		// routine to delete a node

void print_menu();

int main(int argc, char const *argv[])
{
	list* l = NULL;
	list* t = NULL;

	int l_size = 0;
	int x;

	char choice = '\0';

	while (choice != 'q' && choice != 'Q') {

		print_menu();
		scanf(" %c", &choice);		// input choice

		switch(choice) {
			case '1':
				printf("%s: ", "enter item to search");
				scanf(" %d", &x);
				t = search_list(l, x);

				if (t == NULL)
					printf("\n%s", "DATA NOT FOUND");
				else
					printf("\n%s @ ADDRESS 0x%X", "DATA FOUND", t);
				break;
			case '2':
				t = insert_node(&l);
				if (t != NULL) {
					l_size++;
					printf("%s\n%s: %d\n", "item added to list", "LIST SIZE", l_size);
				}
				break;
			case '3':
				delete_node(l);
				l_size--;
				printf("%s\n%s: %d\n", "item deleted", "LIST SIZE", l_size);
				break;
			default:
				break;
		}
	}

	puts("closing program...");
	return 0;
}

void print_menu() {
	puts("\nOPTIONS ---");
	puts("1 - search");
	puts("2 - insert");
	puts("3 - delete");
	puts("q - quit");
	printf("\n%s: ", "enter choice");
}

// we use **l here because we make a change to it in place
// rather *l can used only when using the pointer as it is

list* insert_node(list** l) {

	int data;
	printf("%s: ", "enter integer data");
	scanf(" %d", &data);

	list* p = malloc(sizeof(list));
	p->data = data;

	if (*l == NULL) {
		p->next = NULL;
		*l = p;
	} else {
		p->next = *l;
		*l = p;
	}

	return p;
}

list* search_list(list* l, int d) {
	// recursive search

	if (l == NULL)
		return NULL;
	else if (l->data == d)
		return l;
	else
		return search_list(l->next, d);
}

list* pred_node(list* l,int data) {

	// check for empty list
	if (l == NULL || l->next == NULL) {
		printf("\n%s", "predecessor sought on empty list!");
		return NULL;
	}

	// check current node
	if ((l->next)->data == data)
		return l;

	// recurse
	else
		return(pred_node(l->next, data));
}

void delete_node(list* l) {

	int x;
	printf("\n%s: ", "enter item to delete: ");
	scanf(" %d", &x);

	list* p;
	list* pred;

	p = search_list(l, x);
	if (p != NULL) {
		pred = pred_node(l, x);

		if (pred == NULL)
			l = p->next;
		else
			pred->next = p->next;

		free(p);	// free the memory
	}
}