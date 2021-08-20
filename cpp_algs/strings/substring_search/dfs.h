#ifndef DFS_H
#define DFS_H

// Depth-First Search

#include <iostream>
#include <vector>

#include "digraph.h"

class Dfs {
public:
  Dfs(const Digraph& graph);
  ~Dfs() = default;

  void dfs(int source);
  void dfs(const std::vector<int>& sources);
  bool hasPath(int p, int q);
  bool marked(int v) const;
private:
  Digraph graph_;
  int source_;

  using Color = std::string;
  const Color WHITE = "white";
  const Color GREY = "grey";
  const Color BLACK = "black";

  std::vector<Color> colors;
  std::vector<int> distances;
  std::vector<int> cc;

  void dfsRecursive(int v, int count);
  
};

#endif // DFS_H
