#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

constexpr size_t alphabet_size = 128; // ASCII

std::vector<int> constructShiftArray(const std::string& pattern) {
  std::vector<int> result(alphabet_size, -1);
  for (size_t i = 0; i < pattern.size(); ++i) {
    result[pattern[i]] = i;
  }
  return result;
}

size_t search(const std::string& str, const std::string& pattern) {
  const size_t not_found = str.size();
  std::vector<int> shifts = constructShiftArray(pattern);

  size_t shift = 0;
  for (size_t i = 0; i < str.size() - pattern.size(); i += shift) {
    shift = 0;
    for (int j = pattern.size() - 1; j >= 0; --j) {
      if (str[i + j] != pattern[j]) {
        shift = std::max(1, j - shifts[pattern[j]]);
        break;
      }
    }
    if (shift == 0) {
      return i;
    }
  }
  return not_found;
}

int main() {
  std::string str;
  std::string pattern;
  std::cout << "Enter string and pattern which need to be found\n";
  std::cin >> str >> pattern;
  size_t index_pattern = search(str, pattern);
  if (index_pattern == str.size()) {
    std::cout << "Pattern wasn't found in string\n";
  } else {
    std::cout << "First character from pattern has index = " << index_pattern
      << '\n';
  }
  return 0;
}
