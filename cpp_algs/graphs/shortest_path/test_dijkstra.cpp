#include <iostream>
#include <stack>

#include "weighted_digraph.h"
#include "dijkstra_sp.h"

int main() {
  int V = 0;
  int E = 0;
  std::cout << "Enter number of vertices and edges\n";
  std::cin >> V >> E;
  WeightedDigraph graph(V);
  std::cout << "Enter edges\n";
  for (int i = 0; i < E; ++i) {
    int v1 = 0, v2 = 0;
    double weight = 0;
    std::cin >> v1 >> v2 >> weight;
    graph.addEdge({v1, v2, weight});
  }
  std::cout << "Source for Dijkstra's algorithm: ";
  int source = 0;
  std::cin >> source;
  DijkstraSP dijkstra(graph, source);
  for (int v = 0; v < graph.V(); ++v) {
    std::cout << "Shortest path for " << v << ": ";
    std::stack<WeightedDigraph::Edge> path = dijkstra.pathTo(v);
    while (!path.empty()) {
      WeightedDigraph::Edge edge = path.top();
      path.pop();
      if (path.empty()) {
        std::cout << edge.from() << " -> " << edge.to();
      } else {
        std::cout << edge.from() << " -> ";
      }
    }
    std::cout << "; distance = " << dijkstra.distTo(v) << '\n';
  }
  return 0;
}
