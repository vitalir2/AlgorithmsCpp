#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "utils/utils.h"
#include "utils/container_out.h"

template<typename ForwardIt>
void mergeCounter(ForwardIt begin_first, ForwardIt end_first,
    ForwardIt begin_second, ForwardIt end_second, int& count);

template<typename ForwardIt>
void sortAndCount(ForwardIt begin, ForwardIt end, int& count) {
  if (std::distance(begin, end) == 1) {
    return;
  }

  int mid = std::distance(begin, end) / 2;
  sortAndCount(begin, begin + mid, count);
  sortAndCount(begin + mid, end, count);
  mergeCounter(begin, begin + mid, begin + mid, end, count);
}

// i < j but a[i] > a[j]
template<typename ForwardIt>
void mergeCounter(ForwardIt begin_first, ForwardIt end_first,
    ForwardIt begin_second, ForwardIt end_second, int& count) {
  auto it = begin_first;
  auto jt = begin_second;
  std::vector<int> tmp(std::distance(begin_first, end_second));
  auto tmp_it = tmp.begin();

  while (it != end_first && jt != end_second) {
    if (*it <= *jt) {
      *tmp_it++ = *it++;
    } else {
      *tmp_it++ = *jt++;
      ++count;
    }
  }

  while (it != end_first) {
    *tmp_it++ = *it++;
  }

  while (jt != end_second) {
    *tmp_it++ = *jt++;
  }

  std::move(tmp.begin(), tmp.end(), begin_first);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);

  utils::generateRandomVector(a, n);
//  std::cout << a << std::endl;

  int count = 0;
  sortAndCount(a.begin(), a.end(), count);

  std::cout << "The number of inversions = " << count << '\n';
//  std::cout << "Sorted array: " << a << '\n';
  return 0;
}
