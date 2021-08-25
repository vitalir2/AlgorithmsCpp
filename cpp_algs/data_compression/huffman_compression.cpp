#include <bitset>
#include <fstream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

constexpr int alphabet_size = 256; // extended ASCII

class Huffman {
  struct Node;
  using NodePtr = std::shared_ptr<Node>;
public:
  Huffman() {
  }
  ~Huffman() {
    if (fin.is_open()) {
      fin.close();
    }
    if (fout.is_open()) {
      fout.close();
    }
  }
  NodePtr buildTrie(const std::vector<int>& frequencies) {
    std::priority_queue<NodePtr> pq;
    for (int c = 0; c < alphabet_size; ++c) {
      if (frequencies[c] > 0) {
        pq.push(std::make_shared<Node>(c, frequencies[c], nullptr, nullptr));
      }
    }

    while (pq.size() > 1) {
      NodePtr first = pq.top();
      pq.pop();
      NodePtr second = pq.top();
      pq.pop();
      NodePtr parent = std::make_shared<Node>('\0', first->frequency + second->frequency,
          first, second);
      pq.push(parent);
    }

    return pq.top();
  }

  void writeTrie(NodePtr node) {
    if (node->isLeaf()) {
      writeBool(true);
      writeChar(node->ch);
      return;
    }
    writeBool(false);
    writeTrie(node->left);
    writeTrie(node->right);
  }

  void encode(const std::string& file_name) {
    resetStream(file_name, true);
    std::string str = readString();
    std::vector<int> frequencies(alphabet_size);
    for (char c: str) {
      ++frequencies[c];
    }
    root = buildTrie(frequencies);
    buildCodeTable(root);
    writeTrie(root);
    writeInt(str.size());

    for (char c: str) {
      std::string code = code_table_[c];
      for (char code_symbol: code) {
        if (code_symbol == '1') {
          writeBool(true);
        } else {
          writeBool(false);
        }
      }
    }
  }

  NodePtr readTrie() {
    if (readBool()) {
      return std::make_shared<Node>(readChar(), 0, nullptr, nullptr);
    } else {
      return std::make_shared<Node>('\0', 0, readTrie(), readTrie());
    }
  }

  void decode(const std::string& file_name) {
    resetStream(file_name, false);
    readTrie();
    int input_size = readInt();
    for (int i = 0; i < input_size; ++i) {
      NodePtr node = root;
      while (!node->isLeaf()) {
        if (readBool()) {
          node = node->left;
        } else {
          node = node->right;
        }
        fout << node->ch;
      }
    }
  }

private:
  std::ifstream fin;
  std::ofstream fout;

  struct Node {
    char ch;
    int frequency;
    NodePtr left, right;

    bool isLeaf() {
      return left == nullptr && right == nullptr;
    }

    bool operator<(const Node& rhs) {
      return this->frequency < rhs.frequency;
    }
  };

  NodePtr root; // Huffman Trie
  std::vector<std::string> code_table_;

  int readInt() {
    int value;
    fin >> value;
    return value;
  }

  bool readBool() {
    bool value;
    fin >> value;
    return value;
  }

  char readChar() {
    char value;
    fin >> value;
    return value;
  }

  std::string readString() {
    std::string value;
    fin >> value;
    return value;
  }

  void writeBool(bool value) {
    fout << value;
  }

  void writeChar(char value) {
    fout << std::bitset<8>(value);
  }

  void writeInt(int value) {
    fout << std::bitset<32>(value);
  }

  void buildCodeTable(const NodePtr& trie) {
    code_table_.resize(alphabet_size);
    buildCodeTable(trie, "");
  }

  void buildCodeTable(NodePtr node, std::string str) {
    if (node->isLeaf()) {
      code_table_[node->ch] = str;
      return;
    }
    buildCodeTable(node->left, str + "0");
    buildCodeTable(node->right, str + "1");
  }

  void resetStream(const std::string& file_name, bool encoding) {
    if (fin.is_open()) {
      fin.close();
    }
    if (fout.is_open()) {
      fout.close();
    }
    if (encoding) {
      fin.open(file_name, std::ios::binary);
      fout.open(file_name + ".enc", std::ios::binary);
    } else {
      fin.open(file_name, std::ios::binary);
      fout.open(file_name + ".dcd", std::ios::binary);
    }
  }
};
