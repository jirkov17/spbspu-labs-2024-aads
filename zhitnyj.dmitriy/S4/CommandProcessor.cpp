#include <fstream>
#include <iostream>
#include <stdexcept>
#include "CommandProcessor.hpp"

void zhitnyj::processLineToTree(const std::string &line, zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &dict) {
  if (line.empty()) {
    return;
  }

  size_t pos = 0;
  size_t spacePos = line.find(' ');
  std::string dataset = line.substr(0, spacePos);
  BSTree< long long, std::string > tree;

  if (spacePos != std::string::npos) {
    pos = spacePos + 1;
    std::string lastKey;

    while (pos < line.length()) {
      size_t nextSpace = line.find(' ', pos);

      if (nextSpace == std::string::npos) {
        if (lastKey.empty()) {
          lastKey = line.substr(pos);
        }
        else {
          long long key = std::stoll(lastKey);
          std::string value = line.substr(pos);
          tree.push(key, value);
        }
        break;
      }
      else {
        if (lastKey.empty()) {
          lastKey = line.substr(pos, nextSpace - pos);
        }
        else {
          long long key = std::stoll(lastKey);
          std::string value = line.substr(pos, nextSpace - pos);
          tree.push(key, value);
          lastKey.clear();
        }
        pos = nextSpace + 1;
      }
    }
  }

  dict.push(dataset, tree);
}

void zhitnyj::loadTreeFromFile(const std::string &file_, zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &dict) {
  std::ifstream file(file_);
  if (!file) {
    throw std::runtime_error("Unable to open file");
  }

  std::string line;
  while (std::getline(file, line)) {
    processLineToTree(line, dict);
  }
  file.close();
}

void zhitnyj::handleIntersect(zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &dict) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto it1 = dict.find(dataset1);
  auto it2 = dict.find(dataset2);
  if (it1 == dict.end() || it2 == dict.end()) {
    invalidCommandWarning(std::cout);
  }
  else {
    const auto &tree1 = it1->second;
    const auto &tree2 = it2->second;
    BSTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      if (tree2.count(it->first) == 1) {
        result.push(it->first, it->second);
      }
    }

    dict.push(newDataset, result);
  }
}

void zhitnyj::handleComplement(zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &dict) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto it1 = dict.find(dataset1);
  auto it2 = dict.find(dataset2);
  if (it1 == dict.end() || it2 == dict.end()) {
    invalidCommandWarning(std::cout);
  }
  else {
    const auto &tree1 = it1->second;
    const auto &tree2 = it2->second;
    BSTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      if (tree2.count(it->first) == 0) {
        result.push(it->first, it->second);
      }
    }

    dict.push(newDataset, result);
  }
}

void zhitnyj::handleUnion(zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &dict) {
  std::string newDataset, dataset1, dataset2;
  std::cin >> newDataset >> dataset1 >> dataset2;

  auto it1 = dict.find(dataset1);
  auto it2 = dict.find(dataset2);
  if (it1 == dict.end() || it2 == dict.end()) {
    invalidCommandWarning(std::cout);
  }
  else {
    const auto &tree1 = it1->second;
    const auto &tree2 = it2->second;
    BSTree< long long, std::string > result;

    for (auto it = tree1.begin(); it != tree1.end(); ++it) {
      result.push(it->first, it->second);
    }

    for (auto it = tree2.begin(); it != tree2.end(); ++it) {
      if (result.count(it->first) == 0) {
        result.push(it->first, it->second);
      }
    }

    dict.push(newDataset, result);
  }
}

void zhitnyj::handlePrint(zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &dict) {
  std::string dataset;
  std::cin >> dataset;

  auto it = dict.find(dataset);
  const auto &tree = it->second;
  if (it == dict.end()) {
    invalidCommandWarning(std::cout);
  }
  else if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    std::cout << dataset;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
      std::cout << " " << it->first << " " << it->second;
    }
    std::cout << "\n";
  }
}

void zhitnyj::emptyCommandWarning(std::ostream &out) {
  out << "<EMPTY>\n";
}

void zhitnyj::invalidCommandWarning(std::ostream &out) {
  out << "<INVALID COMMAND>\n";
}
