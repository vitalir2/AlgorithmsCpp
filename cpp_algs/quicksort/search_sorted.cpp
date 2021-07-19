#include <iostream>
#include <vector>

#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/container_out.h"
#include "/home/vitalir/Programming/algorithms/cpp_algs/utils/utils.h"

// log n => binary search!! 

// Fucking copypaste
template<typename RandIter>
int kth(RandIter arr1, RandIter arr2, RandIter end1, RandIter end2, int k)
{
    if (arr1 == end1)
        return arr2[k];
    if (arr2 == end2)
        return arr1[k];
    int mid1 = (end1 - arr1) / 2;
    int mid2 = (end2 - arr2) / 2;
    if (mid1 + mid2 < k)
    {
        if (arr1[mid1] > arr2[mid2])
            return kth(arr1, arr2 + mid2 + 1, end1, end2,
                k - mid2 - 1);
        else
            return kth(arr1 + mid1 + 1, arr2, end1, end2,
                k - mid1 - 1);
    }
    else
    {
        if (arr1[mid1] > arr2[mid2])
            return kth(arr1, arr2, arr1 + mid1, end2, k);
        else
            return kth(arr1, arr2, end1, arr2 + mid2, k);
    }
}


int main() {
  constexpr int n = 3;
  std::vector<int> a1(n);
  std::vector<int> a2(n);

  utils::generateRandomVector(a1, 2*n);
  utils::generateRandomVector(a2, 2*n);
  std::sort(a1.begin(), a1.end());
  std::sort(a2.begin(), a2.end());

  std::cout << a1 << '\n' << a2 << std::endl;
  int k = 0;
  std::cin >> k;

  int found = kth(a1.begin(), a2.begin(), a1.end(), a2.end(), k);

  std::cout << found << std::endl;

  return 0;
}
