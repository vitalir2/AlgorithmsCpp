#ifndef EULER_GRAPH_H
#define EULER_GRAPH_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "graph.h"

class EulerCycle {
public:
  using Cycle = std::stack<int>;

  EulerCycle(const Graph& graph);

  Cycle eulerCycle();

private:
  const Graph graph_;
  std::vector<int> visits;

  void dfsCycle(int v, Cycle& cycle);
};

#endif // EULER_GRAPH_H
