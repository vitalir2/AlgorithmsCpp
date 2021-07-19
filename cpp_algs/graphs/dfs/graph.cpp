#include <algorithm>

#include "graph.h"

Graph::Graph() : V_(0) {
}

Graph::Graph(int V) : adj_list_(V), V_(V) {
}

void Graph::addEdge(int p, int q) {
  adj_list_[p].push_back(q);
  adj_list_[q].push_back(p);
}

void Graph::deleteEdge(int p, int q) {
  auto rm1 = std::remove(adj_list_[p].begin(), adj_list_[p].end(), q);
  adj_list_[p].erase(rm1, adj_list_[p].end());
  auto rm2 = std::remove(adj_list_[q].begin(), adj_list_[q].end(), p);
  adj_list_[q].erase(rm2, adj_list_[q].end());
}

Graph::Vertex Graph::adj(int v) const {
  return adj_list_[v];
}

int Graph::V() const noexcept {
  return V_;
}

int Graph::degree(int v) const noexcept {
  return adj_list_[v].size();
}

const std::vector<Graph::Vertex>& Graph::adj_list() const noexcept {
  return adj_list_;
}

bool Graph::isEulerCycle() const noexcept {
  if (is_euler_.has_value()) {
    return is_euler_.value();
  } else {
    for (size_t v = 0; v < adj_list_.size(); ++v) {
      int deg = degree(v);
      if (deg == 0 || deg % 2 != 0) {
        return false;
      }
    }
    return true;
  }
}
