#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>


class Graph {
  using Vertex = std::vector<int>;
public:
  Graph() = default;
  Graph(int V) {
    adj_list.reserve(V);
    directions.reserve(V);
    colors.resize(V, false);
  }
  ~Graph() = default;

  void addEdge(int v, int q) {
    adj_list[v].push_back(q);
    adj_list[q].push_back(v);
  }

  Vertex adj(int v) const {
    return adj_list[v];
  }
  Vertex& adj(int v) {
    return adj_list[v];
  }

  void dfs(int source_) {
    source = source_;
    colors[source] = true;
    dfsRecCycle(source, source);
  }

  // without upgrades like bipartite etc
  void dfs_stack(int source_) {
    source = source_;
    std::stack<int> vertices;
    vertices.push(source);
    while (!vertices.empty()) {
      int v = vertices.top();
      vertices.pop();
      for (int vertex: adj(v)) {
        if (!visited[vertex]) {
          vertices.push(vertex);
          visited[vertex] = true;
          directions[vertex] = v;
        }
      }
    }
  }

  bool hasPath(int v) const { // for the last vertex in dfs
    try {
      return visited.at(v);
    } catch (...) {
      return false;
    }
  }
  std::stack<int> pathTo(int v) const {
    std::stack<int> result;
    if (!hasPath(v)) {
      return result;
    }
    for (int x = v; x != source; x = directions[x]) {
      result.push(x);
    }
    result.push(source);
    return result;
  }

  bool isBipartite() const {
    return is_bipartite_;
  }

  bool isAcyclic() const {
    return is_acyclic_;
  }

private:
  std::vector<Vertex> adj_list;
  std::map<int, bool> visited;
  std::vector<int> directions;
  int source;

  std::vector<bool> colors;
  bool is_bipartite_ = true;

  bool is_acyclic_ = true;

  void dfsRec(int v) {
    visited[v] = true;
    for (int vertex: adj(v)) {
      if (!visited[vertex]) {
        colors[vertex] = !colors[v];
        dfsRec(vertex);
        directions[vertex] = v;
      } else if (colors[vertex] == colors[v]) {
        is_bipartite_ = false;
      }
    }
  }

  void dfsRecCycle(int v, int q) {
    visited[v] = true;
    for (int vertex: adj(v)) {
      if (!visited[vertex]) {
        colors[vertex] = !colors[v];
        dfsRecCycle(vertex, v);
        directions[vertex] = v;
      } else {
        if (colors[vertex] == colors[v]) {
          is_bipartite_ = false;
        }
        if (vertex != q) {
          is_acyclic_ = false;
        }
      }
    }
  }
};



int main() {
  int v;
  int e;
  std::cout << "Number of vertices and edges\n";
  std::cin >> v >> e;
  Graph graph(v);
  std::cout << "Coords of edges\n";
  for (int i = 0; i < e; ++i) {
    int p1, p2;
    std::cin >> p1 >> p2;
    graph.addEdge(p1, p2);
  }
  int source;
  std::cout << "Source for dfs search\n";
  std::cin >> source;
  graph.dfs(source);
  int x;
  std::cout << "Path to vertex ?\n";
  std::cin >> x;
  std::stack<int> path_x = graph.pathTo(x);
  while (!path_x.empty()) {
    int v = path_x.top();
    path_x.pop();
    std::cout << v << " ";
  }
  std::cout << std::endl;
  std::cout << "Graph" << (graph.isBipartite() ? " is bipartite\n" : " is not bipartite\n");
  std::cout << "Graph" << (graph.isAcyclic() ? " is acyclic\n" : " is cyclic\n");
  return 0;
}
