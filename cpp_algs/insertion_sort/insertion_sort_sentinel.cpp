#include <iostream>
#include <vector>

#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/utils.h"
#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/container_out.h"

template<typename T>
void insertionSortSent(std::vector<T>& v) {
  size_t n = v.size();

  for (size_t i = 0; i < n; ++i) {
    if (i == 0) {
      int min_idx = 0;
      for (size_t x = 1; x < n; ++x) {
        if (v[x] < v[min_idx]) {
          min_idx = x;
        }
      }
      std::swap(v[0], v[min_idx]);
    } else {
      for (size_t j = i; v[j-1] > v[j]; --j) {
        std::swap(v[j-1], v[j]);
      }
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);

  utils::generateRandomVector(a, n);
  std::cout << a << std::endl;

  insertionSortSent(a);
  std::cout << a << std::endl;

  return 0;
}
