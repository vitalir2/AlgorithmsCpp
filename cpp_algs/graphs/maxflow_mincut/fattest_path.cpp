#include <limits>
#include <vector>
#include <stack>

#include "flow_graph.h"
#include "indexed_queue.h"

// Need to:
// 1) Visit the source node
// 2) Visit adjacent nodes that have the largest residual capacity to the current node
// 3) Return path from source node to sink node
class FattestPath {
public:
  using Path = std::stack<FlowEdge>;
  FattestPath(const FlowGraph& graph, int source) : source_(source),
 pq(graph.V()), graph_(graph) {
    marked_.resize(graph.V(), 0);
    edge_to_.resize(graph.V());
    flow_to_.resize(graph.V(), std::numeric_limits<double>::lowest());
    flow_to_[source] = 0;
    pq.insert(source, 0);
    while (!pq.isEmpty()) {
      int w = pq.delMin();
      visit(w);
    }
  }
  Path pathTo(int w) {
    std::stack<FlowEdge> result;
    for (int k = w; k != source_; k = edge_to_[k].other(k)) {
      result.push(edge_to_[k]);
    }
    return result;
  }

  double flowTo(int w) const {
    return flow_to_[w];
  }

  void visit(int vertex) {
    marked_[vertex] = 1;
    for (const FlowEdge& edge: graph_.adj(vertex)) {
      int w = edge.other(vertex);
      if (!marked_[w]) {
        double edge_weight = 0;
        // because flow always equals 0 in source
        if (vertex == source_) {
          edge_weight = edge.residualCapacityTo(w);
        } else {
          edge_weight = std::min(edge.residualCapacityTo(w), flowTo(vertex));
        }
        if (edge_weight > flow_to_[w]) {
          edge_to_[w] = edge;
          flow_to_[w] = edge_weight;
          if (!pq.contains(w)) {
            // negative for maximum flow (min priority queue)
            pq.insert(w, -flow_to_[w]);
          } else {
            pq.change(w, -flow_to_[w]);
          }
        }
      }
    }
  }
private:
  int source_;
  std::vector<int> marked_;
  std::vector<FlowEdge> edge_to_;
  std::vector<double> flow_to_;
  IndexQueue<double> pq;

  FlowGraph graph_;
};
