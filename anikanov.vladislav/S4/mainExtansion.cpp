#include "mainExtansion.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <binarySearchTree.hpp>

void anikanov::print(std::ostream &os, const tree &dict)
{
  for (auto i = dict.begin(); i != dict.end(); ++i){
    os << i->first << " " << i->second;
    if (++i != dict.end()) {
      os << " ";
    }
    --i;
  }
}

bool anikanov::loadFromFile(const std::string &filename, std::map< std::string, tree > &dictionaries)
{
  std::ifstream infile(filename);
  if (!infile) {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(infile, line)) {
    if (line.empty()) {
      continue;
    }

    char *cstr = new char[line.length() + 1];
    std::strcpy(cstr, line.c_str());

    char *token = std::strtok(cstr, " ");
    std::string dictName(token);
    int key = 0;
    std::string value = "";
    BinarySearchTree< int, std::string, std::less<> > tree;

    while ((token = std::strtok(nullptr, " "))) {
      key = std::stoi(token);
      token = std::strtok(nullptr, " ");
      if (token) {
        value = token;
        tree.push(key, value);
      }
    }

    dictionaries[dictName] = std::move(tree);
    delete[] cstr;
  }
  return true;
}

void anikanov::printInvalidUsage(std::ostream &os, char **argv)
{
  os << "Usage: " << argv[0] << " filename\n";
}

void anikanov::printInvalidCommand(std::ostream &os)
{
  os << "<INVALID COMMAND>\n";
}

void anikanov::printEmpty(std::ostream &os)
{
  os << "<EMPTY>\n";
}
