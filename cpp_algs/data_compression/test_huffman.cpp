#include <iostream>

#include "huffman_compression.cpp"

int main() {
  std::cout << "Enter the name of the file\n";
  std::string file_name;
  std::cin >> file_name;
  Huffman encoder;
  encoder.encode(file_name);
  encoder.decode(file_name + ".enc");
  return 0;
}
