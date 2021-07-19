#include <algorithm>
#include <iostream>
#include <vector>

#include "permutations/container_out.h"
#include "utils/utils.h"

using utils::TimeCounter;

// write contatiners extensions
int main() {
  /*
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (int& elem: v) {
    std::cin >> elem;
  }
  */

  constexpr int n = 100'000;
  std::vector<int> v(n);

  utils::generateRandomVector(v, n/2);
  for (int i = 0; i < n; ++i) {
    v[i] = i % 2 == 0 ? v[i] : -v[i];
  }

  std::sort(v.begin(), v.end());

  int count1 = 0;
  int count2 = 0;

  // Sums O(n)
  {
  TimeCounter tc;
  int l = 0;
  int r = n-1;
  while(l < r) {
    if (v[l] + v[r] < 0) {
      ++l;
    } else if (v[l] + v[r] > 0) {
      --r;
    } else {
      ++l;
      ++count1;
    }
  }
  }
  {
    // O(n log(n))
    TimeCounter tc;
    for (int i = 0; i < n; ++i) {
      if (std::binary_search(v.begin() + i, v.end(), -v[i])) {
        ++count2;
      }
    }
  }

//  std::cout << sums0 << '\n';
  std::cout << count1 << std::endl;
  std::cout << count2 << std::endl;

  return 0;
}
