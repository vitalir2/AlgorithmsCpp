#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <vector>

#include "flow_graph.h"

class FordFulkerson {
public:
  FordFulkerson(FlowGraph graph, int source, int sink);
  double maxFlow() const {
    return value_;
  }
private:
  std::vector<int> marked_;
  std::vector<FlowEdge> edge_to_;
  double value_;

  bool existAugmentedPath(const FlowGraph& graph, int source, int sink);
};

#endif // FORD_FULKERSON_H
