#include <iostream>
#include <vector>

#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/utils.h"
#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/container_out.h"

template<typename T>
void insertionSort(std::vector<T>& v) {
  size_t n = v.size();
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j > 0 && v[j-1] > v[j]; --j) {
      std::swap(v[j-1], v[j]);
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  utils::generateRandomVector(a, n);

  std::cout << a << std::endl;
  insertionSort(a);
  std::cout << a << std::endl;

  return 0;
}
