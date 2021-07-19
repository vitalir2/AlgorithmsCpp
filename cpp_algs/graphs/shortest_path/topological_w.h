#ifndef TOPOLOGICAL_W_H
#define TOPOLOGICAL_W_H

#include <stack>
#include <vector>

#include "weighted_digraph.h"

class TopologicalWeighted {
public:
  TopologicalWeighted(const WeightedDigraph& digraph);
  std::stack<int> order();
private:
  void dfs(int v);

  WeightedDigraph digraph_;
  std::vector<int> marked_;
  std::vector<int> edge_to_;

  std::stack<int> order_;
};

#endif // TOPOLOGICAL_W_H
