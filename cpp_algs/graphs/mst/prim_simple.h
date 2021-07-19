#ifndef PRIM_SIMPLE_H
#define PRIM_SIMPLE_H

#include <iostream>
#include <vector>
#include <queue>

#include "weighted_graph.h"

class PrimMST {
public:
  using Edge = WeightedGraph::Edge;

  explicit PrimMST(const WeightedGraph& graph) : graph_(graph), marked_(graph.V(), 0) {
    calculate();
  }

  std::queue<Edge> edges() const {
    return mst_;
  }

private:
  void calculate();
  void visit(int v);

  WeightedGraph graph_;
  std::vector<int> marked_;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

  std::queue<Edge> mst_;
};

#endif // PRIM_SIMPLE_H
