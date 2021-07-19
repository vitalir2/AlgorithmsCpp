#include <iostream>
#include <queue>

#include "weighted_graph.h"
#include "union_find.h"

class KruskalMST {
public:
  using Edge = WeightedGraph::Edge;

  KruskalMST(WeightedGraph wgraph) : graph_(wgraph) {
    this->calculate();
  }

  void calculate() {
    auto cmp = [](const Edge& lhs, const Edge& rhs) 
    { return lhs.weight > rhs.weight; };
    // fuck you boy decltype??
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);
    for (Edge edge: graph_.edges()) {
      std::cerr << edge.v << " " <<  edge.w << std::endl;
      pq.push(edge);
    }
    UnionFind uf(graph_.V());
    while (!pq.empty() && static_cast<int>(mst_.size()) < graph_.V() - 1) {
      Edge e = pq.top();
      pq.pop();
      if (!uf.connected(e.v, e.w)) {
        uf.unionF(e.v, e.w);
        mst_.push(e);
      }
    }
  }

  int weight() const noexcept {
    return weight_;
  }

  std::queue<Edge> edges() {
    return mst_;
  }

private:
  WeightedGraph graph_;

  std::queue<Edge> mst_;
  int weight_;
};
