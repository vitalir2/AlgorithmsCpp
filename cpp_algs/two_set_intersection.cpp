#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "test_generators/points_generator.h"

constexpr double big_number = 1'00;

class Point2D {
public:
  double x;
  double y;

  bool operator<(const Point2D& rhs) const {
    return std::make_pair(this->x, this->y) < std::make_pair(rhs.x, rhs.y);
  }

  friend std::ostream& operator<<(std::ostream& stream, const Point2D& rhs);
};

std::ostream& operator<<(std::ostream& stream, const Point2D& rhs) {
  stream << '[' << rhs.x << ',' << rhs.y << ']';
  return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& rhs) {
  stream << '{' << ' ';
  for (const T& element: rhs) {
    stream << element << ' ';
  }
  stream << '}';
  return stream;
}

// Draw a picture of algo (2 sets & their intersection)
// also realise how to use sorted arrays to find their intersection
// in o(n^2) time

// Speed << n^2
int countNumberOfPoints(const std::vector<Point2D>& first,
    const std::vector<Point2D>& second) {

  auto it = first.cbegin();
  auto jt = second.cbegin();
  int count = 0;
  while (it != first.cend() && jt != second.cend()) {
    if (*it < *jt) {
      ++it;
    } else {
      if (!(*jt < *it)) {
        ++it;
        ++count;
      }
      ++jt;
    }
  }

  return count;
}

int countPointsSlowestWay(const std::vector<Point2D>& first, const std::vector<Point2D>& second) {
  int count = 0;
  for (auto it = first.cbegin(); it != first.cend(); ++it) {
    for (auto jt = second.cbegin(); jt != second.cend(); ++jt) {
      if (it->x == jt->x && it->y == jt->y) {
        ++count;
        break;
      }
    }
  }
  return count;
}

void generatePointsFile(const std::string& file_name){
  PointGenerator<Point2D> generator;
  std::ofstream fout(file_name);

  for (size_t i = 0; i < big_number; ++i) {
    fout << generator.generate(1.0, big_number) << '\n';
  }

  fout.close();
}

int main(int argc, char* argv[]) {
  std::string mode = "";

  if (argc > 1) {
    mode = argv[1];
  }

  if (mode == "gen"){
    std::cerr << "BADDD\n";
    generatePointsFile("points.txt");
    return 0;
  }

  std::vector<Point2D> first;
  std::vector<Point2D> second;
  double x = 0, y = 0;
  char c1, c2, c3;
  bool first_push = true;

  while (std::cin >> c1 >> x >> c2 >> y >> c3) {
    if (first_push) {
      first.push_back({x, y});
    } else {
      second.push_back({x, y});
    }
    first_push = !first_push;
  }

  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());

  std::cout << "First set: " << first << '\n';
  std::cout << "Second set: " << second << '\n';

  std::cout << "Count of points that are both in the intersection: "
    << countNumberOfPoints(first, second) << '\n';

  return 0;
}
