#include <algorithm>
#include <iostream>

#include "dfs.h"

Dfs::Dfs(const Graph& graph) : graph_(graph) {
  colors.resize(graph.V());
  distances.resize(graph.V());
  cc.resize(graph.V());
  std::fill(colors.begin(), colors.end(), WHITE);
}

void Dfs::dfs(int source) {
  source_ = source;
  int count = 0;
  for (size_t v = 0; v < graph_.adj_list().size(); ++v) {
    if (colors[v] == WHITE) {
      dfsRecursive(v, count);
      ++count;
    }
  }
}

void Dfs::dfsRecursive(int v, int count) {
  colors[v] = GREY;
  cc[v] = count;
  for (int vertex: graph_.adj_list()[v]) {
    if (colors[vertex] == WHITE) {
      dfsRecursive(vertex, count);
      distances[vertex] = v;
    }
  }
  colors[v] = BLACK;
};

bool Dfs::hasPath(int p, int q) {
  return cc[p] == cc[q];
}
