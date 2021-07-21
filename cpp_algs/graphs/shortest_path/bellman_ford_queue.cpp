#include <limits>
#include <queue>

#include "bellman_ford_queue.h"
#include "weighted_digraph.h"

BellmanFordQSP::BellmanFordQSP(const WeightedDigraph& graph, int source) : graph_(graph),
  edge_to_(graph.V()), dist_to_(graph.V(), std::numeric_limits<double>::infinity()),
  was_changed_(graph.V(), 0) {
    dist_to_[source] = 0;

    changed_vertices_.push(source);
    while (!changed_vertices_.empty()) {
      int v = changed_vertices_.front();
      changed_vertices_.pop();
      was_changed_[v] = 0;
      relaxAdj(v);
    }
}

void BellmanFordQSP::relaxAdj(int v) {
  for (const Edge& edge: graph_.adj(v)) {
    relax(edge);
  }
}

void BellmanFordQSP::relax(const Edge& edge) {
  if (dist_to_[edge.to()] > dist_to_[edge.from()] + edge.weight()) {
    edge_to_[edge.to()] = edge;
    dist_to_[edge.to()] = dist_to_[edge.from()] + edge.weight();
    if (!was_changed_[edge.to()]) {
      was_changed_[edge.to()] = 1;
      changed_vertices_.push(edge.to());
    }
  }
}
std::stack<WeightedDigraph::Edge> BellmanFordQSP::pathTo(int v) const {
  std::stack<Edge> path;
  for (int x = v; x != 0; x = edge_to_[x].from()) {
    path.push(edge_to_[x]);
  }
  return path;
}
