#include <iostream>
#include <string>
#include <vector>

constexpr size_t alphabet_size = 128;
using Table = std::vector<std::vector<size_t>>;
// DFA - deterministic finite automata
Table buildDFAfromPattern(const std::string& pattern) {
  Table dfa(alphabet_size, std::vector<size_t>(pattern.size()));
  dfa[pattern[0]][0] = 1;
  for (size_t state = 0, j = 1; j < pattern.size(); ++j) {
    for (size_t c = 0; c < alphabet_size; ++c) {
      dfa[c][j] = dfa[c][state];
    }
    dfa[pattern[j]][j] = j + 1;
    state = dfa[pattern[j]][state];
  }
  return dfa;
}

// Knuth-Morris-Pratt substring search (Internet for more details)
size_t KMP(const std::string& str, const std::string& pattern) {
  Table dfa = buildDFAfromPattern(pattern);
  size_t i = 0;
  size_t j = 0;
  for (; i < str.size() && j < pattern.size(); ++i) {
    j = dfa[str[i]][j];
  }
  if (j == pattern.size()) {
    return i - j;
  } else {
    return str.size();
  }
}


int main() {
  std::string str;
  std::string pattern;
  std::cout << "Enter string and pattern which need to be found\n";
  std::cin >> str >> pattern;
  size_t index_pattern = KMP(str, pattern);
  if (index_pattern == str.size()) {
    std::cout << "Pattern wasn't found in string\n";
  } else {
    std::cout << "First character from pattern has index = " << index_pattern
      << '\n';
  }
  return 0;
}
