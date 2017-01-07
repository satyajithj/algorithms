/**	
 * 	author: satyajith
 * 	
 *	differences from binary tree routines lie in the
 *	INSERT and DELETE functions only, as the RB tree
 *	coloring needs to be maintained to keep it balanced
 */

#include "rb_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("\n> I AM HERE RIGHT NOW!");

// init a rb-tree
void init_rb_tree(red_blk_tree* rbt) {
	// allocate tree

	rbt->nil = rbt->root = NULL;

	rbt->nil = (red_blk_node*) malloc(sizeof(red_blk_node));	// initialize the sentinel node
	rbt->nil->color = BLACK;
	rbt->nil->parent = NULL;
	rbt->nil->left = NULL;
	rbt->nil->right = NULL;
	rbt->nil->key = -9999;
	rbt->nil->data = 0;

	rbt->root = rbt->nil;	// initially point root to the sentinel

	printf("\n> rb-tree initialized");
}

// create a new rb-tree node
red_blk_node* create_rb_tree_node(int key, int value) {
	// dynamically allocate new node
	red_blk_node* t = (red_blk_node*) malloc(sizeof(red_blk_node));
	t->key = key;
	t->data = value;

	t->parent = NULL;
	t->left = NULL;
	t->right = NULL;

	t->color = RED;	// always insert a RED node (-- think why --)

	printf("\n> init (k: %d, v: %d)", key, value);

	return t;
}

// fix-up RB-tree after delete
void delete_fixup_rbtree(red_blk_tree* rbt, red_blk_node* x) {
	red_blk_node* w = NULL;
	// x is a doubly-black node
	while (x != rbt->root && x->color == BLACK) {
		// 8 cases; 4 symmetric pairs
		if (x == x->parent->left) {
			// if x is its parent's left child
			w = x->parent->right;	// x's sibling
			// if w is colored RED - case 1
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate_red_blk_node(rbt, x->parent);
				w = x->parent->right;
			}
			// case 2 - both w's children are colored BLACK
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			// if w is not RED or w's both children are not BLACK
			else {
				// case 3 - w's left child is RED and right child is BLACK
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotate_red_blk_node(rbt, w);
					w = x->parent->right;
				}
				// case 4 - w's right child is RED
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate_red_blk_node(rbt, x->parent);
				x = rbt->root;
			}
		} else {
			// if x is its parent's right child
			w = x->parent->left;	// x's sibling
			// if w is colored RED - case 1
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate_red_blk_node(rbt, x->parent);
				w = x->parent->left;
			}
			// case 2
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			// if w is not RED or w's both children are not BLACK
			else {
				// case 3 - w's right child is RED and left child is BLACK
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate_red_blk_node(rbt, w);
					w = x->parent->left;
				}
				// case 4 - w's left child is RED
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate_red_blk_node(rbt, x->parent);
				x = rbt->root;
			}
		}
	}
	// x is a red-and-black node
	x->color = BLACK;
	w = NULL;
}


// delete node z from RB-Tree
void delete_node_rbtree(red_blk_tree* rbt, red_blk_node* z) {
	red_blk_node* y = z;
	red_blk_node* x = NULL;

	bool y_orig_color = y->color;
	// if z's left is the sentinel, replace z with z->right
	if (z->left == rbt->nil) {
		x = z->right;
		node_transplant_rb(rbt, z, z->right);
	}
	// if z's right is the sentinel, replace z with z->right
	else if (z->right == rbt->nil) {
		x = z->left;
		node_transplant_rb(rbt, z, z->left);
	}
	// if both, z's left and right point to the sentinel
	else {
		y = get_tree_minimum(z->right);
		y_orig_color = y->color;	// as RB-Tree properties may be violated in this region
		x = y->right;
		// if y is z's child
		if (y->parent == z)
			x->parent = y;	// x can be the sentinel
		// if y is not z's child
		else {
			node_transplant_rb(rbt, y, y->right);
			y->right = z->right;
			y->right->parent = y;	// link z's right child and node y
		}
		// replace z with y
		node_transplant_rb(rbt, z, y);
		y->left = z->left;
		y->left->parent = y;	// link z's left with y
		y->color = z->color;	// y is placed with the appropriate color

		// no fix up is required at node y's new position here
		// RB-Tree properties may be violated at y's old position (node x)
	}

	if (y_orig_color == BLACK)
		delete_fixup_rbtree(rbt, x);
}


// replace node X in rbt with node Y
void node_transplant_rb(red_blk_tree* rbt, red_blk_node* X, red_blk_node* Y) {
	// if X is root, it's parent is the sentinel
	if (X->parent == rbt->nil)
		rbt->root = Y;
	// if X is left child of X->parent
	else if (X == X->parent->left)
		X->parent->left = Y;
	// if X is right child
	else
		X->parent->right = Y;

	Y->parent = X->parent;	// unconditional; as Y can point to sentinel


	// there are cases where we manipulate the sentinel's parent to
	// run a procedure even though a sentinel has no specific parent
}

/*
	The fix up RB-tree method is complicated to understand if you
	just read it. Read on why the procedure is followed as coded
	here and understand the proof that is presented in the
	"CLRS - Introduction to Algorithms" text on Red Black Trees in
	chapter 13. It is very well explained and intuitive.
 */

