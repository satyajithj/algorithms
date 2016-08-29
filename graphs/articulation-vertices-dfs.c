/*
    author: Satyajith

    algorithm: determining articulation vertices using DFS
    time complexity: O(|V|+|E|)

    run command: $ gcc articulation-vertices-dfc.c ../elementary-datastructures/queue.c graph-basic.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph-basic.h"

typedef enum { NONE, TREE, BACK } EDGE_CLASS;

void dfs(graph *, int);
void process_vertex_early(int);     // the process methods are useful to perform actions when we encounter
void process_edge(int, int);        // a vertex or a certain edge
void process_vertex_late(int);
EDGE_CLASS classify_edge(int, int);

void print_array(int[], int);

// flags for status of each vertex in bfs
bool processed[MAX_V+1];
bool discovered[MAX_V+1];
int parent[MAX_V+1];                // the parent array can be used for interesting applications
int reachable_ancestor[MAX_V+1];
int tree_out_degree[MAX_V+1];

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

// classify the edge type
EDGE_CLASS classify_edge(int x, int y) {
	if (discovered[y] == false)
		return TREE;
	else
		return BACK;
}

// initial processing of vertex
void process_vertex_early(int v) {
	reachable_ancestor[v] = v;		// initialize oldest reachable ancestor to itself
}

// final processing of vertex
void process_vertex_late(int v) {

	bool root;
	int time_v;
	int time_parent;

	if (parent[v] < 1) {
		if (tree_out_degree[v] > 1)
			printf("root articulation vertex: %d \n", v);
		return;
	}

	root = (parent[parent[v]] < 1);		// is parent[v] the root?

	if ((reachable_ancestor[v] == parent[v]) && (!root)) {
		
	}
}

// process visited edge
void process_edge(int x, int y) {

	EDGE_CLASS class;
	class = classify_edge(x, y);

	if (class == TREE)
		tree_out_degree[x]++;
	if ((class == BACK) && (parent[x] != y))
		if (entry_time[y] < entry_time[reachable_ancestor[x]])		// time is checked because we can reach many ancestors
			reachable_ancestor[x] = y;								// ... we need the oldest one
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
