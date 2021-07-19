#include <iostream>

#include "graph.h"
#include "dfs.h"

int main() {
  int V = 0;
  int E = 0;
  std::cout << "Enter number of vertices and edges\n";
  std::cin >> V >> E;
  Graph graph(V);
  std::cout << "Enter edges\n";
  for (int i = 0; i < E; ++i) {
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    graph.addEdge(v1, v2);
  }
  Dfs dfs(graph);

  int source = 0;
  std::cout << "Enter source of DFS\n";
  std::cin >> source;
  dfs.dfs(source);

  std::cout << "Enter edges to find if path exist\n";
  while (true) {
    int p, q;
    std::cin >> p >> q;
    std::cout << "Path between " << p << " and " << q << " is " << dfs.hasPath(p, q) << std::endl;
  }
  return 0;
}
