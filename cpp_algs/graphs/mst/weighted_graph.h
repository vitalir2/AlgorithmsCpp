#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <set>
#include <vector>
#include <optional>

class WeightedGraph {
public:
  struct Edge {
    int v;
    int w;
    double weight;

    friend bool operator<(const Edge& lhs, const Edge& rhs);
    friend bool operator>(const Edge& lhs, const Edge& rhs);
  };

  WeightedGraph(int V);
  ~WeightedGraph() = default;
  // TODO: Make deep copy constructor

  void addEdge(const Edge& edge);
  std::vector<Edge> adj(int v) const;
  std::set<Edge> edges() const;

  int V() const noexcept;
  const std::vector<std::vector<Edge>>& adj_list() const noexcept;
  int degree(int v) const noexcept;
private:
  // for simplicity using only int
  std::vector<std::vector<Edge>> adj_list_;
  int V_;
};

#endif // WEIGHTED_GRAPH_H
