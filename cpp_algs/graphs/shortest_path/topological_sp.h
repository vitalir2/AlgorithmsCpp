#ifndef TOPOLOGICAL_SP_H
#define TOPOLOGICAL_SP_H

#include <stack>
#include <vector>

#include "topological_w.h"
#include "weighted_digraph.h"

class TopologicalSP {
using Edge = WeightedDigraph::Edge;
public:
  TopologicalSP(const WeightedDigraph& graph);
  std::stack<Edge> pathTo(int v);
  double distTo(int v);
private:
  WeightedDigraph graph_;

  std::vector<Edge> edge_to_;
  std::vector<double> dist_to_;
  void relaxAdj(int v);
  void relax(const Edge& edge);
};

#endif // TOPOLOGICAL_SP_H
