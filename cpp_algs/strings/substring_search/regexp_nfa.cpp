#include <unordered_set>
#include <stack>
#include <string>
#include <vector>

#include "digraph.h"
#include "dfs.h"

// Nondetermenistic Finite Automata
class NFA {
public:
  NFA(const std::string& pattern) : regexp_(pattern),
    regexp_length_(pattern.size()),
    graph_(buildEpsTransitionDigraph()) {
  }

  bool appearsIn(const std::string& str) {
    std::vector<size_t> reachable;
    Dfs dfs(graph_);
    dfs.dfs(0);
    for (size_t v = 0; v < graph_.V(); ++v) {
      if (dfs.marked(v)) {
        reachable.push_back(v);
      }
    }

    for (size_t i = 0; i < str.size(); ++i) {
      std::unordered_set<size_t> match;
      for (size_t v: reachable) {
        if (v != regexp_length_
            && (regexp_[v] == str[i] || regexp_[v] == '.')) {
          match.insert(v + 1);
        }
      }

      dfs.clearDfs();
      dfs.dfs(match);
      reachable.clear();
      for (size_t v = 0; v < graph_.V(); ++v) {
        if (dfs.marked(v)) {
          reachable.push_back(v);
        }
      }
    }

    for (size_t v: reachable) {
      if (v == regexp_length_) {
        return true;
      }
    }
    return false;
  }

private:
  std::string regexp_;
  size_t regexp_length_;
  Digraph graph_;

  bool contains(const std::vector<size_t>& v, size_t target) {
    for (size_t elem: v) {
      if (elem == target) {
        return true;
      }
    }
    return false;
  }

  Digraph buildEpsTransitionDigraph() {
    Digraph digraph(regexp_length_ + 1);
    std::stack<int> operators;
    for (size_t i = 0; i < regexp_length_; ++i) {
      size_t left_paranthesis = i;
      if (regexp_[i] == '(' || regexp_[i] == '|') {
        operators.push(i);
      } else if (regexp_[i] == ')') {
        size_t or_ = operators.top(); // or - bad word in cpp ;(
        operators.pop();
        if (regexp_[or_] == '|') {
          left_paranthesis = operators.top();
          operators.pop();
          digraph.addEdge(left_paranthesis, or_ + 1);
          digraph.addEdge(or_, i);
        } else {
          left_paranthesis = or_; 
        }
      }

      if (i < regexp_length_ - 1 && regexp_[i + 1] == '*') {
        digraph.addEdge(i, i + 1);
        digraph.addEdge(i + 1, i);
      }

      if (regexp_[i] == '(' || regexp_[i] == '*' || regexp_[i] == ')') {
          digraph.addEdge(i, i + 1);
      }
    }
    return digraph;
  }
};
