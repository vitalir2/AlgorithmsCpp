#ifndef DIJKSTRA_SP_H
#define DIJKSTRA_SP_H

#include <iostream>
#include <vector>
#include <stack>

#include "indexed_queue.h"
#include "weighted_digraph.h"

class DijkstraSP {
using Edge = WeightedDigraph::Edge;

public:
  DijkstraSP(const WeightedDigraph& graph, int source);
  std::stack<Edge> pathTo(int v);
  double distTo(int v);
private:
  void relax(const Edge& edge);
  void relaxAdj(int v);

  WeightedDigraph graph_;
  IndexQueue<double> pq;
  std::vector<Edge> edge_to_;
  std::vector<double> dist_to_;
  // maybe do std::array instead of vector???
};

#endif // DIJKSTRA_SP_H
