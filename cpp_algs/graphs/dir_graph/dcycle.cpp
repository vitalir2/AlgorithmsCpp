#include <optional>
#include <vector>
#include <queue>

#include "digraph.h"

class DiCycle {
public:
  DiCycle(const Digraph& digraph) : digraph_(digraph) {
    marked_.resize(digraph.V(), 0);
    edge_to_.resize(digraph_.V());
  }
  ~DiCycle() = default;

  bool isCyclic() {
    if (is_acyclic_.has_value()) {
      return is_acyclic_.value();
    }
    int random_v = 0;
    std::queue<int> bfs_queue;
    marked_[random_v] = 1;
    bfs_queue.push(random_v);
    while (!bfs_queue.empty()) {
      int v = bfs_queue.front();
      bfs_queue.pop();
      for (int vertex: digraph_.adj(v)) {
        if (!marked_[vertex]) {
          marked_[vertex] = 1;
          edge_to_[vertex] = v;
          bfs_queue.push(vertex);
        } else {
          is_acyclic_ = false;
          return is_acyclic_.value();
        }
      }
    }

    is_acyclic_ = true;
    return is_acyclic_.value();
  }
private:
  Digraph digraph_;
  std::optional<bool> is_acyclic_;

  std::vector<int> marked_;
  std::vector<int> edge_to_;
};
