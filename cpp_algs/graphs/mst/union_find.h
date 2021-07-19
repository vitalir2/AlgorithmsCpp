#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <cstddef>
#include <vector>

class UnionFind {
public:
  UnionFind(size_t count);
  inline size_t count() const noexcept {
    return count_;
  }
  size_t find(size_t p);
  void unionF(size_t p, size_t q);
  bool connected(size_t p, size_t q);
private:
  size_t count_;
  std::vector<size_t> id_;
  std::vector<size_t> size_;
};

#endif // UNION_FIND_H
