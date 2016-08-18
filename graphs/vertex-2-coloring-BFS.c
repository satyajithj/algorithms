/*
    author: Satyajith

    algorithm: vertex-2-coloring check using BFS

    time complexity: O(n+m)

    run command: $ gcc vertex-2-coloring-BFS.c ../elementary-datastructures/queue.c graph-basic.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph-basic.h"
#include "../elementary-datastructures/queue.h"

typedef enum {UNCOLORED, BLACK, WHITE} COLOR;

bool bfs(graph *, int);
bool process_edge(int, int);        // a vertex or a certain edge
bool two_color(graph *);
COLOR complement(COLOR);            // return the complement color

// flags for status of each vertex in bfs
bool processed[MAX_V+1];
bool discovered[MAX_V+1];
// colors array
COLOR color[MAX_V+1];

int main(int argc, char const *argv[]) {

  graph *g = malloc(sizeof(graph));
  read_graph_file(g, "8-c-u-bip.txt", false);

  for (size_t i = 1; i <= g->nvertices; i++)
    processed[i] = discovered[i] = false;

  bool is_2_color = two_color(g);

  if (is_2_color)
    printf("\n\n%s\n", "g is a vertex 2-colorable graph (is bipartite)");
  else
    printf("\n\n%s\n", "g is NOT a vertex 2-colorable graph (is NOT bipartite)");

  return 0;
}

COLOR complement(COLOR c) {
  if (c == WHITE) return (BLACK);
  if (c == BLACK) return (WHITE);

  return (UNCOLORED);
}

// check for two coloring of a graph
bool two_color(graph *g) {

  size_t i;
  for (i = 1; i <= g->nvertices; i++)
    color[i] = UNCOLORED;

  bool is_2_color = true;

  for (i = 1; i <= g->nvertices; i++) {
    if (discovered[i] == false) {
      color[i] = WHITE;
      is_2_color = bfs(g, i);
      if (!is_2_color)
        return false;
    }
  }
  return true;
}

// process visited edge
bool process_edge(int x, int y) {

  if (color[x] == color[y])
    return false;

  color[y] = complement(color[x]);
  return true;
}

// bfs routine
bool bfs(graph *g, int start) {

  queue q;            // queue of vertices to visit
  int v;              // current vertex
  int y;              // successor vertex
  edgenode *temp_e;   // pointer to edge

  init_queue(&q);
  enqueue(&q, start);         // add start vertex to the queue
  discovered[start] = true;

  while (!is_empty(&q)) {

    v = dequeue(&q);             // get element from queue
    processed[v] = true;         // update status flag processed
    temp_e = g->edges[v];        // get first incident edge

    // process all adjacent vertices
    while (temp_e != NULL) {
      y = temp_e->y;

      if (processed[y] == false || g->directed) {
        if (!process_edge(v, y))                    // if not bipartite, return false
          return false;
      }

      if (discovered[y] == false){
        enqueue(&q, y);
        discovered[y] = true;
      }
      temp_e = temp_e->next;  // next edge in list adjacent to v
    }
  }
  return true;
}
