#include <algorithm>
#include <iostream>

#include "dfs.h"
#include "digraph.h"

Dfs::Dfs(const Digraph& graph) : graph_(graph) {
  marked_.resize(graph.V());
}

void Dfs::dfs(int source) {
  sources_.insert(source);
  marked_[source] = true;
  dfsRecursive(source);
}

void Dfs::dfs(const std::unordered_set<size_t>& sources) {
  for (int v: sources) {
    dfs(v);
  }
}

void Dfs::dfsRecursive(int v) {
  for (int vertex: graph_.adj_list()[v]) {
    if (!marked_[vertex]) {
      marked_[vertex] = true;
      dfsRecursive(vertex);
    }
  }
};

void Dfs::clearDfs() {
  sources_.clear();
  marked_.clear();
  marked_.resize(graph_.V());
}

bool Dfs::marked(int v) const {
  return marked_[v];
}
