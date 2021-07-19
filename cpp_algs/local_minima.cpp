#include <algorithm>
#include <iostream>
#include <vector>

#include "utils/utils.h"
#include "utils/container_out.h"

// O(2log n)
int localMin(const std::vector<int>& a) {
  size_t l = 0;
  size_t r = a.size()-1;
  while (l < r) {
    int mid = (l + r) / 2;
    int left_n = std::max(mid-1, 0);
    int right_n = std::min(mid+1, static_cast<int>(a.size() - 1));
    if ((a[left_n] > a[mid] || left_n == mid)
        && (a[mid] < a[right_n] || mid == right_n)) {
      return mid;
    } else {
      int min = std::min(a[left_n], a[right_n]);
      if (min == a[left_n]) {
        r = mid;
      } else {
        l = mid;
      }
    }
  }
  return -1; // no local min
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<int> a(n);

  utils::generateRandomVector(a, n);
  utils::uniqueAndShuffle(a);

  int min_id = localMin(a);
  if (min_id != -1) {
    std::cout << a[min_id] << " is local minima of the array\n";
  } else {
    std::cout << "There is no local minima in the array\n";
  }

  return 0;
}