// fix up RB-tree after insertion
void insert_fixup_rbtree(red_blk_tree* rbt, red_blk_node* n) {
	// pointer to n's uncle
	red_blk_node* y = NULL;

	// 6 cases; 3 are symmetric
	while (n->parent->color == RED) {
		// if n's parent is it's grand parent's left child
		if (n->parent == n->parent->parent->left) {
			y = n->parent->parent->right;	// n's uncle

			if (y->color == RED) {
				n->parent->color = BLACK;
				y->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			} else {
				if (n == n->parent->right) {
					n = n->parent;
					left_rotate_red_blk_node(rbt, n);
				}

				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				right_rotate_red_blk_node(rbt, n->parent->parent);
			}
		} else {
			// if n's parent is it's grand parent's right child
			y = n->parent->parent->left;	// n's uncle

			if (y->color == RED) {
				n->parent->color = BLACK;
				y->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			} else {
				if (n == n->parent->left) {
					n = n->parent;
					right_rotate_red_blk_node(rbt, n);
				}

				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				left_rotate_red_blk_node(rbt, n->parent->parent);
			}
		}
	}

	rbt->root->color = BLACK;	// set root to BLACK
	printf(" - rb-tree fixed-up");
}


// insert new node
void insert_node_rbtree(red_blk_tree* rbt, red_blk_node* n) {
	red_blk_node* y = rbt->nil;
	red_blk_node* x = rbt->root;

	while (x != rbt->nil) {
		y = x;
		if (n->key < x->key)
			x = x->left;
		else
			x = x->right;
	}	// at the end of the loop, n is to be inserted as child of y

	n->parent = y;	// n's parent is y

	/*
		in the following lines of code, the left and right children of
		the new node is set to the sentinel (rbt->nil) and the node's relevant
		parent is assigned
	*/

	if (y == rbt->nil) {	// tree is empty
		rbt->root = n;
		rbt->root->parent = rbt->nil;
		rbt->root->left = rbt->nil;
		rbt->root->right = rbt->nil;
	}

	else if (n->key < y->key) {
		n->left = rbt->nil;
		n->right = rbt->nil;
		y->left = n;
		y->left->parent = y;
	}

	else {
		n->left = rbt->nil;
		n->right = rbt->nil;
		y->right = n;
		y->right->parent = y;
	}

	printf("\n> insert (k: %d, v: %d)", n->key, n->data);
	insert_fixup_rbtree(rbt, n);	// fix up the tree after the insertion
}


// rotate right
void right_rotate_red_blk_node(red_blk_tree* rbt, red_blk_node* y) {
	red_blk_node* x = y->left;	// get y's left node

	y->left = x->right;
	if (y->left != NULL)
		y->left->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL)	// if y is root of RB-Tree
		rbt->root = x;
	else if (y->parent->left == y)	// if y is its parent's left child
		y->parent->left = x;
	else	// if y is its parent's right child
		y->parent->right = x;

	y->parent = x;	// make x, y's parent
	x->right = y;	 // make y, x's right child
}


// rotate left
void left_rotate_red_blk_node(red_blk_tree* rbt, red_blk_node* x) {
	red_blk_node* y = x->right;	// get right node to x

	x->right = y->left;
	if (x->right != NULL)
		x->right->parent = x;	// if y's left is not NULL then update it's new parent

	y->parent = x->parent;	// link y to x's previous parent

	if (x->parent == rbt->nil)	// if x is root of rb-Tree
		rbt->root = y;
	else if (x->parent->left == x)	// if x is its parent's left child
		x->parent->left = y;
	else	// if x is its parent's right child
		x->parent->right = y;

	x->parent = y;	// make y, x's parent
	y->left = x;	  // make x, y's left child
}


// return the predecessor node
red_blk_node* get_predecessor(red_blk_node* node) {
	// if a left node exists, then predecessor is max key in the left sub-tree
	if (node->left != NULL)
		return get_tree_maximum(node->left);

	red_blk_node* node_parent = node->parent;
	// the predecessor of the queried node is the first ancestor
	// to which the queried is a descendant in the right sub-tree
	while (node_parent != NULL && node_parent->left == node) {
		node = node_parent;
		node_parent = node_parent->parent;
	}
	return node_parent;
}


// return the successor node
red_blk_node* get_successor(red_blk_node* node) {
	// if a right node exists, then successor is min key in the right sub-tree
	if (node->right != NULL)
		return get_tree_minimum(node->right);

	red_blk_node* node_parent = node->parent;	// keep track of the parent node
	// the successor of the queried node is the first ancestor
	// to which the queried node is a descendant in the left sub-tree
	while (node_parent != NULL && node_parent->right == node) {
		node = node_parent;
		node_parent = node_parent->parent;
	}
	return node_parent;
}


// return the node with max key
red_blk_node* get_tree_maximum(red_blk_node* node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}


// return the node with min key
red_blk_node* get_tree_minimum(red_blk_node* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}


// search if node with matching key 'k' exists (iterative routine)
red_blk_node* search_key_iterative(red_blk_node* node, int k) {
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
void in_order_rbtree_walk(red_blk_node* node) {
	if (node->key != -9999) {
		in_order_rbtree_walk(node->left);
		// process the current node here
		printf("\nkey = %d, color = %d, data = %d", node->key, node->color, node->data);
		in_order_rbtree_walk(node->right);
	}
}


// pre-order tree walk (recursive routine); (Root - Left - Right)
void pre_order_rbtree_walk(red_blk_node* node) {
	if (node->key != -9999) {
		// process the current node here
		printf("key = %d, color = %d, data = %d\n", node->key, node->color, node->data);
		pre_order_rbtree_walk(node->left);
		pre_order_rbtree_walk(node->right);
	}
}


// post-order tree walk (recursive routine); (Left - Right - Root)
void post_order_rbtree_walk(red_blk_node* node) {
	if (node->key != -9999) {
		post_order_rbtree_walk(node->left);
		post_order_rbtree_walk(node->right);
		// process the current node here
		printf("key = %d, color = %d, data = %d\n", node->key, node->color, node->data);
	}
}
