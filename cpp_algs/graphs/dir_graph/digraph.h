#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <iostream>
#include <vector>

class Digraph {
public:
  using Vertex = std::vector<int>;
  Digraph(size_t V); 
  void addEdge(int v, int q);
  Vertex adj(int v) const;

  inline size_t V() const noexcept {
    return V_;
  }

  inline size_t E() const noexcept{
    return E_;
  }

private:
  size_t V_;
  size_t E_;
  std::vector<Vertex> adj_list_;
};

#endif // DIGRAPH_H
