#include <list>
#include <iostream>
#include <vector>

#include "bfs.cpp"

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
  Bfs bfs(graph);

  int source = 0;
  std::cout << "Enter source of BFS\n";
  std::cin >> source;
  bfs.bfs(source);

  std::cout << "Enter command to make: 0 - distance, 1 - path\n";
  std::cout << "Then enter vertex\n";
//  std::cout << "Enter vertex to find min path between bfs source and that vertex\n";
  while (true) {
    int command_num = 0;
    std::cin >> command_num;
    switch(command_num) {
      case 0: {
        int p;
        std::cin >> p;
        std::cout << "Min dist: " << bfs.shortestDistanceTo(p) << std::endl;
        break;
      }
       case 1: {
        int q;
        std::cin >> q;
        std::cout << "Path: ";
        std::list<int> path = bfs.pathTo(q);
        path.reverse();
        for (int v: path) {
          std::cout << v << " ";
        }
        std::cout << '\n';
        break;
      }
    }
  }
  return 0;
} 
