#include <iostream>

#include "flow_graph.h"
#include "ford_fulkerson.h"

int main() {
  int V = 0;
  int E = 0;
  std::cout << "Enter number of vertices and edges\n";
  std::cin >> V >> E;
  FlowGraph graph(V);
  std::cout << "Enter edges\n";
  for (int i = 0; i < E; ++i) {
    int v1 = 0, v2 = 0;
    double capacity = 0;
    std::cin >> v1 >> v2 >> capacity;
    graph.addEdge({v1, v2, capacity});
  }
  std::cout << "Source and sink for Ford-Fulkerson algorithm: ";
  int source = 0, sink = 0;
  std::cin >> source >> sink;
  FordFulkerson fold_fulkerson(graph, source, sink);
  std::cout << "Max flow from " << source << " to " << sink << " equal " << fold_fulkerson.maxFlow()
    << '\n';
  return 0;
}
