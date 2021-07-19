#ifndef TOPOLOGICAL_H
#define TOPOLOGICAL_H

#include <stack>
#include <vector>

#include "digraph.h"

class Topological {
public:
  Topological(const Digraph& digraph);
  std::stack<int> order();
private:
  void dfs(int v);

  Digraph digraph_;
  std::vector<int> marked_;
  std::vector<int> edge_to_;

  std::stack<int> order_;
};

#endif // TOPOLOGICAL_H
