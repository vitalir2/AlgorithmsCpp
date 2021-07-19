#include <iostream>
#include <random>

#include "union_find.h"

int main() {
  int n;
  std::cin >> n;
  UnionFind uf(n);
  for (int i = 0; i < n / 2; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, n-1);
    int x1 = dist(gen);
    int x2 = dist(gen);
    std::cerr << "I in for: " << x1 << ", J in for: " << x2 << std::endl;
    uf.unionF(x1, x2);
  }
  while (true) {
    int p, q;
    std::cin >> p >> q;
    std::cout << "Node p = " << p << " and node q = " << q
      << " are " << (uf.connected(p, q) ? "connected\n" : "disconnected\n");
  }
  return 0;
}
