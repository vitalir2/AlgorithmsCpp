#include <algorithm>
#include <utility>

#include "weighted_digraph.h"

using Edge = WeightedDigraph::Edge;

WeightedDigraph::WeightedDigraph(int V) : adj_list_(V), V_(V) {
}

bool operator<(const Edge& lhs, const Edge& rhs) {
  return std::tie(lhs.weight_, lhs.v, lhs.w)
  < std::tie(rhs.weight_, rhs.v, rhs.w);
}

bool operator>(const Edge& lhs, const Edge& rhs) {
  return std::tie(lhs.weight_, lhs.v, lhs.w)
  > std::tie(rhs.weight_, rhs.v, rhs.w);
}

void WeightedDigraph::addEdge(const Edge& edge) {
  adj_list_[edge.from()].push_back(edge);
}

std::vector<WeightedDigraph::Edge> WeightedDigraph::adj(int v) const {
  return adj_list_[v];
}

std::set<WeightedDigraph::Edge> WeightedDigraph::edges() const {
  std::set<Edge> result;
  for (int i = 0; i < V_; ++i) {
    for (Edge edge: adj_list_[i]) {
      result.insert(edge);
    }
  }
  return result;
}

int WeightedDigraph::V() const noexcept {
  return V_;
}

const std::vector<std::vector<WeightedDigraph::Edge>>& WeightedDigraph::adj_list() const noexcept {
  return adj_list_;
}
