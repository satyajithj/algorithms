/*
    author: Satyajith

    algorithm: counting Connected Components using BFS
    -- count the number of components in a given input graph

    time complexity: O(n+m)

    run command: $ gcc connected-components-BFS.c ../elementary-datastructures/queue.c graph-basic.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph-basic.h"
#include "../elementary-datastructures/queue.h"

void bfs(graph *, int);
int num_connected_comp(graph *);

// flags for status of each vertex in bfs
bool discovered[MAX_V+1];

int main(int argc, char const *argv[]) {

  graph *g = malloc(sizeof(graph));
  read_graph_file(g, "10-d-u.txt", false);

  for (size_t i = 1; i <= g->nvertices; i++)
    discovered[i] = false;

  int num_cc = num_connected_comp(g);     // call to num connected components
  printf("\n\ng consists of %d connected comp\n", num_cc);

  return 0;
}

// method to count the number of connected components
int num_connected_comp(graph *g) {

  int c = 0;
  for (size_t i = 1; i <= g->nvertices; i++) {
    if (discovered[i] == false) {
      c++;                // there is at least 1 connected component
      bfs(g, i);          // run BFS starting at a vertex not discovered
    }
  }

  // instead of counting the individual components can be extracted as multiple graph
  // objects to process. These operations become very feasible and will not make a clutter in
  // an object oriented environment

  return c;
}

// bfs routine
void bfs(graph *g, int start) {

  queue q;            // queue of vertices to visit
  int v;              // current vertex
  int y;              // successor vertex
  edgenode *temp_e;   // pointer to edge

  init_queue(&q);
  enqueue(&q, start);         // add start vertex to the queue
  discovered[start] = true;

  while (!is_empty(&q)) {

    v = dequeue(&q);             // get element from queue
    temp_e = g->edges[v];        // get first incident edge

    // process all adjacent vertices
    while (temp_e != NULL) {
      y = temp_e->y;

      if (discovered[y] == false){
        enqueue(&q, y);
        discovered[y] = true;
      }
      temp_e = temp_e->next;  // next edge in list adjacent to v
    }
  }
}
