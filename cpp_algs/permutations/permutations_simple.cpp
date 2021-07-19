#include <iostream>
#include <vector>

#include "container_out.h"

// O(n!)
void permutations(std::vector<int>& v, size_t left, size_t right) {
  if (left == right) {
//    std::cout << v << '\n';
    return;
  }
  for (size_t i = left; i <= right; ++i) {
    std::swap(v[left], v[i]);
    permutations(v, left+1, right);
    std::swap(v[left], v[i]);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  permutations(v, 0, v.size() - 1);
  return 0;
}
