#include <algorithm>
#include <iostream>
#include <vector>

// Bitonic: 2 4 7 12 8 3 1;

template<typename C, typename T>
int binary_search(int left, int right, const C& container, const T& value) {
  int mid = (left + right) / 2;
  while (left < right) {
    if (container[mid] < value) {
      left = mid + 1;
    } else if (container[mid] > value) {
      right = mid - 1;
    } else {
      return mid;
    }
    mid = (left + right) / 2;
  }
  return -1;
}

template<typename C, typename T>
int binary_search_reversed(int left, int right, const C& container, const T& value) {
  int mid = (left + right) / 2;
  while (left < right) {
    if (container[mid] > value) {
      left = mid + 1;
    } else if (container[mid] < value) {
      right = mid - 1;
    } else {
      return mid;
    }
    mid = (left + right) / 2;
  }
  return -1;
}

// 2log(n) - ?
template<typename C, typename T>
int binary_search_bitonic(int peak, const C& container, const T& value) {
  // [begin, peak], [peak, end]; a1 <= a2 <= ... <= ak >= a_k+1 >= ... >= an
  return -1;
}

// Time complexity: 3log(n) (3 times binary search, different ways though)
template<typename T>
bool search_bitonic(const std::vector<int>& bit_v, const T& value) {
  int left = 0;
  int right = bit_v.size() - 1;
  int peak = (left + right) / 2;

  // find peak
  while (bit_v[peak] < bit_v[peak-1] || bit_v[peak] < bit_v[peak+1]) {
    if (bit_v[peak] > bit_v[peak-1]) {
      left = peak;
    } else if (bit_v[peak] > bit_v[peak+1]) {
      right = peak;
    }
    peak = (left + right) / 2;
  }

  // binary search for increasing and decreasing sides
  int first_part = binary_search(0, peak, bit_v, value);
  int second_part = binary_search_reversed(peak, bit_v.size() - 1, bit_v, value);
  if (first_part != -1 || second_part != -1) {
    return true;
  } else {
    return false;
  }
};

int main() {
  std::vector<int> v;
  for (int input; std::cin >> input; ) {
    v.push_back(input);
  }
  int search_value = 2;
  std::cout << "Try to find " << search_value << '\n';
  std::cout << (search_bitonic(v, search_value) ? "Found\n" : "Not found\n");
  return 0;
}
