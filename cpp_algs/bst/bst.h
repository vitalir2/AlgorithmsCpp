#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>

template <typename Key, typename Value>
class BST {
public:
  // constructors, asssignment, destructor
  BST() : root_(nullptr) {}
  BST(BST&& o) : root_(o.root_) {}
  BST& operator=(BST&& o) {
    root_ = o.root_;
  }

  ~BST() {
    destroyTree(root_);
  }

  void insert(const Key& key, const Value& value) {
    insert(key, value, root_, nullptr);
  }

  Value get(const Key& key) const {
    return get(key, root_);
  }

  Value deleteElem(const Key& key) {
    deleteElem(key, root_);
  }

  size_t size() const {
    return size(root_);
  }

  template <typename OutputStream>
  void print(OutputStream& stream = std::cout) const {
    print(stream, root_);
  }

  template <typename OutputStream>
  void printDebug(OutputStream& stream) {
    printDebug(root_, 1, false, stream);
  }

  void printDebug() {
    printDebug(root_, 1, false, std::cout);
  }

  struct Node {
    Key key;
    Value value;
    size_t rank;
    Node* parent;
    Node* left;
    Node* right;

    Node(const Key& key_, const Value& value_, size_t rank_,
        Node* parent_ = nullptr, Node* left_ = nullptr, Node* right_ = nullptr)
      : key(key_), value(value_), rank(rank_), parent(parent_), left(left_), right(right_) {}


  };

  /*
  class Iterator {
  public:
    Iterator(Node* node) {
      putLeftNodes(node);
      cur = left_childs.top()->parent;
      Node* tmp = node;
      for (; tmp->right != nullptr; tmp=tmp->right);
      last = tmp;
    }

    Node* operator->() {
      return *cur;
    }

    Node& operator*() {
      return cur;
    }

    Iterator& operator++() {
      cur = left_childs.top();
      left_childs.pop();
      putLeftNodes(cur->right);
      return *this;
    }

    Iterator& Last() {
      return Iterator(last);
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs.left_childs == rhs.left_childs && lhs.last == rhs.last;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
      return lhs.left_childs != rhs.left_childs || lhs.last != rhs.last;
    }

  private:
    Node* cur;
    std::stack<Node*> left_childs;
    Node* last;
    void putLeftNodes(Node* node) {
      for (Node* tmp = node->left; tmp != nullptr; node=node->left) {
        left_childs.push(node);
      }
    }

  };

  Iterator begin() {
    return Iterator(root_);
  }

  Iterator end() {
    return Iterator(root_).Last();
  }
  */



  Key minKey() const {
    return minNode(root_)->key;
  }

  Value minKeyValue() const {
    return minNode(root_)->value;
  }
  
private:
  void destroyTree(Node* root) {
    if (root != nullptr) {
      destroyTree(root->left);
      destroyTree(root->right);
      delete root;
    }
  }

  void insert(const Key& key, const Value& value, Node* &ptr, Node* parent) {
    if (ptr == nullptr) {
      ptr = new Node(key, value, 1, parent, nullptr, nullptr);
      return;
    }

    if (ptr->key > key) {
      insert(key, value, ptr->left, ptr);
    } else if (ptr->key < key) {
      insert(key, value, ptr->right, ptr);
    } else {
      ptr->value = value; // to eliminate equal keys
    }

    ptr->rank = size(ptr->left) + size(ptr->right) + 1;
    return;
  }

  Value get(const Key& key, Node* ptr) const {
    if (ptr == nullptr) {
      throw std::runtime_error("No element in binary search tree"); // works really slow
    }

    if (key < ptr->key) {
      return get(key, ptr->left);
    } else if (key > ptr->key) {
      return get(key, ptr->right);
    } else {
      return ptr->value;
    }
  }

  void deleteElem(const Key& key, Node* node) {
    if (node == nullptr) {
      throw std::runtime_error("No such element in tree with key = " + std::to_string(key));
    }
    while (node->key != key) {
      if (key < node->key) {
        node = node->left;
      } else if (key > node->key) {
        node = node->right;
      }
    }

    if (node->left == nullptr && node->right == nullptr) {
      if (node->parent != nullptr) {
        if (node->parent->left == node) {
          node->parent->left = nullptr;
        } else {
          node->parent->right = nullptr;
        }
      }
      delete node;
    } else if (node->left != nullptr) {
      node->key = node->left->key;
      node->value = node->left->value;
      delete node->left;
      node->left = nullptr;
    } else if (node->right != nullptr) {
      node->key = node->right->key;
      node->value = node->right->value;
      delete node->right;
      node->right = nullptr;
    } else {
      Node* min_right = minNode(node->right);
      // bad style, I think
      node->key = min_right->key;
      node->value = min_right->value;
      deleteMin(node->right);
    }
  }

  size_t size(Node* ptr) const {
    if (ptr == nullptr) {
      return 0;
    } else {
      return ptr->rank;
    }
  }

  template <typename OutputStream>
  void print(OutputStream& stream, Node* node) const {
    if (node != nullptr) {
      print(stream, node->left);
      stream << '[' << node->key << ", "
        << node->value << "] ";
      print(stream, node->right);
    }
  }

  template <typename OutputStream>
  void printDebug(Node* node, int height, bool left, OutputStream& stream) {
    if (node != nullptr) {
      printDebug(node->left, height+1, true, stream);
      std::string message_tree = left ? "Left" : "Right";
      if (height == 1) {
        message_tree = "Root";
      }
      stream << "Height = " << height << ", branch - " << message_tree
        << ", key and value: " << node->key << " " << node->value << std::endl;
      printDebug(node->right, height+1, false, stream);
    }
  }

  Node* minNode(Node* ptr) const {
    if (ptr->left != nullptr) {
      return minNode(ptr->left);
    }
    return ptr;
  }

  void deleteMin(Node* root) {
    Node* min_node = minNode(root);
    if (min_node->right == nullptr) {
      if (min_node->parent != nullptr) {
        min_node->parent->left = nullptr;
        delete min_node;
      } else {
        delete min_node;
      }
    } else {
      min_node->key = min_node->right->key;
      min_node->value = min_node->right->value;
      delete min_node->right;
      min_node->right = nullptr;
    }
  }
 

  Node* root_;

};
