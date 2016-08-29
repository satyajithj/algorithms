/*
    author: Satyajith

    algorithm: Depth First Search (DFS)

    -- A fundamental graph traversal algorithm. It can be used as the basis for many applications

    time complexity: O(|V|+|E|)		-- for traversing without repetition

    run command: $ gcc depth-first-search.c ../elementary-datastructures/queue.c graph-basic.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph-basic.h"

void dfs(graph *, int);
void process_vertex_early(int);     // the process methods are useful to perform actions when we encounter
void process_edge(int, int);        // a vertex or a certain edge
void process_vertex_late(int);

void print_array(int[], int);

void find_path(int, int, int[]);    // displays path from start vertex to end vertex

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
	read_graph_file(g, "6-c-u.txt", false);

	for (size_t i = 1; i <= g->nvertices; i++) {
		processed[i] = discovered[i] = false;
		entry_time[i] = exit_time[i] = -1;
		parent[i] = -1;
	}

	printf("\n-- dfs started\n");
	dfs(g, 1);

	printf("entry times: ");
	print_array(entry_time, g->nvertices);
	printf("\nexit times: ");
	print_array(exit_time, g->nvertices);
	printf("\n");

	return 0;
}

void print_array(int arr[], int n) {
	for (size_t i = 1; i <= n; i++)
    printf(" %d", arr[i]);
}

// initial processing of vertex
void process_vertex_early(int v) {
	printf("early processed vertex %d\n", v);
}

// final processing of vertex
void process_vertex_late(int v) {
	printf("late processed vertex %d\n", v);
}

// process visited edge
void process_edge(int x, int y) {
	printf("processed edge (%d,%d)\n", x, y);
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

	process_vertex_early(v);

	temp_e = g->edges[v];
	while(temp_e != NULL) {
		y = temp_e->y;
		/*	when this condition is used in the else-if check
			below, it eliminates the processing of edges twice
			-- this is application specific
		*/
		condition = parent[v] != y;

		if (discovered[y] == false) {
			parent[y] = v;
			process_edge(v, y);
			dfs(g, y);				// recursion
		}

		else if ((!processed[y] || g->directed) && condition)
			process_edge(v, y);

		if (finished)
			return;

		temp_e = temp_e->next;
	}

	process_vertex_late(v);
	exit_time[v] = time++;

	processed[v] = true;
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
