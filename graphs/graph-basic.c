#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph-basic.h"

// initialize the graph structure
void initialize_graph(graph *g, bool directed) {
	size_t i;
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	for (i = 1; i <= MAX_V; i++)	g->degree[i] = 0;
	for (i = 1; i <= MAX_V; i++)	g->edges[i] = NULL;

  printf("%s\n", "-- graph initialization complete");
}

// read graph info. num vertices, edges and insert edges one by one
void read_graph_stdin(graph *g, bool directed) {

	int m;
	int x, y;
	initialize_graph(g, directed);
	scanf("%d %d", &(g->nvertices), &m);		// number of vertices and edges

	for (size_t i = 1; i < m; i++) {
		scanf("%d %d", &x, &y);
		insert_edge(g, x, y, directed);				// insert edge between vertex x and y
	}

  printf("%s\n", "-- graph read from STDIN complete");
}

// read graph from file
void read_graph_file(graph *g, char *filename, bool directed) {

	char pathname[] = "./graph-files/";
	strcat(pathname, filename);
  FILE *g_file;
  g_file = fopen(pathname, "r");

	int m;
	int x, y;
	initialize_graph(g, directed);

  fscanf(g_file, "%d %d", &(g->nvertices), &m);

	printf("\n-- constructing edges\n");

  for (size_t i = 1; i <= m; i++) {
		fscanf(g_file, "%d %d", &x, &y);
		insert_edge(g, x, y, directed);				// insert edge between vertex x and y
	}

  fclose(g_file);
  printf("-- graph read from %s complete", filename);
}

// insert an edge
void insert_edge(graph *g, int x, int y, bool directed) {

	edgenode *p = NULL;
	p = malloc(sizeof(edgenode));

	p->weight = 0;
	p->y = y;
	p->next = g->edges[x];		// add edgenode reference to the top of adjacency list of the vertex

	g->edges[x] = p;
	g->degree[x]++;

	printf("edge {%d, %d} added\n", x, y);

	if (directed == false)
		insert_edge(g, y, x, true);
	else
		g->nedges++;
}

// print the graph adjacency list
void print_graph(graph *g) {

	edgenode *p;
  printf("\n\n-- graph adjacency list\n");

	for (size_t i = 1; i <= g->nvertices; i++) {
		printf("%zu: ", i);
		p = g->edges[i];

		while (p != NULL) {
			printf(" %d", p->y);
			p = p->next;
		}

		printf("\n");
	}
}
