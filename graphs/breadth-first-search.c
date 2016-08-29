/*
author: Satyajith

algorithm: Breadth First Search (BFS)

-- A fundamental graph traversal algorithm. It can be used as the basis for many applications
-- Useful for finding shortest path from x to y, only if x is used as the root for BFS.
-- BFS gives shortest path only for unweighted graphs.

time complexity: O(n+m)

run command: $ gcc breadth-first-search.c ../elementary-datastructures/queue.c graph-basic.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph-basic.h"
#include "../elementary-datastructures/queue.h"

void bfs(graph *, int);
void process_vertex_early(int);     // the process methods are useful to perform actions when we encounter
void process_edge(int, int);        // a vertex or a certain edge
void print_array(int[], int);

void find_path(int, int, int[]);    // displays path from start vertex to end vertex

// flags for status of each vertex in bfs
bool processed[MAX_V+1];
bool discovered[MAX_V+1];
int parent[MAX_V+1];                // the parent array can be used for interesting applications

int main(int argc, char const *argv[]) {

	graph *g = (graph *) malloc(sizeof(graph));
	read_graph_file(g, "6-c-u.txt", false);

	for (size_t i = 1; i <= g->nvertices; i++) {
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}

	printf("\n");
	bfs(g, 1);    // call to bfs

	printf("\n%s:", "parents");
	print_array(parent, g->nvertices);

	int s = 2, e = 6;
	printf("\npath from %d to %d: ", s, e);
	find_path(s, e, parent);
	printf("\n");

	return 0;
}

void print_array(int arr[], int n) {
	for (size_t i = 1; i <= n; i++)
	printf(" %d", arr[i]);
}

// initial processing of vertex
void process_vertex_early(int v) {
	printf("processed vertex %d\n", v);
}

// process visited edge
void process_edge(int x, int y) {
	printf("processed edge (%d,%d)\n", x, y);
}

// bfs routine
void bfs(graph *g, int start) {

	printf("-- bfs started\n");

	queue q;            // queue of vertices to visit
	int v;              // current vertex
	int y;              // successor vertex
	edgenode *temp_e;   // pointer to edge

	init_queue(&q);
	enqueue(&q, start);         // add start vertex to the queue
	discovered[start] = true;

	while (!is_empty(&q)) {

		v = dequeue(&q);             // get element from queue
		process_vertex_early(v);     // doing initial processing here
		processed[v] = true;         // update status flag processed
		temp_e = g->edges[v];        // get first incident edge

		// process all adjacent vertices
		while (temp_e != NULL) {
			y = temp_e->y;

			if (processed[y] == false || g->directed)
			process_edge(v, y);

			if (discovered[y] == false){
				enqueue(&q, y);
				discovered[y] = true;
				parent[y] = v;
			}
			temp_e = temp_e->next;  // next edge in list adjacent to v
		}
	}
}

// recursive find path from start vertex to end vertex
void find_path(int start, int end, int parent[]) {

	if (start == end || end == -1)
	printf("%d", start);

	else {
		find_path(start, parent[end], parent);
		printf("-%d", end);
	}
}
