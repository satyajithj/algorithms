/**
 *	author: satyajith
 *
 *	rb-tree node and tree structure and
 *	method declarations
 */

#include <stdbool.h>

#ifndef RB_TREE_H_
#define RB_TREE_H_

#define BLACK false
#define RED true

// rb-tree node definition
typedef struct red_blk_node {
	int key;						// node's key
	int data;						// data ---- THIS IS TO BE MODIFIED TO SERVE ONE's PURPOSE
	struct red_blk_node* parent;	// pointer to parent node
	struct red_blk_node* left;		// pointer to left child
	struct red_blk_node* right;		// pointer to right child
	bool color;						// if 'true', node color is RED else BLACK
} red_blk_node;

// rb-tree definition
typedef struct red_blk_tree {
	red_blk_node* root;	// rb-tree root
	red_blk_node* nil;	 // rb-tree node
} red_blk_tree;

// rb-tree method declarations --------------------------------------------------------------------------
// rb-tree traversal
void in_order_rbtree_walk(red_blk_node*);								 // in-order traversal
void pre_order_rbtree_walk(red_blk_node*);								 // pre-order traversal
void post_order_rbtree_walk(red_blk_node*);								 // post-order traversal
void node_transplant_rb(red_blk_tree*, red_blk_node*, red_blk_node*);	// replace node with another
// rb-tree editing
red_blk_node* create_rb_tree_node(int, int);					 // create and return a new rb-tree node
void init_rb_tree(red_blk_tree*);								 // initialize a new rb-tree
void insert_node_rbtree(red_blk_tree*, red_blk_node*);			 // insert node
void insert_fixup_rbtree(red_blk_tree*, red_blk_node*);			 // fix up rb-tree after insertion
void delete_node_rbtree(red_blk_tree*, red_blk_node*);			 // delete node
void delete_fixup_rbtree(red_blk_tree*, red_blk_node*);			 // fix up rb-tree after delete
void left_rotate_red_blk_node(red_blk_tree*, red_blk_node*);	 // rotate node left
void right_rotate_red_blk_node(red_blk_tree*, red_blk_node*);	// rotate node right
// rb-tree look up
red_blk_node* search_key_iterative(red_blk_node*, int);	// search for key iteratively
red_blk_node* get_tree_minimum(red_blk_node*);			   // return minimum key node
red_blk_node* get_tree_maximum(red_blk_node*);			   // return maximum key node
red_blk_node* get_successor(red_blk_node*);				   // return successor node
red_blk_node* get_predecessor(red_blk_node*);			   // return predecessor node
// end of method declarations ---------------------------------------------------------------------------

#endif