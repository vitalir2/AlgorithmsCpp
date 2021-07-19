#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<double> a(n);

  for (double& elem: a) {
    std::cin >> elem;
  }

  auto first_id = std::min_element(a.begin(), a.end());
  auto second_id = std::max_element(a.begin(), a.end());
  std::cout << "The biggest difference in the array = "
    << *second_id - *first_id << '\n';
  return 0;
}
