#include <iostream>
#include <string>

#include "rway_trie.cpp"

RWayTrie<int> testInsert() {
  constexpr int ascii_size = 128;
  RWayTrie<int> trie(ascii_size);
  std::cout << "Enter 5 strings\n";
  for (int i = 0; i < 5; ++i) {
    std::string str;
    std::cin >> str;
    trie.insert(str, i);
  }
  return trie;
}

void testAt(RWayTrie<int>& trie) {
  std::cout << "Enter 2 string to check their value in trie\n";
  std::string str1;
  std::string str2;
  std::cin >> str1 >> str2;
  std::cout << trie.at(str1).value() << std::endl;
  std::cout << trie.at(str2).value() << std::endl;
}
int main() {
  RWayTrie<int> trie = testInsert();
  testAt(trie);
  return 0;
}
