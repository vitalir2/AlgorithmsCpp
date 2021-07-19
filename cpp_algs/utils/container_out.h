#ifndef CONTAINER_OUT_H
#define CONTAINER_OUT_H

#include <iostream>
#include <map>
#include <forward_list>
#include <vector>
#include <utility>

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& rhs) {
  stream << '{';
  for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
    if (it + 1 == rhs.cend()) {
      stream << *it;
    } else {
      stream << *it << ", ";
    }
  }
  stream << '}';
  return stream;
}

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& stream, const std::map<Key, Value>& rhs) {
  stream << '{';
  for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
    if (it + 1 == rhs.cend()) {
      stream << *it;
    } else {
      stream << *it << ", ";
    }
  }
  stream << '}';
  return stream;
}

template<typename U, typename V>
std::ostream& operator<<(std::ostream& stream, const std::pair<U, V>& rhs) {
  stream << '[' << rhs.first << ", " << rhs.second << ']';
  return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::forward_list<T>& rhs) {
  stream << '{';
  for (auto it = rhs.cbegin(); it != rhs.cend();++it) {
    stream << *it << ", ";
  }
  stream << '}';
  return stream;
}

#endif // CONTAINER_OUT_H
