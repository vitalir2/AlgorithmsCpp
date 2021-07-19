#include <cmath>
#include <iostream>
#include <vector>

#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/utils.h"
#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/container_out.h"

std::vector<int> generateSequenceSedgewick(int upper_bound) {
  std::vector<int> seq;
  int cur = 1;
  for (int k = 1; cur < upper_bound; ++k) {
    seq.push_back(cur);
    cur = std::pow(4, k) + 3 * pow(2, k-1) + 1;
  }
  return seq;
}

template<typename T>
void shellSort(std::vector<T>& v) {
  std::vector<int> seq = generateSequenceSedgewick(v.size());

  for (auto it = seq.rbegin(); it != seq.rend(); ++it) {
    // insertion sort for every gap seq until *it = 1 => final sorting
    for (size_t i = *it; i < v.size(); ++i) {
      T tmp = v[i];
      int j = i;
      for (; j >= *it && v[j - *it] > tmp; j -= *it) {
        v[j] = v[j-*it];
      }
      v[j] = tmp;
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);

  utils::generateRandomVector(a, n);

//  std::cout << a << std::endl;
  shellSort(a);
//  std::cout << a << std::endl;

  return 0;
}
