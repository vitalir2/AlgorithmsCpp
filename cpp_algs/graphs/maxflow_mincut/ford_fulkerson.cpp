#include <iostream> 
#include <limits>
#include <queue>

#include "flow_graph.h"
#include "ford_fulkerson.h"

FordFulkerson::FordFulkerson(FlowGraph graph, int source, int sink) : value_(0) {
  while (existAugmentedPath(graph, source, sink)) {
    double bottleneck = std::numeric_limits<double>::infinity();
    for (int v = sink; v != source; v = edge_to_[v].other(v)) {
      bottleneck = std::min(bottleneck, edge_to_[v].residualCapacityTo(v));
    }

    for (int v = sink; v != source; v = edge_to_[v].other(v)) {
      FlowEdge e = edge_to_[v];
      for (FlowEdge& edge: graph.adj(v)) {
        // we need to change edge in graph, not in vector because it will be destroyed
        if (e.from == edge.from && e.to == edge.to) {
//            std::cerr << "FLOW B " << edge.flow << std::endl;
          edge.changeFlowTo(v, bottleneck);
         // std::cerr << "FLOW A " << edge.flow << std::endl;
        }
      }
      for (FlowEdge& edge: graph.adj(e.other(v))) {
        if (e.from == edge.from && e.to == edge.to) {
          edge.changeFlowTo(v, bottleneck);
        }
      }
    }
    value_ += bottleneck;
  }
}

bool FordFulkerson::existAugmentedPath(const FlowGraph& graph, int source, int sink) {
  marked_.clear();
  marked_.resize(graph.V(), 0);
  edge_to_.clear();
  edge_to_.resize(graph.V());

  std::queue<int> bfs;
  bfs.push(source);
  marked_[source] = 1;
//  std::cerr << "START BFS" << std::endl;
  while (!bfs.empty()) {
    int v = bfs.front();
    bfs.pop();
    for (const FlowEdge& edge: graph.adj(v)) {

      int w = edge.other(v);
      if (!marked_[w]) {
//        std::cerr << "FLOW IN BFS " << edge.flow << std::endl;
      }
      if (!marked_[w] && edge.residualCapacityTo(w) > 0) {
//        std::cerr << "RESCAP: " << edge.residualCapacityTo(w) << std::endl;
        edge_to_[w] = edge;
        marked_[w] = 1;
        bfs.push(w);
      }
    }
  }
//  std::cerr << "END BFS" << std::endl;

  return marked_[sink];
}
