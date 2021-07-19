#include <algorithm>
#include <iostream>
#include <vector>

#include "utils/utils.h"
#include "utils/container_out.h"

// O(log n)
// Maybe here i + fib_k_2 > n - 1 => make min(n-1, i + fib_k_2) = x)
template <typename T>
bool binary_search_fib(const std::vector<T>& v, const T& value) {
  int fib_k_2 = 0;
  int fib_k_1 = 1;
  int fib_k = 1;

  while (fib_k < static_cast<int>(v.size())) {
    fib_k_2 = fib_k_1;
    fib_k_1 = fib_k;
    fib_k = fib_k_1 + fib_k_2;
  }
  // 0 1 1 2 3 5

  int i = 0;

  while (fib_k >= 1) {
    fib_k_2 = fib_k - fib_k_1;
    if (v[i+fib_k_2] > value) {
      //
    } else if (v[i+fib_k_2] < value) {
      i = fib_k_2;
    } else {
      return true;
    }
    fib_k = fib_k_1;
    fib_k_1 = fib_k_2;
  }
  return false;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);

  utils::generateRandomVector(a, n);
  std::sort(a.begin(), a.end());

  int value = n / 2;
  bool result = binary_search_fib(a, value);

  if (result) {
    std::cout << value << " was found in the array\n";
  } else {
    std::cout << value << " wasn't found in the array\n";
  }

  return 0;
}
