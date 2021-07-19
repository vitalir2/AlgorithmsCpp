#include <iostream>

template <typename Key, typename Value>
class RedBlackST {
public:
  // constructors, asssignment, destructor
  RedBlackST() : root_(nullptr) {}
  RedBlackST(const RedBlackST& o) = delete; // Not working yet
  RedBlackST(RedBlackST&& o) {
    root_ = o.root_;
  }
  RedBlackST& operator=(const RedBlackST& o) = delete; // Not working yet
  RedBlackST& operator=(RedBlackST&& o) {
    root_ = o.root_;
  }
  ~RedBlackST() { // or make destructor in Nodes?
    destroyTree(root_);
  }

  void insert(const Key& key, const Value& value) {
    root_ = insert(key, value, root_);
  }

  Value& operator[](const Key& key) const {
    return get(key, root_);
  }

  void inorderPrint() const {
    inorderPrint(root_);
  }
  
private:

  constexpr static bool RED = true;
  constexpr static bool BLACK = false;
  struct Node {
    Key key;
    Value value;
    bool colour;

    Node* left;
    Node* right;

  };

  Node* root_;

  bool isRed(Node* node) {
    if (node == nullptr) {
      return BLACK;
    }
    return node->colour == RED;
  }

  Node* insert(const Key& key, const Value& value, Node*& root) {
    if (root == nullptr) {
      return new Node{key, value, RED, nullptr, nullptr};
    } else if (key < root->key) {
      root->left = insert(key, value, root->left);
    } else if (key > root->key) {
      root->right = insert(key, value, root->right);
    } else {
      root->key = key;
    }

    if (!isRed(root->left) && isRed(root->right)) {
      root = rotateLeft(root);
    }
    if (isRed(root->left) && isRed(root->left->left)) {
      root = rotateRight(root);
    }
    if (isRed(root->left) && isRed(root->right)) {
      flipColors(root);
    }

    return root;
  }

  Value& get(const Key& key, Node* root) const {
    if (root == nullptr) {
      // throw? 
    } else {
      if (key < root->key) {
        return get(key, root->left);
      } else if (key > root->key) {
        return get(key, root->right);
      } else {
        return root->value;
      }
    }
  }

  void inorderPrint(Node* root) const {
    if (root != nullptr) {
      inorderPrint(root->left);
      std::cout << "[ " << root->key << ", " << root->value << " ] ";
      inorderPrint(root->right);
    }
  }

  Node* rotateLeft(Node* root) {
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    x->colour = root->colour;
    root->colour = RED;
    return x;
  }

  Node* rotateRight(Node* root) {
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    x->colour = root->colour;
    root->colour = RED;
    return x;
  }

  void flipColors(Node* root) {
    root->colour = RED;
    root->left->colour = BLACK;
    root->right->colour = BLACK;
  }

  void destroyTree(Node* root) {
    if (root != nullptr) {
      if (root->left != nullptr) {
        destroyTree(root->left);
      }
      if (root->right != nullptr) {
        destroyTree(root->right);
      }
      delete root;
    }
  }
  
};
