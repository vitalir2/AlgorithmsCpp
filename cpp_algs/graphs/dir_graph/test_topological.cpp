#include <stack>

#include "digraph.h"
#include "topological.h"

int main() {
  int V = 0;
  int E = 0;
  std::cout << "Enter number of vertices and edges\n";
  std::cin >> V >> E;
  Digraph graph(V);
  std::cout << "Enter edges\n";
  for (int i = 0; i < E; ++i) {
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    graph.addEdge(v1, v2);
  }
  Topological topological(graph);
  std::stack<int> order = topological.order();
  std::cout << "Topological order: ";
  while (!order.empty()) {
    std::cout << order.top() << " ";
    order.pop();
  }
  std::cout << '\n';
  return 0;
}
