#include <forward_list>
#include <iostream>
#include <random>

#include "utils/container_out.h"

// slow version? O(n^2)
void shuffleListSlow(std::forward_list<int>& l) {
  int i = 0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist;
  for (int& elem: l) { // n times
    int x = 0;
    auto it = l.begin();
    dist = std::uniform_int_distribution<int>(0, i++);
    int rand = dist(gen);

    while (x++ != rand && it++ != l.end()); // n times
    std::swap(elem, *it);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::forward_list<int> l(n);

  auto it = l.begin();
  for (int i = 0; i < n; ++i) {
    *it++ = i;
  }

//  std::cout << l << std::endl;

  shuffleListSlow(l);

//  std::cout << l << std::endl;

  return 0;
}
