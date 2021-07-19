#include <iostream>
#include <random>

#include "indexed_queue.h"
int main() {
  IndexQueue<int> pq(10);
  for (int i = 0; i < 10; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    int rand = dist(gen);
    std::cout << "RAND " << i << " : " << rand << std::endl;
    pq.insert(i, rand);
  }
  for (int i = 0; i < 5; ++i) {
    std::cout << pq.min() << std::endl;
    pq.delMin();
  }
  return 0;
}
