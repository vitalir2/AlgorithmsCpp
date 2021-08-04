#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

constexpr size_t ascii_size = 128;

// MSD sort - sort from right to left,
// by partitioning and recursion (like quick sort)

int getChar(const std::string& str, size_t idx) {
  if (idx >= str.size() || idx < 0) {
    return -1;
  } else {
    return str[idx];
  }
}

// Basis for msd sort
void msdRec(std::vector<std::string>& arr, std::vector<std::string>& aux,
    int low_bound, int up_bound, size_t d);
void countSort(std::vector<std::string>& arr, std::vector<std::string>& aux,
    int low_bound, int up_bound, size_t d, size_t R);

void msd(std::vector<std::string>& arr) {
  std::vector<std::string> aux(arr.size());
  msdRec(arr, aux, 0, arr.size() - 1, 0);
}

void msdRec(std::vector<std::string>& arr, std::vector<std::string>& aux,
    int low_bound, int up_bound, size_t d) {
  if (up_bound <= low_bound) {
    return;
  }
  countSort(arr, aux, low_bound, up_bound, d, ascii_size);
}

void countSort(std::vector<std::string>& arr, std::vector<std::string>& aux,
    int low_bound, int up_bound, size_t d, size_t R) {
  std::vector<int> count(R + 2);
  for (int i = low_bound; i <= up_bound; ++i) {
    int index = getChar(arr[i], d);
    ++count[index + 2];
  }

  for (size_t i = 1; i < count.size() - 1; ++i) {
    count[i] += count[i-1];
  }

  for (int i = low_bound; i <= up_bound; ++i) {
    int index = getChar(arr[i], d);
    aux[count[index + 1]++] = arr[i];
  }

  for (int i = low_bound; i <= up_bound; ++i) {
    arr[i] = aux[i - low_bound];
  }

  for (size_t r = 0; r < R; ++r) {
    msdRec(arr, aux, low_bound + count[r], low_bound + count[r + 1] - 1, d + 1);
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& rhs) {
  for (const T& elem: rhs) {
    std::cout << elem << " ";
  }
  return stream;
}

void testMsd() {
  int n = 0;
  std::cout << "Enter size of an array\n";
  std::cin >> n;
  std::vector<std::string> arr(n);
  std::cout << "Enter all elements of an array\n";
  for (std::string& elem: arr) {
    std::cin >> elem;
  }

  std::cout << "Array before MSD sort\n" << arr << '\n';
  msd(arr);
  std::cout << "Array after MSD sort\n" << arr << '\n';
}

int main() {
  testMsd();
  return 0;
}
