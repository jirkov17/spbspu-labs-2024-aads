#ifndef CODING_HUFFMAN_HPP
#define CODING_HUFFMAN_HPP

#include <string>
#include "list.hpp"
#include "queue.hpp"
#include "binarySearchTreeAVL.hpp"

namespace ponomarev
{
  struct MinHeapNode
  {
    MinHeapNode(char data, int freq);

    char data;
    int freq;
    MinHeapNode * left, * right;
  };

  struct Compare
  {
    bool operator()(MinHeapNode * l, MinHeapNode * r);
  };

  class HuffmanCode
  {
  public:
    HuffmanCode();

    BSTree < char, std::string, int > codes;
    BSTree < char, int, int > freq;
    std::string text;
    std::string decodingText;
    Queue < MinHeapNode * > minHeap;
    List< std::string > fileNames;
  };

  void printCodes(MinHeapNode * root, std::string str);
  void storeCodes(MinHeapNode * root, std::string str, HuffmanCode & data);
  void createTree(HuffmanCode & data);
  void calcFreq(std::string str, HuffmanCode & data);
  void decodeFile(HuffmanCode & data);
  void makeEncode(HuffmanCode & data);
  void fillFreq(std::string parameter, HuffmanCode & data);
}

#endif
