#include <limits>
#include <queue>

#include "bellman_ford.h"
#include "weighted_digraph.h"

BellmanFordSP::BellmanFordSP(const WeightedDigraph& graph, int source) : graph_(graph),
  edge_to_(graph.V()), dist_to_(graph.V(), std::numeric_limits<double>::infinity()) {
    dist_to_[source] = 0;

    for (int v = 0; v < graph_.V(); ++v) {
      for (Edge e: graph_.edges()) {
          relax(e);
      }
    }
}

void BellmanFordSP::relax(const Edge& edge) {
  if (dist_to_[edge.to()] > dist_to_[edge.from()] + edge.weight()) {
    edge_to_[edge.to()] = edge;
    dist_to_[edge.to()] = dist_to_[edge.from()] + edge.weight();
  }
}
std::stack<WeightedDigraph::Edge> BellmanFordSP::pathTo(int v) const {
  std::stack<Edge> path;
  for (int x = v; x != 0; x = edge_to_[x].from()) {
    path.push(edge_to_[x]);
  }
  return path;
}
