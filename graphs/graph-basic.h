/*
	author: Satyajith J

	-- consists of basic data structures and methods to perform operation on graphs
	-- graph can be read from a file too
*/

#include <stdbool.h>

#ifndef GRAPH_BASIC_H
#define GRAPH_BASIC_H

#define MAX_V	100		// max vertices

typedef struct {
	int y;						// adjacency info
	int weight;					// edge weight if any
	struct edgenode	*next;		// next edge in list
} edgenode;

typedef struct {
	edgenode *edges[MAX_V + 1];	// adjacency info
	int degree[MAX_V + 1];		// outdegree of each vertex
	int nvertices;				// number of vertices
	int nedges;					// number of edges
	bool directed;				// is the graph directed?
} graph;

void initialize_graph(graph *, bool);											// initialize the graph structure
void insert_edge(graph *, int, int, bool);								// insert edge between specified vertices
void print_graph(graph *);																// print graph adjacency list
void read_graph_stdin(graph *, bool);											// read graph from user input
void read_graph_file(graph *, char *, bool);				// read graph from a file

#endif
