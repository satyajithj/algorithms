/**
 *	author: satyajith
 *	program: red black tree sample program
 *
 *	note: the sentinel's key is -9999
 */

#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

#define N 10

int main(int argc, char const* argv[]) {
	// sample program here
	int keys[ N ] = {7, 21, 10, 12, 16, 14, 15, 17, 3, 19};
	int values[ N ] = {44, 11, 7, 5, 32, 21, 42, 18, 99, 100};

	red_blk_tree* rbt = (red_blk_tree*) malloc(sizeof(red_blk_tree));
	init_rb_tree(rbt);


	for (int i = 0; i < N; ++i)
		insert_node_rbtree(rbt, create_rb_tree_node(keys[ i ], values[ i ]));

	printf("\nin-order traversal");
	in_order_rbtree_walk(rbt->root);

	return 0;
}