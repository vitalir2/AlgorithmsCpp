#include <iostream>
#include <stack>
#include <limits>

#include "topological_sp.h"
#include "topological_w.h"
#include "weighted_digraph.h"

using Edge = WeightedDigraph::Edge;

TopologicalSP::TopologicalSP(const WeightedDigraph& graph) : graph_(graph),
edge_to_(graph.V()), dist_to_(graph.V(), std::numeric_limits<double>::infinity()) {
  TopologicalWeighted tw(graph);
  std::stack<int> order = tw.order();
  dist_to_[order.top()] = 0;

  while (!order.empty()) {
    relaxAdj(order.top());
    order.pop();
  }
}

void TopologicalSP::relaxAdj(int v) {
  for (Edge edge: graph_.adj(v)) {
    relax(edge);
  }
}

void TopologicalSP::relax(const Edge& edge) {
  if (dist_to_[edge.to()] > dist_to_[edge.from()] + edge.weight()) {
    edge_to_[edge.to()] = edge;
    dist_to_[edge.to()] = dist_to_[edge.from()] + edge.weight();
  }
}

std::stack<Edge> TopologicalSP::pathTo(int v) {
  std::stack<Edge> path;
  for (int x = v; x != 0; x = edge_to_[x].from()) {
    path.push(edge_to_[x]);
  }
  return path;
}

double TopologicalSP::distTo(int v) {
  return dist_to_[v];
}
