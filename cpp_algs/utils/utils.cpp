#include "utils.h"
#include <random>

namespace utils {

  void generateRandomVector(std::vector<int>& v, int upper_bound) {
      std::random_device rd;
      std::mt19937 gen(rd()); 
      std::uniform_int_distribution<> distrib(1, upper_bound);
      for (int& elem: v) {
        elem = distrib(gen);
      }
  }

  void generateRandomVector(std::vector<double>& v, int upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, upper_bound);
    for (double& elem: v) {
      elem = dist(gen);
    }
  }

  void fillAscendVector(std::vector<int>& v) {
    int i = 0;
    for (int& elem: v) {
      elem = ++i;
    }
  }

  void fillDescendVector(std::vector<int>& v) {
    int i = std::numeric_limits<int>::max();
    for (int& elem: v) {
      elem = --i;
    }
  }

  TimeCounter::TimeCounter() {
  //    std::clog << "Start clock\n";
      start = std::chrono::steady_clock::now();
  }

  TimeCounter::~TimeCounter() {
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    std::clog << "End clock, time = " << diff.count() << " ms" << std::endl;
  }
}
