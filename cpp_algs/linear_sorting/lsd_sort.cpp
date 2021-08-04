#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>


// LSD sort - count sort on every digit from right to left
// Sort using ASCII characters (char type)

int getChar(const std::string& str, size_t idx) {
  if (idx >= str.size() || idx < 0) {
    return -1;
  } else {
    return str[idx];
  }
}

int getAppropriateIndex(const std::string& str, size_t pos, size_t max_size) {
  return pos - max_size + str.size();
}

// Basis for lsd sort
void countSort(std::vector<std::string>& arr, std::vector<std::string>& aux,
    size_t d, size_t max_size) {
  constexpr int ascii_size = 128;
  std::vector<int> count(ascii_size + 2);
  for (const std::string& str: arr) {
    int index = getChar(str, getAppropriateIndex(str, d, max_size));
    ++count[index + 2];
  }

  for (size_t i = 1; i < count.size(); ++i) {
    count[i] += count[i-1];
  }

  for (size_t i = 0; i < arr.size(); ++i) {
    int index = getChar(arr[i], getAppropriateIndex(arr[i], d, max_size));
    aux[count[index + 1]++] = arr[i];
  }

  std::copy(aux.begin(), aux.end(), arr.begin());
}

void lsd(std::vector<std::string>& arr) {
  std::vector<std::string> aux(arr.size());
  auto length_compare = [](const std::string& lhs, const std::string& rhs)
  { return lhs.size() < rhs.size(); };
  size_t max_size = std::max_element(arr.begin(), arr.end(), length_compare)->size();
  for (int d = max_size - 1; d >= 0; --d) {
    countSort(arr, aux, d, max_size);
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& rhs) {
  for (const T& elem: rhs) {
    std::cout << elem << " ";
  }
  return stream;
}

void testLsd() {
  int n = 0;
  std::cout << "Enter size of an array\n";
  std::cin >> n;
  std::vector<std::string> arr(n);
  std::cout << "Enter all elements of an array\n";
  for (std::string& elem: arr) {
    std::cin >> elem;
  }

  std::cout << "Array before LSD sort\n" << arr << '\n';
  lsd(arr);
  std::cout << "Array after LSD sort\n" << arr << '\n';
}

int main() {
  testLsd();
  return 0;
}
