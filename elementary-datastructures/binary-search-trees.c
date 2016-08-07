/*
	author: Satyajith
	
	data-structure: binary search trees

	operations: insert, search, delete, find-min, find-max
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	int data;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
} tree;

tree *search_node(tree *, int);				// search the b-tree
tree *insert_node(tree **, int, tree*);		// insert a node
void delete_node(tree *, int);					// delete a node
tree *find_min(tree *);						// find min element
tree *find_max(tree *);						// find max element

void print_menu();							// print the options menu

int main(int argc, char const *argv[])
{
	tree *t = NULL;
	tree *aux = NULL;

	char choice = '\0';
	int x = 0;

	while (choice != 'q' && choice != 'Q') {

		print_menu();
		scanf(" %c", &choice);		// input choice

		switch(choice) {
			case '1':
				printf("\n%s: ", "enter the integer data");
				scanf(" %d", &x);
				printf("%s: ", "traversal");		// printing traversal; l and r
				aux = insert_node(&t, x, NULL);		// &t, because insert parameter is **t

				if (aux != NULL)
					printf("\n%s: 0x%x\n", "tree node inserted @ address", aux);
				else
					puts("node insertion failed!");
				break;

			case '2':
				printf("\n%s: ", "enter data to search");
				scanf(" %d", &x);
				printf("%s: ", "traversal");		// printing traversal; l and r
				aux = search_node(t, x);
				
				if (aux != NULL)
					printf("\n%s: 0x%x\n", "tree node found @ address", aux);
				else
					puts("data not found in tree!");
				break;

			case '3':
				aux = find_min(t);

				if (aux != NULL) {
					printf("\n%s : 0x%x", "min element found @ address", aux);
					printf("\n%s: %d\n", "with value", aux->data);
				} else {
					puts("tree is empty!");
				}
				break;

			case 4:
				aux = find_max(t);

				if (aux != NULL) {
					printf("\n%s : 0x%x", "max element found @ address", aux);
					printf("\n%s: %d\n", "with value", aux->data);
				} else {
					puts("tree is empty!");
				}
				break;

			case '5':
				printf("\n%s: ", "enter data to delete");
				scanf(" %d", &x);

				delete_node(t, x);
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
	puts("1 - insert");
	puts("2 - search");
	puts("3 - find min");
	puts("4 - find max");
	puts("5 - delete");
	puts("q - quit");
	printf("\n%s: ", "enter choice");
}

// here **t is needed for the step '*t = n'
// where the object at that location must take n
tree *insert_node(tree **t, int x, tree *p) {

	if (*t == NULL) {
		tree *n = malloc(sizeof(tree));

		n->data = x;
		n->left = n->right = NULL;
		n->parent = p;

		*t = n;
		return n;
	}

	/*	a) **t stores the address of the pointer refering to the address of the
		tree node. so *t is the pointer to a node, and (*t)->data is the data
		variable in that node.

		b) we need to pass a pointer to a pointer of a node.
		(*t)->left is the pointer to the left node, and &((*t)->left) is the address
		of that pointer
		-- similarly the &((*t)->right)
	*/

	if (x < (*t)->data) {
		printf("%c ", 'l');
		return insert_node(&((*t)->left), x, *t);
	} else {
		printf("%c ", 'r');
		return insert_node(&((*t)->right), x, *t);
	}
}

// routine to recursively search for data
tree *search_node(tree *t, int x) {
	
	if (t == NULL)
		return NULL;

	if (t->data == x)
		return t;

	if (x < t->data) {
		printf("%c ", 'l');
		return search_node(t->left, x);
	}
	else {
		printf("%c ", 'r');
		return search_node(t->right, x);
	}
}

// find min element
tree *find_min(tree *t) {

	if (t == NULL)
		return NULL;

	tree *min = t;
	while (min->left != NULL)
		min = min->left;

	return min;	
}

// find max element
tree *find_max(tree *t) {

	if (t == NULL)
		return NULL;

	tree *max = t;
	while (max->right != NULL)
		max = max->right;

	return max;	
}

// delete a node
void delete_node(tree *t, int x) {

	printf("\n%s: ", "traversal");			// printing traversal; l and r
	tree *aux = search_node(t, x);

	if (aux == NULL) {
		puts("node does not exist!");
		return;
	} else {
		//	if node exists
		//	case 1: node is a leaf
		if (aux->left == NULL && aux->right == NULL) {
			if (aux == aux->parent->left)
				aux->parent->left = NULL;
			else
				aux->parent->right = NULL;
		}

		//	case 2: node has 2 children
		else if (aux->left != NULL && aux->right != NULL) {
			//	replace the data with the right sub-tree's min element
			//	and delete the min element node

			tree *r_min = find_min(aux->right);		// the pointer to min element
			aux->data = r_min->data;

			if (r_min->parent->left == r_min)		// make sure the parent has no
				r_min->parent->left = NULL;			// information of the child to
			else									// be removed
				r_min->parent->right = NULL;

			aux = r_min;			// point aux to the node to be removed
		}

		//	case 3: node has 1 child
		else {
			// if it has a right child
			if (aux->left == NULL) {
				if (aux == aux->parent->left)
					aux->parent->left = aux->right;
				else
					aux->parent->right = aux->right;
			}
			// if it has a left child
			else {
				if (aux == aux->parent->left)
					aux->parent->left = aux->left;
				else
					aux->parent->right = aux->left;
			}
		}

		free(aux);		// free memory
		puts("\nnode deleted!");
	}
}