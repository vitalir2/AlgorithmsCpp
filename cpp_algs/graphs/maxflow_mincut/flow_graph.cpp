#include <vector>

#include "flow_graph.h"

int FlowEdge::other(int v) const {
  if (v == from) {
    return to;
  } else if (v == to) {
    return from;
  } else {
    return -1;
  }
}
double FlowEdge::residualCapacityTo(int v) const {
  if (v == from) {
    return flow;
  } else if (v == to) {
    return capacity - flow;
  } else {
    // Impossible case if input data is correct

    return -1;
  }
}
void FlowEdge::changeFlowTo(int v, double change) {
  if (v == from) {
    flow -= change;
  } else if (v == to) {
    flow += change;
  }
}
