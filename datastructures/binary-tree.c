/**
 *	author: satyajith
 *	program: binary tree routines
 */

#include <stdio.h>
#include <stdlib.h>

#define N 5

// node structure definition
typedef struct Node Node;

struct Node {
	int key;
	int data;
	Node* parent;
	Node* left;
	Node* right;
};

// Tree structure
typedef struct {
	Node* root;
} Tree;

// function declarations
void in_order_btree_walk(Node*);	  // in-order traversal
void pre_order_btree_walk(Node*);	 // pre-order traversal
void post_order_btree_walk(Node*);	// post-order traversal

Node* search_key_iterative(Node*, int);	// search for key iteratively
Node* get_tree_minimum(Node*);			   // return minimum key node
Node* get_tree_maximum(Node*);			   // return maximum key node
Node* get_successor(Node*);				   // return successor node
Node* get_predecessor(Node*);			   // return predecessor node

void insert_node(Tree*, Node*);				  // insert node in tree
void node_transplant(Tree*, Node*, Node*);	// replace first node with second
void delete_node(Tree*, int);				  // delete node with given key from tree
Node* create_node(int, int);				  // create and return a Node object

int main(int argc, char const* argv[]) {
	// sample program here
	Tree* T = malloc(sizeof(Tree));
	T->root = NULL;

	int keys[ N ] = {24, 32, 10, 17, 44};
	int data[ N ] = {10, 20, 30, 40, 50};

	for (int i = 0; i < N; ++i)
		insert_node(T, create_node(keys[ i ], data[ i ]));

	printf("\nIn-order binary tree walk\n");
	in_order_btree_walk(T->root);

	printf("\nPre-order binary tree walk\n");
	pre_order_btree_walk(T->root);

	printf("\nPost-order binary tree walk\n");
	post_order_btree_walk(T->root);

	return 0;
}


// create and return a new Node object
Node* create_node(int k, int data) {
	Node* new_node = malloc(sizeof(Node));
	new_node->parent = new_node->left = new_node->right = NULL;
	new_node->key = k;
	new_node->data = data;

	return new_node;
}


// delete node with key 'k'
void delete_node(Tree* T, int k) {
	Node* temp = search_key_iterative(T->root, k);

	// if node does not exist
	if (temp == NULL) {
		printf("node with given key '%d' does not exist!\n", k);
		return;
	} else {
		if (temp->left == NULL)
			node_transplant(T, temp, temp->right);
		else if (temp->right == NULL)
			node_transplant(T, temp, temp->left);
		else {
			// get minimum key node in right sub-tree
			Node* min = get_tree_minimum(temp->right);
			// if parent of min is not the node to be deleted
			if (min->parent != temp) {
				node_transplant(T, min, min->right);
				min->right = temp->right;
				min->right->parent = min;
			}
			// replace temp with min node
			node_transplant(T, temp, min);
			// link the left sub-tree
			min->left = temp->left;
			min->left->parent = min;
		}
		free(temp);	// free the node's memory
	}
}


// replace node X with node Y in tree T
// no modification to X is done here
void node_transplant(Tree* T, Node* X, Node* Y) {
	// if X is root
	if (X->parent == NULL)
		T->root = Y;
	// if X is left child of X->parent
	else if (X == X->parent->left)
		X->parent->left = Y;
	// if X is right child
	else
		X->parent->right = Y;

	// if Y is not NULL
	// Y is NULL when a leaf is being deleted
	if (Y != NULL)
		Y->parent = X->parent;
}


// insert new node in the tree
void insert_node(Tree* T, Node* node) {
	Node* temp = T->root;
	Node* parent_node = NULL;	// the trailing pointer, to determine the parent
	// find parent of new node
	while (temp != NULL) {
		parent_node = temp;
		if (node->key < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}	// at the end of the loop, 'parent_node' is the parent of 'node'

	node->parent = parent_node;

	if (parent_node == NULL)
		T->root = node;	// if Tree is empty
	else if (node->key > parent_node->key)
		parent_node->right = node;	// if key is greater than the parent
	else
		parent_node->left = node;	// if key is less than the parent
}


// return the predecessor node
Node* get_predecessor(Node* node) {
	// if a left node exists, then predecessor is max key in the left sub-tree
	if (node->left != NULL)
		return get_tree_maximum(node->left);

	Node* node_parent = node->parent;
	// the predecessor of the queried node is the first ancestor
	// to which the queried is a descendant in the right sub-tree
	while (node_parent != NULL && node_parent->left == node) {
		node = node_parent;
		node_parent = node_parent->parent;
	}
	return node_parent;
}


// return the successor node
Node* get_successor(Node* node) {
	// if a right node exists, then successor is min key in the right sub-tree
	if (node->right != NULL)
		return get_tree_minimum(node->right);

	Node* node_parent = node->parent;	// keep track of the parent node
	// the successor of the queried node is the first ancestor
	// to which the queried node is a descendant in the left sub-tree
	while (node_parent != NULL && node_parent->right == node) {
		node = node_parent;
		node_parent = node_parent->parent;
	}
	return node_parent;
}


// return the node with max key
Node* get_tree_maximum(Node* node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}


// return the node with min key
Node* get_tree_minimum(Node* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}


// search if node with matching key 'k' exists (iterative routine)
Node* search_key_iterative(Node* node, int k) {
	// using a while loop
	while (node != NULL && node->key != k) {
		if (k < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}


// in-order tree walk (recursive routine); (Left - Root - Right)
// tree root is the argument passed
void in_order_btree_walk(Node* node) {
	if (node != NULL) {
		in_order_btree_walk(node->left);
		// process the current node here
		printf("key = %d, data = %d\n", node->key, node->data);
		in_order_btree_walk(node->right);
	}
}


// pre-order tree walk (recursive routine); (Root - Left - Right)
void pre_order_btree_walk(Node* node) {
	if (node != NULL) {
		// process the current node here
		printf("key = %d, data = %d\n", node->key, node->data);
		pre_order_btree_walk(node->left);
		pre_order_btree_walk(node->right);
	}
}


// post-order tree walk (recursive routine); (Left - Right - Root)
void post_order_btree_walk(Node* node) {
	if (node != NULL) {
		post_order_btree_walk(node->left);
		post_order_btree_walk(node->right);
		// process the current node here
		printf("key = %d, data = %d\n", node->key, node->data);
	}
}