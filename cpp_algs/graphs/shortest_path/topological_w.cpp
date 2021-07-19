#include <stack>

#include "topological_w.h"
#include "weighted_digraph.h"

TopologicalWeighted::TopologicalWeighted(const WeightedDigraph& digraph) : digraph_(digraph),
  marked_(digraph.V(), 0), edge_to_(digraph.V()) {
  dfs(0);
}
std::stack<int> TopologicalWeighted::order() {
  return order_;
}

void TopologicalWeighted::dfs(int v) {
  for (WeightedDigraph::Edge edge: digraph_.adj(v)) {
    if (!marked_[edge.to()]) {
      marked_[edge.to()] = 1;
      edge_to_[edge.to()] = v;
      dfs(edge.to());
    }
  }
  order_.push(v);
}
