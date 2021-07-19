#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace utils {

  void generateRandomVector(std::vector<int>& v, int upper_bound);
  void generateRandomVector(std::vector<double>& v, int upper_bound);

  template<typename Number>
  void generateRandomSigns(std::vector<Number>& v) {
    if (std::is_arithmetic_v<Number>) {
      std::random_device rd;
      std::mt19937 gen(rd());
      constexpr int random_const = 100;
      std::uniform_int_distribution<int> dist(1, random_const);
      for (auto& elem: v) {
        int rd = dist(gen);
        elem = rd % 2 == 0 ? elem : -elem;
      }
    } else {
      throw std::invalid_argument("Not a number, invalid arg");
    }
  }

  template<typename T>
  void uniqueAndShuffle(std::vector<T>& v) {
    std::sort(v.begin(), v.end());
    auto unique_it = std::unique(v.begin(), v.end());
    v.resize(std::distance(v.begin(), unique_it));

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
  }

  void fillAscendVector(std::vector<int>& v);
  void fillDescendVector(std::vector<int>& v);

  template<typename T>
  std::istream& operator>>(std::istream& stream, std::vector<T>& v) {
    for (T& elem: v) {
      stream >> elem;
    }
    return stream;
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& stream, const std::vector<T>& v) {
    for (const T& elem: v) {
      stream << elem << " ";
    }
    return stream;
  }

  class TimeCounter {
  public:
    TimeCounter();
    ~TimeCounter();
  private:
    std::chrono::time_point<std::chrono::steady_clock> start;
  };

}
#endif // UTILS_H
