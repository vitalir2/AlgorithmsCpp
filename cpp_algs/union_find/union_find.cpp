#include <iostream>
#include <numeric>

#include "union_find.h"

UnionFind::UnionFind(size_t count) : count_(count), id_(count), size_(count_) {
  std::iota(id_.begin(), id_.end(), 0);
  std::fill(size_.begin(), size_.end(), 1);
}

size_t UnionFind::find(size_t p) {
  if (p == id_[p]) {
    return p;
  } else {
    return id_[p] = find(id_[p]);
  }
}

bool UnionFind::connected(size_t p, size_t q) {
  return find(p) == find(q);
}

// 7 <- 9
void UnionFind::unionF(size_t p, size_t q) {
  size_t i = find(p);
  size_t j = find(q);
  if (i == j) {
    return;
  }
//  std::cerr << "I = " << i << ", J = " << j << std::endl;
  if (size_[i] < size_[j]) {
    id_[i] = j;
    size_[j] += size_[i];
  } else {
    id_[j] = i;
    size_[i] += size_[j];
  }
  --count_;
}
