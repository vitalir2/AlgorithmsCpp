#ifndef WEIGHTED_DIGRAPH_H
#define WEIGHTED_DIGRAPH_H

#include <set>
#include <vector>
#include <optional>

class WeightedDigraph {
public:
  class Edge {
    int v;
    int w;
    double weight_;
  public:
    Edge() {
    }
    Edge(int from, int to, double weight) : v(from), w(to), weight_(weight) {
    }
    int from() const {
      return v;
    }
    int to() const {
      return w;
    }
    double weight() const {
      return weight_;
    }
    friend bool operator<(const Edge& lhs, const Edge& rhs);
    friend bool operator>(const Edge& lhs, const Edge& rhs);
  };

  WeightedDigraph(int V);
  ~WeightedDigraph() = default;
  // TODO: Make deep copy constructor

  void addEdge(const Edge& edge);
  std::vector<Edge> adj(int v) const;
  std::set<Edge> edges() const;

  int V() const noexcept;
  const std::vector<std::vector<Edge>>& adj_list() const noexcept;
private:
  std::vector<std::vector<Edge>> adj_list_;
  int V_;
};

#endif // WEIGHTED_DIGRAPH_H
