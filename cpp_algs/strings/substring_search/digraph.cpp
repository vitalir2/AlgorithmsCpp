#include <iostream>
#include <vector>

#include "digraph.h"

Digraph::Digraph(size_t V) : V_(V), E_(0) {
  adj_list_.resize(V_);
}

void Digraph::addEdge(int v, int q) {
  adj_list_[v].push_back(q);
  ++E_;
}

Digraph::Vertex Digraph::adj(int v) const {
  return adj_list_[v];
}
