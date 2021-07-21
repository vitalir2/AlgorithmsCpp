#ifndef BELLMAN_FORD_QUEUE_SP_H
#define BELLMAN_FORD_QUEUE_SP_H

#include <queue>
#include <stack>
#include <vector>

#include "weighted_digraph.h"

// Faster way Bellman Ford (but without checking negative cycle)
class BellmanFordQSP {
using Edge = WeightedDigraph::Edge;
using Vertex = int;
public:
  BellmanFordQSP(const WeightedDigraph& graph, int source);

  std::stack<Edge> pathTo(int v) const;
  double distTo(int v) const {
    return dist_to_[v];
  }

private:
  void relax(const Edge& edge);
  void relaxAdj(int v);

  WeightedDigraph graph_;
  
  std::vector<Edge> edge_to_;
  std::vector<double> dist_to_;

  std::queue<Vertex> changed_vertices_;
  std::vector<Vertex> was_changed_;
};

#endif // BELLMAN_FORD_QUEUE_SP_H
