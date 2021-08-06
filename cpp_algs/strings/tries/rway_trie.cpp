#include <algorithm>
#include <memory>
#include <optional>
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
  void erase(const std::string& key) {
    throw std::runtime_error("Doesn't work yet");
  }
  bool contains(const std::string& key) const noexcept {
    return this->operator[](key) != nullptr;
  };
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
/*
  std::shared_ptr<Node> erase(std::shared_ptr<Node>& ptr, const std::string& key,
      size_t d) {
    if (key.size() == d) {
      ptr->value.reset();
      if (std::find_if(ptr->children.begin(), ptr->children.end(),
            [](const std::shared_ptr<Node>& ptr) { return ptr.get() != nullptr; })
          != ptr->children.end()) {
         ptr.reset();
      }
    }
  }
*/
};
