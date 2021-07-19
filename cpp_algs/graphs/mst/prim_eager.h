#include <iostream>
#include <limits>
#include <vector>
#include <queue>

#include "weighted_graph.h"
#include "indexed_queue.h"

class PrimEagerMST {
public:
  using Edge = WeightedGraph::Edge;

  explicit PrimEagerMST(const WeightedGraph& graph) : graph_(graph), marked_(graph.V(), 0),
    edge_to_(graph.V()), dist_to_(graph.V(), std::numeric_limits<double>::infinity()),
    pq(graph.V()) {
    calculate();
  }

  std::queue<Edge> edges() const {
    if (mst_.empty()) {
      for (size_t i = 1; i < edge_to_.size(); ++i) {
        mst_.push(edge_to_[i]);
      }
    }
    return mst_;
  }

private:
  void calculate();
  void visit(int v);

  WeightedGraph graph_;
  std::vector<int> marked_;
  std::vector<Edge> edge_to_;
  std::vector<double> dist_to_;
  IndexQueue<double> pq;

  mutable std::queue<Edge> mst_;
};
