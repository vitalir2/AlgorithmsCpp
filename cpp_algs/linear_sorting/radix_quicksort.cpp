#include <iostream>
#include <string>
#include <vector>

int getChar(const std::string& str, size_t idx) {
  if (idx >= str.size() || idx < 0) {
    return -1;
  } else {
    return str[idx];
  }
}

struct RadixQuicksortPartitionResult {
  int less_than;
  int greater_than;
  int partition_char;
};

void radixQuickSortRec(std::vector<std::string>& arr, int lower_bound,
    int upper_bound, size_t d);
RadixQuicksortPartitionResult partition(std::vector<std::string>& arr, int lower_bound,
    int upper_bound, size_t d);
void callRecursiveRadixQuicksort(std::vector<std::string>& arr,
    int lower_bound, int upper_bound, int less_than, int greater_than,
    size_t d, int c);
void radixQuickSort(std::vector<std::string>& arr) {
  radixQuickSortRec(arr, 0, arr.size() - 1, 0);
}

void radixQuickSortRec(std::vector<std::string>& arr, int lower_bound,
    int upper_bound, size_t d) {
  if (upper_bound <= lower_bound) {
    return;
  }

  RadixQuicksortPartitionResult partition_result = partition(arr, lower_bound,
                                                             upper_bound, d);
  callRecursiveRadixQuicksort(arr, lower_bound, upper_bound, partition_result.less_than,
      partition_result.greater_than, d, partition_result.partition_char);
}

RadixQuicksortPartitionResult partition(std::vector<std::string>& arr, int lower_bound,
    int upper_bound, size_t d) {
  int less_than = lower_bound;
  int greater_than = upper_bound;
  int c = getChar(arr[lower_bound], d);
  int i = lower_bound + 1;
  while (i <= greater_than) {
    int t = getChar(arr[i], d);
    if (t < c) {
      std::swap(arr[less_than++], arr[i++]);
    } else if (t > c) {
      std::swap(arr[greater_than--], arr[i]);
    } else {
      ++i;
    }
  }
  return {less_than, greater_than, c};
}

void callRecursiveRadixQuicksort(std::vector<std::string>& arr,
    int lower_bound, int upper_bound, int less_than, int greater_than,
    size_t d, int c) {

  radixQuickSortRec(arr, lower_bound, less_than - 1, d);
  if (c >= 0) {
    radixQuickSortRec(arr, less_than, greater_than, d + 1);
  }
  radixQuickSortRec(arr, greater_than + 1, upper_bound, d);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& rhs) {
  for (const T& elem: rhs) {
    std::cout << elem << " ";
  }
  return stream;
}

void testRadixQuicksort() {
  int n = 0;
  std::cout << "Enter size of an array\n";
  std::cin >> n;
  std::vector<std::string> arr(n);
  std::cout << "Enter all elements of an array\n";
  for (std::string& elem: arr) {
    std::cin >> elem;
  }

  std::cout << "Array before radix quicksort\n" << arr << '\n';
  radixQuickSort(arr);
  std::cout << "Array after radix quicksort\n" << arr << '\n';
}

int main() {
  testRadixQuicksort();
  return 0;
}
