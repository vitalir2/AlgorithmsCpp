#include <algorithm>
#include <memory>
#include <optional>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

template<typename T>
class RWayTrie {
struct Node;
public:
  RWayTrie() = delete;
  RWayTrie(size_t alphabet_size) : alphabet_size_(alphabet_size) {
  }
  RWayTrie(const RWayTrie& trie) = delete; // for now
  RWayTrie(RWayTrie&& trie) = default;
  RWayTrie& operator=(const RWayTrie& trie) = delete; // the same as above
  RWayTrie& operator=(RWayTrie&& trie) = default;
  ~RWayTrie() = default;

  void insert(const std::string& key, const T& value) noexcept {
    root_ = insert(root_, key, value, 0);
  }

  std::optional<T> at(const std::string& key) {
    std::shared_ptr<Node> ptr = at(root_, key, 0);
    if (ptr.get() == nullptr) {
      throw std::runtime_error("No element in a trie: " + key);
    }
    return ptr->value;
  }

  T& operator[](const std::string& key) noexcept {
    std::shared_ptr<Node> ptr = at(root_, key, 0);
    return ptr->value;
  };

  const std::optional<T> at(const std::string& key) const {
    std::shared_ptr<Node> ptr = at(root_, key, 0);
    if (ptr.get() == nullptr) {
      throw std::runtime_error("No element in a trie: " + key);
    }
    return ptr->value;
  }

  const T& operator[](const std::string& key) const noexcept {
    std::shared_ptr<Node> ptr = at(root_, key, 0);
    return ptr->value;
  };



  void erase(const std::string& key) noexcept {
    erase(root_, key, 0);
  }

  bool contains(const std::string& key) const noexcept {
    return this->operator[](key) != nullptr;
  };

  using Keys = std::vector<std::string>;
  Keys keys() const noexcept { // can implement iterator by cashing keys in field
    Keys result;
    collect(root_, "", result);
    return result;
  }

  Keys keys_with_prefix(const std::string& prefix) const noexcept {
    Keys result;
    std::shared_ptr<Node> node = at(root_, prefix, 0);
    collect(node, prefix, result);
    return result;
  }
private:
  std::shared_ptr<Node> root_;
  const size_t alphabet_size_;

  struct Node {
    std::optional<T> value;
    std::vector<std::shared_ptr<Node>> children;

    Node(size_t alphabet_size) {
      children.resize(alphabet_size);
    }
  };

  std::shared_ptr<Node> insert(std::shared_ptr<Node>& ptr, const std::string& key,
      const T& value, size_t d) {
    if (ptr.get() == nullptr) {
      ptr = std::make_shared<Node>(alphabet_size_);
    }
    if (key.size() == d) {
      ptr->value = value;
      return ptr;
    }
    char c = key[d];
    ptr->children[c] = insert(ptr->children[c], key, value, d + 1);
    return ptr;
  }

  std::shared_ptr<Node> at(const std::shared_ptr<Node>& ptr, const std::string& key, size_t d) {
    if (ptr.get() == nullptr) {
      return ptr;
    }
    if (key.size() == d) {
      return ptr;
    }
    char c = key[d];
    return at(ptr->children[c], key, d + 1);
  }

  std::shared_ptr<Node> at(const std::shared_ptr<Node>& ptr, const std::string& key, size_t d) const {
    if (ptr.get() == nullptr) {
      return ptr;
    }
    if (key.size() == d) {
      return ptr;
    }
    char c = key[d];
    return at(ptr->children[c], key, d + 1);
  }



  bool erase(std::shared_ptr<Node>& ptr, const std::string& key,
      size_t d) {
    if (key.size() == d) {
      ptr->value.reset();
    } else {
      char c = key[d];
      if (ptr->children[c].get() != nullptr
          && erase(ptr->children[c], key, d + 1)) {
        ptr->children[c].reset();
      }
    }
    return !ptr->value.has_value() && !hasChild(ptr);
 }

  bool hasChild(const std::shared_ptr<Node>& ptr) {
    return std::find_if(ptr->children.begin(), ptr->children.end(),
    [](const std::shared_ptr<Node>& ptr) { return ptr.get() != nullptr; })
    != ptr->children.end();
  }

  void collect(std::shared_ptr<Node> ptr, std::string prefix, Keys& keys) const noexcept {
    if (ptr == nullptr) {
      return;
    }
    if (ptr->value.has_value()) {
      keys.push_back(prefix);
    }
    for (size_t i = 0; i < ptr->children.size(); ++i) {
      std::shared_ptr<Node>& child = ptr->children[i];
      collect(child, prefix + static_cast<char>(i), keys);
    }
  }
};
