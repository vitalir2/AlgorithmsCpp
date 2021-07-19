#include <algorithm>
#include <utility>

#include "weighted_graph.h"

using Edge = WeightedGraph::Edge;

WeightedGraph::WeightedGraph(int V) : adj_list_(V), V_(V) {
}

bool operator<(const Edge& lhs, const Edge& rhs) {
  return std::tie(lhs.weight, lhs.v, lhs.w)
  < std::tie(rhs.weight, rhs.v, rhs.w);
}

bool operator>(const Edge& lhs, const Edge& rhs) {
  return std::tie(lhs.weight, lhs.v, lhs.w)
  > std::tie(rhs.weight, rhs.v, rhs.w);
}

void WeightedGraph::addEdge(const Edge& edge) {
  adj_list_[edge.v].push_back(edge);
  adj_list_[edge.w].push_back(edge);
}

std::vector<WeightedGraph::Edge> WeightedGraph::adj(int v) const {
  return adj_list_[v];
}

std::set<WeightedGraph::Edge> WeightedGraph::edges() const {
  std::set<Edge> result;
  for (int i = 0; i < V_; ++i) {
    for (Edge edge: adj_list_[i]) {
      result.insert(edge);
    }
  }
  return result;
}

int WeightedGraph::V() const noexcept {
  return V_;
}

int WeightedGraph::degree(int v) const noexcept {
  return adj_list_[v].size();
}

const std::vector<std::vector<WeightedGraph::Edge>>& WeightedGraph::adj_list() const noexcept {
  return adj_list_;
}
