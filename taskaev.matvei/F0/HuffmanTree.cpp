#include <string>
#include <cstdlib>
#include "HuffmanTree.hpp"

void taskaev::HuffmanTree::build(const std::string& text)
{
  for (char c : text)
  {
    freq_[c]++;
  }

  List<Node*> nodes;
  for (const auto& kv : freq_)
  {
    nodes.pushBack(new Node(kv.first, kv.second));
  }

  while (nodes.getSize() > 1)
  {
    Node* left = nodes.front();
    nodes.popFront();
    Node* right = nodes.front();
    nodes.popFront();
    nodes.pushBack(new Node('\0', left->freq_ + right->freq_, left, right));
  }

  root_ = nodes.front();
  genCode(root_, "");
}

void taskaev::HuffmanTree::genCode(Node* node, const std::string& code)
{
  if (!node)
  {
    return;
  }
  if (!node->left_ && !node->right_)
  {
    codes_[node->symbol_] = code.empty() ? "1" : code;
  }
  genCode(node->left_, code + "0");
  genCode(node->right_, code + "1");
}

std::string taskaev::HuffmanTree::encode(const std::string& text)
{
  std::string encoded;
  for (char c : text)
  {
    encoded += codes_[c];
  }
  return encoded;
}

void taskaev::HuffmanTree::freqTable(std::ostream& out) {
  for (const auto& kv : freq_)
  {
    out << kv.first << ": " << kv.second << '\n';
  }
}

void taskaev::HuffmanTree::codeTable(std::ostream& out) {
  for (const auto& kv : codes_)
  {
    out << kv.first << ": " << kv.second << '\n';
  }
}

