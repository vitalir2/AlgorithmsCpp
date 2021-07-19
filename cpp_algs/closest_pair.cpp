#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#include "utils/utils.h"
#include "permutations/container_out.h"

int main() {
  /*
  int n;
  std::cin >> n;
  std::vector<double> a(n);
  for (double& elem: a) {
    std::cin >> elem;
  }
  */

  constexpr int n = 1'000'000;
  std::vector<double> a(n);
  utils::generateRandomVector(a, n*2);

  bool positive = true;
  for (double& elem: a) {
    elem = positive ? elem : -elem;
  }

  std::sort(a.begin(), a.end());

  int first_id = -1;
  int second_id = -1;
  double dif = std::numeric_limits<double>::max();
  for (int i = 0; i < n - 1; ++i) {
    double fabs = std::fabs(a[i+1]-a[i]);
    if (fabs < dif) {
      first_id = i+1;
      second_id = i;
      dif = fabs;
    }
  }

  if (first_id != -1 && second_id != -1) {
    std::cout << "Closest pair: " << a[first_id] << " and " << a[second_id]
      << " : " << dif << '\n';
//    std::cerr << a << std::endl;
  } else {
    std::cout << "Error: no elements in array\n";
  }
  return 0;
}
