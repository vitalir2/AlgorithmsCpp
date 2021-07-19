/*=============================================================================
   Copyright (C) 2021 Khvostov Vitaly. All rights reserved.
   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/

#include <algorithm>
#include <iostream>
#include <vector>

// Works in O(n^2) for the sorted vector; also counts duplicates (like -1, -1);
size_t countZeroSumsThreeElems(const std::vector<int>& v) {
  size_t count = 0;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    auto left_boundary = it + 1;
    auto right_boundary = v.cend() - 1;
    for (; left_boundary < right_boundary;) {
      int sum = *it + *left_boundary + *right_boundary;
      if (sum == 0) {
        while (left_boundary < right_boundary && *(left_boundary + 1) == *left_boundary) {
          ++left_boundary;
          ++count;
        }
        while (left_boundary < right_boundary && *(right_boundary - 1) == *right_boundary) {
          --right_boundary;
          ++count;
        }
        ++left_boundary;
        --right_boundary;
        ++count;
      } else if (sum < 0) {
        ++left_boundary;
      } else {
        --right_boundary;
      }
    }
  }
  return count;
}

int main() {
  std::vector<int> sample;
  for (int input; std::cin >> input;) {
    sample.push_back(input);
  }
  std::sort(sample.begin(), sample.end());
  size_t result = countZeroSumsThreeElems(sample);
  std::cout << "Count of zero sums of 3 elements = " << result << '\n';
  return 0;
}
