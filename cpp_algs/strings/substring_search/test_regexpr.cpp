#include <iostream>
#include <string>

#include "regexp_nfa.cpp"
int main() {
  std::string pattern;
  std::cout << "Enter pattern to find in the next string\n";
  std::cin >> pattern;
  pattern = '(' + pattern + ')'; // for working
  NFA regexp(pattern);
  std::string str;
  std::cout << "Enter string\n";
  std::cin >> str;
  bool found = regexp.appearsIn(str);
  if (found) {
    std::cout << "Pattern was matched\n";
  } else {
    std::cout << "Pattern wasn't matched\n";
  }
  return 0;
}
