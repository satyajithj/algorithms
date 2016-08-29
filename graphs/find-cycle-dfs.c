/*
    author: Satyajith

    algorithm: Find cycles in a graph using DFS

    time complexity: O(|V|+|E|)		-- for traversing without repetition

    run command: $ gcc find-cycle-dfs.c ../elementary-datastructures/queue.c graph-basic.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph-basic.h"

void dfs(graph *, int);
void process_edge(int, int);        // a vertex or a certain edge

void print_array(int[], int);
void find_path(int, int);

// flags for status of each vertex in bfs
bool processed[MAX_V+1];
bool discovered[MAX_V+1];
int parent[MAX_V+1];                // the parent array can be used for interesting applications

int entry_time[MAX_V+1];			// time intervals have useful properties
int exit_time[MAX_V+1];

bool finished;				// to allow for DFS to terminate if needed
int time;

int main(int argc, char const *argv[]) {

	finished = false;
	time = 0;

	graph *g = malloc(sizeof(graph));
	read_graph_file(g, "8-c-u-bip.txt", false);

	for (size_t i = 1; i <= g->nvertices; i++) {
		processed[i] = discovered[i] = false;
		entry_time[i] = exit_time[i] = -1;
		parent[i] = -1;
	}

	printf("\n-- cycles\n");
	dfs(g, 1);

	return 0;
}

void print_array(int arr[], int n) {
	for (size_t i = 1; i <= n; i++)
    printf(" %d", arr[i]);
}

// process visited edge
void process_edge(int x, int y) {
	if (parent[x] != y) {	// back edge
		printf("cycle from %d to %d: ", y, x);
		find_path(y, x);
		printf("\n");
		finished = true;
	}
}

// bfs routine
void dfs(graph *g, int v) {

	int y;              // successor vertex
	edgenode *temp_e;   // pointer to edge
	bool condition = true;

	if (finished)
		return;

	discovered[v] = true;
	entry_time[v] = time++;		// fill in entry time

	temp_e = g->edges[v];
	while(temp_e != NULL) {
		y = temp_e->y;
		/*	when this condition is used in the else-if check
			below, it eliminates the processing of edges twice
			-- this is application specific
		*/
		condition = (parent[v] != y);

		if (discovered[y] == false) {
			parent[y] = v;
			dfs(g, y);				// recursion
		}

		else if ((!processed[y] || g->directed) && condition)
			process_edge(v, y);

		if (finished)
			return;

		temp_e = temp_e->next;
	}
	exit_time[v] = time++;
	processed[v] = true;
}

// recursive find path from start vertex to end vertex
void find_path(int start, int end) {
	if (start == end || end == -1)
		printf("%d", start);

	else {
		find_path(start, parent[end]);
		printf("-%d", end);
	}
}
