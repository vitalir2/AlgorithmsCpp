/*=============================================================================
   Copyright (C) 2021 Khvostov Vitaly. All rights reserved.
   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/

#ifndef STACK_H
#define STACK_H

#include <vector>

template<typename T>
class Stack {
public:
  // constructors, asssignment, destructor
  Stack() noexcept : data_(1), size_(0), capacity_(1) {}
  Stack(const Stack& o) = default;
  Stack(Stack&& o) = default;
  Stack& operator=(const Stack& o) = default;
  Stack& operator=(Stack&& o) = default;
  ~Stack() = default;

  void push(const T& value) {
    if (capacity_ <= size_) {
      this->resize(capacity_ * 2);
    }
    data_[size_++] = value;
  }

  T pop() {
    if (size_ <= capacity_ / 4 && capacity_ / 2 != 0) {
      this->resize(capacity_ / 2);
    }
    return data_[--size_];
  }

  size_t size() const noexcept {
    return size_;
  }

  bool empty() const noexcept {
    return size_ == 0;
  }

private:
  void resize(size_t capacity) {
    std::vector<T> data(capacity);
    std::move(data_.begin(), data_.begin() + capacity, data.begin());
    data_ = std::move(data);
    capacity_ = capacity;
  }

  std::vector<T> data_;
  size_t size_ = 0;
  size_t capacity_ = 1;
};

#endif // STACK_H

/*
int main() {
  Stack<int> stack;
  for (int i = 0; i < 100; ++i) {
    stack.push(i);
  }
  
  for (int i = 0; i < 100; ++i) {
    std::cout << stack.pop() << " ";
  }

  std::cout << std::endl;
  return 0;
}
*/
