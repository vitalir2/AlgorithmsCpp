#include <iostream>

int collatz(int n) {
  int stopping_time = 0;
  while (n != 1) {
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = 3 * n + 1;
    }
    std::cout << n << " ";
    ++stopping_time;
  }
  return stopping_time;
}

int main() {
  int n;
  std::cout << "Enter number\n";
  std::cin >> n;
  std::cout << "Numbers before conjecture: ";
  int stopping_time = collatz(n);
  std::cout << "\nStopping time of " << n << " = " << stopping_time << '\n';
  return 0;
}
