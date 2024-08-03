#include "mainExtensions.hpp"
#include <iostream>

anikanov::List< std::string > anikanov::split(const std::string &str)
{
  anikanov::List< std::string > list;
  std::string cur = "";
  for (char pos: str) {
    if (pos != ' ') {
      cur += pos;
    } else if (!cur.empty()) {
      list.push_back(cur);
      cur = "";
    }
  }
  if (!cur.empty()) {
    list.push_back(cur);
  }
  return list;
}

void anikanov::inputList(std::unique_ptr< mainList > &lists, std::istream &stream)
{
  std::string inputName;
  std::string line;

  line = "";
  std::getline(stream, line);
  while (!stream.eof()) {
    if (line.empty()) {
      line = "";
      std::getline(stream, line);
      continue;
    }
    List< std::string > inputList = split(line);
    anikanov::list numbers;
    inputName = inputList[0];
    inputList.pop(0);
    for (auto &i: inputList) {
      numbers.push_back(std::stoull(i));
    }

    std::pair< std::string, List< unsigned long long > > listPair;
    listPair.first = inputName;
    for (auto num: numbers) {
      listPair.second.push_back(num);
    }
    lists->push_back(listPair);
    line = "";
    std::getline(stream, line);
  }
}

bool anikanov::printNames(const std::unique_ptr< mainList > &lists, std::ostream &cout)
{
  for (auto it = lists->begin(); it != lists->end();) {
    std::cout << it->first;
    if (++it != lists->end()) {
      cout << " ";
    }
  }

  if (lists->empty()) {
    cout << "0\n";
    return 0;
  } else {
    std::cout << "\n";
  }
  return 1;
}

anikanov::getSums anikanov::countList(const std::unique_ptr< mainList > &lists, std::ostream &cout)
{
  bool finished = false;
  bool startPrint = false;
  size_t idx = 0;
  List< unsigned long long > sums;
  bool badSum = false;

  while (!finished) {
    finished = true;
    startPrint = true;
    for (auto listIter = lists->begin(); listIter != lists->end(); ++listIter) {
      const auto &list = *listIter;
      if (idx < list.second.size()) {
        if (finished) {
          sums.push_back(0);
          finished = false;
        }
        auto numIter = list.second.begin();
        for (size_t i = 0; i < idx; ++i) {
          numIter++;
        }
        if (startPrint) {
          cout << *numIter;
          startPrint = false;
        } else {
          cout << " " << *numIter;
        }
        if (*sums.back() + *numIter < std::max(*sums.back(), *numIter)) {
          badSum = true;
        }
        *sums.back() += *numIter;
      }
    }
    cout << (finished ? "" : "\n");
    idx++;
  }

  return std::make_pair(sums, badSum);
}

void anikanov::printList(const list &sums, std::ostream &cout)
{
  for (auto sumIter = sums.begin(); sumIter != sums.end();) {
    cout << *sumIter;
    if (++sumIter != sums.end()) {
      cout << " ";
    }
  }

  if (sums.empty()) {
    cout << "0";
  }
}
