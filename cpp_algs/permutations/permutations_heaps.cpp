#include <iostream>
#include <vector>

#include "container_out.h"

void perm_heap(size_t k, std::vector<int>& v){
  if (k == 1) {
    std::cout << v << '\n';
  } else {
    perm_heap(k - 1, v);
    for (size_t i = 0; i < k - 1; ++i) {
      if (k % 2 == 0) {
        std::swap(v[i], v[k-1]);
      } else {
        std::swap(v[0], v[k-1]);
      }
      perm_heap(k - 1, v);
    }
  }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  perm_heap(v.size(), v);
  return 0;
}
