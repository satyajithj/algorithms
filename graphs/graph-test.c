#include <stdio.h>
#include <stdlib.h>
#include "graph-basic.h"

int main(int argc, char const *argv[]) {

  graph *g = malloc(sizeof(graph));     // declare a graph pointer and allocate memor
  read_graph_file(g, "6-c-u.txt", false);  // read graph data from specified file
  print_graph(g);

  printf("\n");
  return 0;
}
