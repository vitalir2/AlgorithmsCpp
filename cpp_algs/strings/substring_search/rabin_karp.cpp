#include <iostream>
#include <string>
#include <vector>

constexpr size_t alphabet_size = 128;
constexpr size_t big_prime = 2'147'483'647;

size_t hash(const std::string& str, size_t digit) {
  size_t hash_result = 0;
  for (size_t i = 0; i < digit; ++i) {
    hash_result = (alphabet_size * hash_result + str[i]) % big_prime;
  }
  return hash_result;
}

bool check(const std::string& str, const std::string& pattern, size_t digit) {
  for (size_t i = 0; i < pattern.size(); ++i) {
    if (pattern[i] != str[i + digit]) {
      return false;
    }
  }
  return true;
}

// Rabin-Karp algorithm
size_t search(const std::string& str, const std::string& pattern) {
  size_t s_size = str.size();
  size_t p_size = pattern.size();
  size_t pattern_hash = hash(pattern, p_size); 
  size_t str_hash = hash(str, p_size); 

  if (pattern_hash == str_hash && check(str, pattern, 0)) {
    return 0;
  }

  size_t alphabet_size_pattern_power = 1;
  for (size_t i = 1; i <= pattern.size() - 1; ++i) {
    alphabet_size_pattern_power *= alphabet_size % big_prime;
  }

 for (size_t i = p_size; i < s_size; ++i) {
    str_hash = (str_hash + big_prime - alphabet_size_pattern_power * str[i - p_size] % big_prime)
      % big_prime;
    str_hash = (str_hash * alphabet_size + str[i]) % big_prime;
    size_t offset = i - p_size + 1;
    if (pattern_hash == str_hash && check(str, pattern, offset)) {
      return offset;
    }
  }
  return s_size;
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
