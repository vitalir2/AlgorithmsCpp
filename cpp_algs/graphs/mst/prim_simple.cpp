#include <vector>
#include <queue>

#include "weighted_graph.h"
#include "prim_simple.h"

void PrimMST::calculate() {
  visit(0);
  while (!pq.empty()) {
    Edge e = pq.top();
    pq.pop();
    if (!(marked_[e.v] && marked_[e.w])) {
      mst_.push(e);
      if (!marked_[e.v]) {
        visit(e.v);
      }
      if (!marked_[e.w]) {
        visit(e.w);
      }
    }
  }
}

void PrimMST::visit(int v) {
  marked_[v] = 1;
  for (Edge e: graph_.adj(v)) {
    // if v == e.v -> e.w
    int other = v == e.v ? e.w : e.v;
    if (!marked_[other]) {
      pq.push(e);
    }
  }
}
