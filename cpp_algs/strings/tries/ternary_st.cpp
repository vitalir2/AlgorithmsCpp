#include <algorithm>
#include <memory>
#include <optional>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

template<typename T>
class TernaryST {
struct Node;
using NodePtr = std::shared_ptr<Node>;
public:
  TernaryST() = delete;
  TernaryST(size_t alphabet_size) : alphabet_size_(alphabet_size) {
  }
  TernaryST(const TernaryST& trie) = delete; 
  TernaryST(TernaryST&& trie) = default;
  TernaryST& operator=(const TernaryST& trie) = delete;
  TernaryST& operator=(TernaryST&& trie) = default;
  ~TernaryST() = default;

  void insert(const std::string& key, const T& value) noexcept {
    root_ = insert(root_, key, value, 0);
  }

  std::optional<T> at(const std::string& key) {
    NodePtr ptr = at(root_, key, 0);
    if (ptr.get() == nullptr) {
      throw std::runtime_error("No element in a trie: " + key);
    }
    return ptr->value;
  }

  T& operator[](const std::string& key) noexcept {
    NodePtr ptr = at(root_, key, 0);
    return ptr->value;
  };

  const std::optional<T> at(const std::string& key) const {
    NodePtr ptr = at(root_, key, 0);
    if (ptr.get() == nullptr) {
      throw std::runtime_error("No element in a trie: " + key);
    }
    return ptr->value;
  }

  const T& operator[](const std::string& key) const noexcept {
    NodePtr ptr = at(root_, key, 0);
    return ptr->value;
  };

  void erase(const std::string& key) noexcept {
    root_ = erase(root_, key, 0);
  }

  bool contains(const std::string& key) const noexcept {
    return this->operator[](key) != nullptr;
  };

  using Keys = std::vector<std::string>;
  Keys keys() const noexcept {
    Keys result;
    collect(root_, "", result);
    return result;
  }

  Keys keys_with_prefix(const std::string& prefix) const noexcept {
    Keys result;
    NodePtr node = at(root_, prefix, 0);
    collect(node, prefix, result);
    return result;
  }
private:
  NodePtr root_;
  const size_t alphabet_size_;

  struct Node {
    std::optional<T> value;
    char c;
    NodePtr left;
    NodePtr middle;
    NodePtr right;
  };

  NodePtr insert(NodePtr& ptr, const std::string& key,
      const T& value, size_t d) {
    char c = key[d];
    if (ptr == nullptr) {
      ptr = std::make_shared<Node>();
      ptr->c = c;
    }
    if (c < ptr->c) {
      ptr->left = insert(ptr->left, key, value, d);
    } else if (c > ptr->c) {
      ptr->right = insert(ptr->right, key, value, d);
    } else if (d < key.size() - 1) {
      ptr->middle = insert(ptr->middle, key, value, d + 1);
    } else {
      ptr->value = value;
    }
    return ptr;
  }

  NodePtr at(const NodePtr& ptr, const std::string& key, size_t d) {
    char c = key[d];
    if (ptr == nullptr) {
      return ptr;
    }
    if (c < ptr->c) {
      return at(ptr->left, key, d);
    } else if (c > ptr->c) {
      return at(ptr->right, key, d);
    } else if (d < key.size() - 1) {
      return at(ptr->middle, key, d + 1);
    } else {
      return ptr;
    }
  }
  NodePtr at(const NodePtr& ptr, const std::string& key, size_t d) const {
    char c = key[d];
    if (ptr == nullptr) {
      return ptr;
    }
    if (c < ptr->c) {
      return at(ptr->left, key, d);
    } else if (c > ptr->c) {
      return at(ptr->right, key, d);
    } else if (d < key.size() - 1) {
      return at(ptr->middle, key, d + 1);
    } else {
      return ptr;
    }
  }

  // Lazy delete (can improve by adding parent to node or smart recursion)
  NodePtr erase(NodePtr& ptr, const std::string& key,
      size_t d) {
    if (ptr == nullptr) {
      return ptr;
    }
    char c = key[d];
    if (c < ptr->c) {
      ptr->left = erase(ptr->left, key, d);
    } else if (c > ptr->c) {
      ptr->right = erase(ptr->right, key, d);
    } else if (d < key.size() - 1) {
      ptr->middle = erase(ptr->middle, key, d + 1);
    } else {
      ptr->value.reset();
    }
    if (!hasChild(ptr)) {
      ptr.reset();
    }
    return ptr;
  }

  bool hasChild(const NodePtr& ptr) {
    return ptr->left != nullptr
      || ptr->right != nullptr
      || ptr->middle != nullptr;
  }

  void collect(NodePtr ptr, std::string prefix, Keys& keys) const noexcept {
    if (ptr == nullptr) {
      return;
    }
    if (ptr->value.has_value()) {
      prefix += ptr->c;
      keys.push_back(prefix);
      prefix.pop_back();
    }
    collect(ptr->left, prefix, keys);
    collect(ptr->right, prefix, keys);
    collect(ptr->middle, prefix + ptr->c, keys);
  }
};
