#include <iostream>
#include <stack>

#include "flow_graph.h"
#include "fattest_path.cpp"

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
  std::cout << "Source and sink for Fattest path algorithm: ";
  int source = 0, sink = 0;
  std::cin >> source >> sink;
  FattestPath fp(graph, source);
  std::cout << "Fattest path from " << source << " to " << sink << " is:\n";
  std::stack<FlowEdge> path = fp.pathTo(sink);
  while (!path.empty()) {
    FlowEdge edge = path.top();
    path.pop();
    if (path.empty()) {
      std::cout << edge.from << " -> " << edge.to;
    } else {
      std::cout << edge.from << " -> ";
    }
  }
  std::cout << "; flow = " << fp.flowTo(sink) << '\n';
  return 0;
}
