#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/container_out.h"
#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/utils.h"

template<typename T>
void quickSort(std::vector<T>& v, int lo, int hi);
template<typename T>
int partition(std::vector<T>& v, int lo, int hi);

template<typename T>
void quickSort(std::vector<T>& v) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::shuffle(v.begin(), v.end(), gen);
  quickSort(v, 0, v.size() - 1);
}

template<typename T>
void quickSort(std::vector<T>& v, int lo, int hi) {
  if (lo < hi) {
    int p = partition(v, lo, hi);
    quickSort(v, lo, p-1);
    quickSort(v, p+1, hi);
  }
}

template<typename T>
int partition(std::vector<T>& v, int lo, int hi) {
  int i = lo;
  int j = hi + 1;
  while (true) {
    while (v[++i] < v[lo]) {
      if (i == hi) {
        break;
      }
    }
    while (v[lo] < v[--j]) {
      if (j == lo) {
        break;
      }
    }
    if (i >= j) {
      break;
    }
    std::swap(v[i], v[j]);
  }
  std::swap(v[lo], v[j]);
  return j;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);

  utils::generateRandomVector(a, n);

//  std::cout << a << std::endl;
  quickSort(a);
//  std::cout << a << std::endl;
  return 0;
}
