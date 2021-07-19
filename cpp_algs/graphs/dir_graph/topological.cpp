#include <stack>

#include "topological.h"
#include "digraph.h"

Topological::Topological(const Digraph& digraph) : digraph_(digraph),
  marked_(digraph.V(), 0), edge_to_(digraph.V()) {
  dfs(0);
}
std::stack<int> Topological::order() {
  return order_;
}

void Topological::dfs(int v) {
  for (int w: digraph_.adj(v)) {
    if (!marked_[v]) {
      marked_[w] = 1;
      edge_to_[w] = v;
      dfs(w);
    }
  }
  order_.push(v);
}
