#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename T>
void countSort(std::vector<T>& arr, const std::map<T, int>& symbols) {
  std::vector<int> count(symbols.size() + 1);
  for (const T& elem: arr) {
    ++count[symbols.at(elem) + 1];
  }

  for (size_t i = 1; i < count.size(); ++i) {
    count[i] += count[i-1];
  }

  std::vector<T> sub(arr.size());
  for (size_t i = 0; i < arr.size(); ++i) {
    sub[count[symbols.at(arr[i])]++] = arr[i];
  }

  std::copy(sub.begin(), sub.end(), arr.begin());
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& rhs) {
  for (const T& elem: rhs) {
    std::cout << elem << " ";
  }
  return stream;
}

// a bad way to test different types of data
template<typename T>
void testCountSort(const T& type) {
  int dic_size = 0;
  std::map<T, int> dic;
  std::cout << "Enter number of possible elements in the array\n";
  std::cin >> dic_size;
  std::cout << "Enter all possible elements in the array\n";
  for (int i = 0; i < dic_size; ++i) {
    T element;
    std::cin >> element;
    dic[element] = i;
  }

  int n = 0;
  std::cout << "Enter size of an array\n";
  std::cin >> n;
  std::vector<T> arr(n);
  std::cout << "Enter all elements of an array\n";
  for (T& elem: arr) {
    std::cin >> elem;
  }

  std::cout << "Array before count sort\n" << arr << '\n';
  countSort(arr, dic);
  std::cout << "Array after count sort\n" << arr << '\n';
}

int main() {
  std::string str = "";
  // if put here a string literal -> gives an error!!
  testCountSort(str);
  return 0;
}
