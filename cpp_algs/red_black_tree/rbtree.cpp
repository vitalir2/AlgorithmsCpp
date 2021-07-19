#include <iostream>

#include "red_black_tree_left.h"

int main() {
  RedBlackST<int, int> tree;
  for (int i = 0; i < 10; ++i) {
    tree.insert(i, i+1);
  }
  tree.inorderPrint();
  std::cout << std::endl;

  std::cout << tree[2] << std::endl;

  return 0;
}
