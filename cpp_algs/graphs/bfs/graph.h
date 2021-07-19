#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <optional>

class Graph {
public:
  using Vertex = std::vector<int>;

  Graph();
  Graph(int V);
  ~Graph() = default;

  void addEdge(int p, int q);
  void deleteEdge(int p, int q);
  Vertex adj(int v) const;

  int V() const noexcept;
  const std::vector<Vertex>& adj_list() const noexcept;
  int degree(int v) const noexcept;
  
  bool isEulerCycle() const noexcept;
private:
  // for simplicity using only int
  std::vector<Vertex> adj_list_;
  int V_;

  std::optional<bool> is_euler_;
};

#endif // GRAPH_H
