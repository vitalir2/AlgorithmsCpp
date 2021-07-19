#include <queue>

#include "weighted_graph.h"
#include "kruskal.cpp"

int main() {
  int V = 0;
  int E = 0;
  std::cout << "Enter number of vertices and edges\n";
  std::cin >> V >> E;
  WeightedGraph graph(V);
  std::cout << "Enter edges\n";
  for (int i = 0; i < E; ++i) {
    int v1 = 0, v2 = 0;
    double weight = 0;
    std::cin >> v1 >> v2 >> weight;
    graph.addEdge({v1, v2, weight});
  }
  KruskalMST kruskal(graph);
  std::queue<WeightedGraph::Edge> mst = kruskal.edges();
  while (!mst.empty()) {
    WeightedGraph::Edge e = mst.front();
    mst.pop();
    std::cout << e.v << " -> " << e.w << ", weight = " << e.weight << '\n';
  }
  return 0;
}
