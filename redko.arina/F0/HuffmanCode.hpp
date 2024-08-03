#ifndef HUFFMANCODE_HPP
#define HUFFMANCODE_HPP
#include <iostream>
#include "binarySearchTree.hpp"

namespace redko
{
  class HuffmanCode
  {
  public:
    HuffmanCode();
    explicit HuffmanCode(const std::string & src);
    HuffmanCode(const std::string & res, const BSTree< char, std::string > & alph);

    std::string getEncoded();
    std::string getDecoded();

    BSTree< char, std::string > getEncoding();

    void encode();
    void decode();

  private:
    struct HuffmanNode
    {
      HuffmanNode(unsigned long frequency = 0, char c = '0', HuffmanNode * lPtr = nullptr, HuffmanNode * rPtr = nullptr):
        freq(frequency),
        data(c),
        left(lPtr),
        right(rPtr)
      {}

      bool operator>(const HuffmanNode * rhs)
      {
        return freq > rhs->freq;
      }

      unsigned long freq;
      char data;
      HuffmanNode * left;
      HuffmanNode * right;
    };

    void countFreq();
    void makeCharCode(HuffmanNode * node, const std::string & str);
    void makeCodeTree();

    BSTree< char, unsigned long > charsFreq_;
    BSTree< char, std::string > charsCode_;
    std::string sourseText_;
    std::string encodedText_;
    HuffmanNode * root_;
  };

  bool isBinary(const std::string & str);
  std::istream & operator>>(std::istream & in, HuffmanCode & obj);
}

#endif
