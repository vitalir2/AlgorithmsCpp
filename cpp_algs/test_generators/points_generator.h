#ifndef POINTS_GENERATOR_H
#define POINTS_GENERATOR_H

#include <stdexcept>
#include <random>

// with coordinates = double
template<typename Point>
class PointGenerator {
public:
  PointGenerator() : gen(std::random_device{}()) {
  }

  Point generate(double lower_bound, double upper_bound) {
    std::uniform_real_distribution<double> dist(lower_bound, upper_bound);
    return Point(dist(gen), dist(gen));
  }
private:
  std::mt19937 gen;
};

#endif // POINTS_GENERATOR_H
