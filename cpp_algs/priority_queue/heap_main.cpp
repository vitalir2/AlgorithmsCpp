#include <iostream>
#include <functional>
#include <random>

#include "general_heap.h"

int main() {
  MinHeap<int,std::greater<int>> heap;
  constexpr int n = 15;
  for (int i = 0; i < n; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, n*4);
    heap.insert(dist(gen));
  }
  heap.print();
  std::cout << std::endl;

  for (int i = 0; i < n; ++i) {
    std::cout << heap.min() << " ";
    heap.deleteMin();
  }

  std::cout << std::endl;
  return 0;
}
