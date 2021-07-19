#include <list>
#include <vector>
#include <queue>

#include "graph.h"

class Bfs {
public:
  Bfs(const Graph& graph) : graph_(graph) {
    marked_.resize(graph_.V(), false);
    edge_to_.resize(graph_.V());
    distances_.resize(graph_.V());
  }

  void bfs(int source) {
    source_ = source;
    std::queue<int> vertices;
    marked_[source_] = true;
    distances_[source_] = 0;
    vertices.push(source_);
    while (!vertices.empty()) {
      int v = vertices.front();
      vertices.pop();
      for (int vertex: graph_.adj(v)) {
        if (!marked_[vertex]) {
          marked_[vertex] = true;
          edge_to_[vertex] = v;
          distances_[vertex] = distances_[v] + 1;
          vertices.push(vertex);
        }
      }
    }
  }

  bool hasPathTo(int v) const {
    return marked_[v];
  }

  int shortestDistanceTo(int v) const {
    if (!hasPathTo(v)) {
      return -1;
    }
    return distances_[v];
  }

  std::list<int> pathTo(int v) const {
    std::list<int> result;
    if (hasPathTo(v)) {
      for (int x = v; x != source_; x = edge_to_[x]) {
        result.push_back(x);
      }
      result.push_back(source_);
    }
    return result;
  }

private:
  int source_;
  Graph graph_;
  std::vector<bool> marked_;
  std::vector<int> edge_to_;
  std::vector<int> distances_;
};
