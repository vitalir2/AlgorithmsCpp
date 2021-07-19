#include <limits>

#include "dijkstra_sp.h"
#include "weighted_digraph.h"

using Edge = WeightedDigraph::Edge;

DijkstraSP::DijkstraSP(const WeightedDigraph& graph, int source) : graph_(graph), pq(graph.V()) {
  edge_to_.resize(graph.V());
  dist_to_.resize(graph.V(), std::numeric_limits<double>::infinity());
  dist_to_[source] = 0;
  pq.insert(source, 0);
  while (!pq.isEmpty()) {
    relaxAdj(pq.delMin());
  }
}

void DijkstraSP::relaxAdj(int v) {
  for (Edge edge: graph_.adj(v)) {
    relax(edge);
  }
}

void DijkstraSP::relax(const Edge& edge) {
  // change in weighted graph to take from and to from methods
  int from = edge.from();
  int to = edge.to();
  if (dist_to_[to] > dist_to_[from] + edge.weight()) {
    dist_to_[to] = dist_to_[from] + edge.weight();
    edge_to_[to] = edge;
    if (pq.contains(to)) {
      pq.change(to, dist_to_[to]);
    } else {
      pq.insert(to, dist_to_[to]);
    }
  }
}

std::stack<Edge> DijkstraSP::pathTo(int v) {
  std::stack<Edge> path;
  for (int x = v; x != 0; x = edge_to_[x].from()) {
    path.push(edge_to_[x]);
  }
  return path;
}

double DijkstraSP::distTo(int v) {
  return dist_to_[v];
}
