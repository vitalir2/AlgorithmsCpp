#ifndef FORWARD_LINKED_LIST_H
#define FORWARD_LINKED_LIST_H

#include <iostream>

// Challenge: create your own iterator!
template <typename T>
class ForwardLinkedList {
public:
  // constructors, asssignment, destructor
  ForwardLinkedList();
  ForwardLinkedList(const ForwardLinkedList& o);
  ForwardLinkedList(ForwardLinkedList&& o);
  ForwardLinkedList& operator=(const ForwardLinkedList& o);
  ForwardLinkedList& operator=(ForwardLinkedList&& o);
  ~ForwardLinkedList();

  size_t size() const noexcept {
    return size_;
  }

  bool empty() const noexcept {
    return size_ == 0;
  }
  
private:
  struct ListNode {
    T value;
    ListNode next;
  };

  ListNode first_;
  size_t size_;
  
};

#endif // FORWARD_LINKED_LIST_H
