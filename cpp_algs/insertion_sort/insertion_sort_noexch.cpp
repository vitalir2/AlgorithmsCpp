#include <iostream>
#include <vector>

#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/utils.h"
#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/container_out.h"

template<typename T>
void insertionSortNoExch(std::vector<T>& v) {
  size_t n = v.size();
  /*
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j > 0 && v[j-1] > v[j]; --j) {
      std::swap(v[j-1], v[j]);
    }
  }
  */
  // 2 2 4 1
  for (size_t i = 1; i < n; ++i) {
    T cur = v[i];
    size_t j = i;
    for (; j > 0 && cur < v[j-1]; --j) {
      v[j] = v[j-1];
    }
    v[j] = cur;
  }
} // a[i+1] = a[i];

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  utils::generateRandomVector(a, n);

  std::cout << a << std::endl;
  insertionSortNoExch(a);
  std::cout << a << std::endl;

  return 0;
}
