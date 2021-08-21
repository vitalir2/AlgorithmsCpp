#ifndef DFS_H
#define DFS_H

// Depth-First Search

#include <iostream>
#include <unordered_set>
#include <vector>

#include "digraph.h"

class Dfs {
public:
  Dfs(const Digraph& graph);
  ~Dfs() = default;

  void dfs(int source);
  void dfs(const std::unordered_set<size_t>& sources);
  bool marked(int v) const;

  void clearDfs();
private:
  Digraph graph_;
  std::unordered_set<size_t> sources_;

  std::vector<bool> marked_;

  void dfsRecursive(int v);
  
};

#endif // DFS_H
