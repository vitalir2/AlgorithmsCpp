#include "euler_graph.h"

EulerCycle::EulerCycle(const Graph& graph) : graph_(graph) {
  visits.resize(graph_.V());
  for (size_t v = 0; v < visits.size(); ++v) {
    visits[v] = graph_.degree(v);
  }
}

EulerCycle::Cycle EulerCycle::eulerCycle() {
  Cycle cycle;
  if (graph_.isEulerCycle()) {
    int v = 0;
    dfsCycle(v, cycle);
  }
  return cycle;
}

void EulerCycle::dfsCycle(int v, Cycle& cycle) {
  while (visits[v] != 0) {
    int next_edge = graph_.adj_list()[v][--visits[v]];
    dfsCycle(next_edge, cycle);
  }
  cycle.push(v);
}
