/*=============================================================================
   Copyright (C) 2021 Khvostov Vitaly. All rights reserved.
   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/

#ifndef QUEUE_BY_STACK_H
#define QUEUE_BY_STACK_H

#include <iostream>

#include "stack.h"

template<typename T>
class QueueByStack {
public:
  // constructors, asssignment, destructor
  QueueByStack() = default;
  QueueByStack(const QueueByStack& o) = default;
  QueueByStack(QueueByStack&& o) = default;
  QueueByStack& operator=(const QueueByStack& o) = default;
  QueueByStack& operator=(QueueByStack&& o) = default;
  ~QueueByStack() = default;

  void enqueue(const T& value) {
    front_.push(value);
  }

  T dequeue() {
    if (end_.empty()) {
      while(!front_.empty()) {
        end_.push(front_.pop());
      }
    }
    return end_.pop();
  }

  size_t size() const noexcept {
    return front_.size() + end_.size();
  }

  bool empty() const noexcept {
    return front_.size() + end_.size() == 0;
  }
  
private:
  Stack<T> front_;
  Stack<T> end_;
};

#endif // QUEUE_BY_STACK_H

/*
int main() {
  QueueByStack<int> queue;
  queue.enqueue(5);
  std::cout << queue.dequeue() << std::endl;
  return 0;
}
*/
