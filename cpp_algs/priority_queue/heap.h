#include <algorithm>
#include <cstddef>
#include <iostream>

// Easy implementation (without allocators and so on)
// Later - compare + allocator

template <typename T>
class Heap final {
public:
  Heap() : data_(new T[1]), size_(0), capacity_(1) {
  }
  Heap(size_t size) : data_(new T[size<<1]), size_(size), capacity_(size*2) {
  }
  Heap(const Heap<T>& heap) : data_(new T[heap.size_]), size_(heap.size_),
  capacity_(heap.capacity_) {
    for (int i = 0; i < size_; ++i) {
      data_[i] = heap.data_[i];
    }
  }
  Heap& operator=(const Heap<T>& heap) {
    delete[] data_;

    data_ = new T[heap.capacity_];
    size_ = heap.size_;
    capacity_ = heap.capacity_;

    for (int i = 0; i < size_; ++i) {
      data_[i] = heap.data_[i];
    }
  }

  ~Heap() {
    delete[] data_;
  }

  void insert(const T& value) {
    if (size_ >= capacity_) {
      resize(capacity_ * 2);
    }
    data_[size_++] = value;
    swim(size_-1);
  }

  T min() const {
    return data_[0];
  }

  void deleteMin() {
    std::swap(data_[0], data_[--size_]);
    sink(0);
  }

  void print() const {
    for (size_t i = 0; i < size_; ++i) {
      std::cout << data_[i] << " ";
    }
  }

//       1
//     /  \
//    9    8

private:
  T* data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t capacity) {
    T* tmp = new T[capacity];
    for (size_t i = 0; i < size_; ++i) {
      tmp[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = tmp;
    capacity_ = capacity;
  }

  void swim(size_t k) {
    if (data_[(k-1)/2] < data_[k]) {
      return;
    }
    while (k > 0 && data_[(k-1)/2] > data_[k]) {
      std::swap(data_[(k-1)/2], data_[k]);
      k = (k-1)/2;
    }
  }
  // 1 3 7
  // -> 1 1 3

  void sink(size_t k) {
    while (2*k+1 < size_) {
      size_t min_id = 2*k+1;
      if (min_id + 1 < size_ && data_[min_id] > data_[min_id+1]) {
        ++min_id;
      }
      if (!(data_[k] > data_[min_id])) {
        break;
      }
      std::swap(data_[k], data_[min_id]);
      k = min_id;
    }
  }
};
