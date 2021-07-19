#ifndef INDEX_QUEUE_H
#define INDEX_QUEUE_H

#include <cstddef>
#include <iostream>
#include <vector>

// Now only min
template <typename T>
class IndexQueue {
public:
  IndexQueue(size_t max_size) : size_(0), pq_(max_size+1), qp_(max_size, -1),
    keys_(max_size+1) {
  }
  void insert(size_t i, const T& key); 
  void change(size_t i, const T& key);
  bool contains(size_t i) const {
    return qp_[i] != -1;
  }
  size_t delMin();
  T min() const {
    return keys_[pq_[1]];
  }
  size_t minIndex() const {
    return pq_[1];
  }
  void remove(size_t i);
  bool isEmpty() const {
    return size_ == 0;
  }
  size_t size() const {
    return size_;
  }
private:
  size_t size_;
  std::vector<int> pq_; // heap pos gives index
  std::vector<int> qp_; // index gives heap position
  std::vector<T> keys_;

  void swim(size_t k);
  void sink(size_t k);

  // heap position ids
  bool less_(size_t i, size_t j) {
    return keys_[pq_[i]] < keys_[pq_[j]];
  }

  void exchange(size_t i, size_t j) { 
    std::swap(qp_[pq_[i]], qp_[pq_[j]]);
    std::swap(pq_[i], pq_[j]);
  }

};

#endif // INDEX_QUEUE_H

template<typename T>
void IndexQueue<T>::insert(size_t i, const T& key) { // i - index, size_ - pos in pq
    ++size_;
    qp_[i] = size_;
    pq_[size_] = i;
    keys_[i] = key;
    swim(size_);
}

template<typename T>
void IndexQueue<T>::change(size_t i, const T& key) {
  keys_[i] = key;
  swim(qp_[i]);
  sink(qp_[i]);
}

template<typename T>
size_t IndexQueue<T>::delMin() {
  size_t index_min = pq_[1];
  exchange(size_--, 1);
  qp_[pq_[size_+1]] = -1;
  sink(1);
  return index_min;
}

template<typename T>
void IndexQueue<T>::remove(size_t i) {
  exchange(size_--, i); // qp or just i?
  swim(qp_[i]);
  sink(qp_[i]);
  qp_[pq_[size_+1]] = -1;
}

template<typename T>
void IndexQueue<T>::swim(size_t k) {
  while (k > 1 && less_(k, k/2)) {
    exchange(k, k/2);
    k /= 2;
  }
}

template<typename T>
void IndexQueue<T>::sink(size_t k) {
  while (2*k <= size_) {
    size_t i = 2 * k;
    if (i < size_ && less_(i+1, i)) {
      ++i;
    }
    if (less_(k, i)) {
      break;
    }
    exchange(k, i);
    k = i;
  }
}
