#ifndef FLOW_GRAPH_H
#define FLOW_GRAPH_H

#include <vector>

struct FlowEdge {
  FlowEdge() {}
  FlowEdge(int v, int w, double capacity) : from(v), to(w), capacity(capacity),
 flow (0) {
  }
  int other(int v) const;
  double residualCapacityTo(int v) const;
  void changeFlowTo(int v, double change);

  int from, to;
  double capacity;
  double flow;
};

class FlowGraph {
public:
  using Vertex = std::vector<FlowEdge>;

  FlowGraph(int V) : V_(V) {
    adj_list_.resize(V);
  }
  void addEdge(FlowEdge edge) {
    adj_list_[edge.from].push_back(edge);
    adj_list_[edge.to].push_back(edge);
  }
  const Vertex& adj(int v) const {
    return adj_list_[v];
  }

  Vertex& adj(int v) {
    return adj_list_[v];
  }

  int V() const {
    return V_;
  }
private:
  int V_;
  std::vector<Vertex> adj_list_;
};

#endif // FLOW_GRAPH_H
