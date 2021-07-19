#include <vector>
#include <queue>

#include "weighted_graph.h"
#include "prim_eager.h"

// Fix it later (my head is aching after index queue xd)
void PrimEagerMST::calculate() {
  dist_to_[0] = 0;
  pq.insert(0, 0);
  visit(0);
  while (!pq.isEmpty()) {
    size_t vertex = pq.delMin();
    if (!marked_[vertex]) {
      visit(vertex);
    }
  }
}

void PrimEagerMST::visit(int v) {
  marked_[v] = 1;
  for (Edge e: graph_.adj(v)) {
    int other = v == e.v ? e.w : e.v;
    if (!marked_[other]) {
      if (e.weight < dist_to_[other]) {
        edge_to_[other] = e;
        dist_to_[other] = e.weight;
        if (pq.contains(other)) {
          pq.change(other, dist_to_[other]);
        } else {
          pq.insert(other, dist_to_[other]);
        }
      }
    }
  }
}
