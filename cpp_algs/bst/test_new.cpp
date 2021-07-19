#include <iostream>


void f(double* n) {
  n = new double(4);
}

void g(double* n) {
  delete n;
}

int main() {
  double* x = new double(5);
  f(x);
  std::cout << *x << std::endl;
  g(x);
  std::cout << *x << std::endl;
  int* m = nullptr;
  delete m;
  return 0;
}
