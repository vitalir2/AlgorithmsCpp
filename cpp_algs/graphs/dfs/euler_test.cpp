#include <iostream>
#include <stack>

#include "graph.h"
#include "euler_graph.h"

int main() {
  int V = 4;
  int E = 4;
  std::cout << "Enter number of vertices and edges\n";
  std::cin >> V >> E;
  Graph graph(V);
  std::cout << "Enter edges\n";
  for (int i = 0; i < E; ++i) {
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    graph.addEdge(v1, v2);
  }

  EulerCycle ec(graph);
  std::stack<int> cycle = ec.eulerCycle();
  while (!cycle.empty()) {
    int vertex = cycle.top();
    cycle.pop();
    std::cout << vertex;
    if (cycle.empty()) {
      std::cout << '\n';
    } else {
      std::cout << " -> ";
    }
  }

  return 0;
}
