#ifndef BELLMAN_FORD_SP_H
#define BELLMAN_FORD_SP_H

#include <deque>
#include <stack>
#include <vector>

#include "weighted_digraph.h"

// Standard Bellman-Ford algorithm
class BellmanFordSP {
using Edge = WeightedDigraph::Edge;
public:
  BellmanFordSP(const WeightedDigraph& graph, int source);

  std::stack<Edge> pathTo(int v) const;
  double distTo(int v) const {
    return dist_to_[v];
  }

private:
  void relax(const Edge& edge);

  WeightedDigraph graph_;
  
  std::vector<Edge> edge_to_;
  std::vector<double> dist_to_;
};

#endif // BELLMAN_FORD_SP_H
