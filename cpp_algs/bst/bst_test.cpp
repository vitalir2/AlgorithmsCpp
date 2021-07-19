#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "bst.h"

bool height_comp(const std::string& lhs, const std::string& rhs) {
  std::string_view sv1(lhs);
  std::string_view sv2(rhs);
  sv1.remove_prefix(sv1.find('=')+1);
  sv2.remove_prefix(sv2.find('=')+1);
  sv1.remove_suffix(sv1.rfind(' '));
  sv2.remove_suffix(sv2.rfind(' '));
  int h1 = std::stoi(std::string(sv1));
  int h2 = std::stoi(std::string(sv2));
  return h1 < h2;
}

int main() {
  BST<int, double> dic;
  /*
  dic.insert(5, 4.5);
  dic.insert(4, 5.1);
  dic.insert(1, 2.1);
  dic.print(std::cout);
  std::cout << std::endl;
  std::cout << dic.minKey() << std::endl;

  dic.deleteElem(1);
  dic.print(std::cout);
  */
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 50);
  for (int i = 0; i < 10; ++i) {
    int rdv = dist(gen);
    dic.insert(rdv, static_cast<double>(rdv));
  }
  dic.insert(25, 25);
  dic.print(std::cout);
  std::cout << std::endl;

//  dic.deleteElem(25);

 // dic.print(std::cout);
 // std::cout << std::endl;

  std::stringstream sstream;
  dic.printDebug(sstream);
  std::vector<std::string> debug_lines;
  for (std::string line; std::getline(sstream, line);) {
    debug_lines.push_back(line);
  }
  std::sort(debug_lines.begin(), debug_lines.end(), height_comp);
  std::cout << dic.size() << std::endl;
  for (const std::string& line: debug_lines) {
    std::cout << line << std::endl;
  }

  /*
  for (auto x: dic) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  */
  return 0;
}
