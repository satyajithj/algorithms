#include <stdio.h>

#define MAX_V	100		// max vertices

typedef struct {
	int y;						// adjacency info
	int weight;					// edge weight if any
	struct edgenode	*next;		// next edge in list
} edgenode;

typedef struct {
	edgenode *edges[MAX_V + 1];	// adjacency info
	int degree[MAX_V + 1]		// outdegree of each vertex
	int nvertices;				// number of vertices
	int nedges;					// number of edges
	bool directed;				// is the graph directed?
} graph;

void initialize_graph(graph *, bool);
void read_graph(graph *, bool);
void insert_edge(graph, int, int, bool);
void print_graph(graph *);
