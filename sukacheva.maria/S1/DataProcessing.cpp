#include "DataProcessing.hpp"
#include <string>
#include <utility>
#include <limits>
#include "List.hpp"

namespace sukacheva {

  using itListOfPairs = listOfPairs::Iterator;
  listOfPairs listInput(std::istream& in)
  {
    std::string name = "";
    List< size_t > args;
    listOfPairs resultList;
    in >> name;
    while (in) {
      resultList.pushBack({ name, args });
      while (in >> name && std::isdigit(name[0])) {
        resultList.back().second.pushBack(std::stoul(name));
      }
    }
    return resultList;
  }

  size_t maxListSize(listOfPairs& newList)
  {
    size_t size = 0;
    size_t maxSize = 0;
    itListOfPairs it = newList.begin();
    while (it != nullptr) {
      size = it->second.getSize();
      maxSize = (maxSize < size ? size : maxSize);
      it++;
    }
    return maxSize;
  }

  void printNameList(listOfPairs& newList)
  {
    itListOfPairs it = newList.begin();
    do {
      if (it != newList.begin()) {
        std::cout << " ";
      }
      std::cout << it->first;
      it++;
    } while (it != nullptr);
    std::cout << "\n";
  }

  void getSumsList(List< size_t >& sumOfArgs)
  {
    List< size_t >::Iterator itSum = sumOfArgs.begin();
    do {
      if (itSum != sumOfArgs.begin()) {
        std::cout << " ";
      }
      std::cout << *itSum;
      itSum++;
    } while (itSum != nullptr);
    std::cout << "\n";
  }

  void printArgs(listOfPairs& newList, bool& overflowFlag, List< size_t >& sumOfArgs)
  {
    itListOfPairs it = newList.begin();
    const size_t maxSum = std::numeric_limits< size_t >::max();
    for (size_t i = 0; i < maxListSize(newList); i++) {
      it = newList.begin();
      size_t sum = 0;
      while (it != nullptr) {
        List< size_t >::Iterator argsIt = it->second[i];
        if (it->second[i] != nullptr)
        {
          if (sum != 0) {
            std::cout << " ";
          }
          std::cout << *argsIt;
          if (sum > maxSum - *argsIt)
          {
            overflowFlag = true;
            std::cout << "\n";
            throw std::overflow_error("overflow!!");
          }
          else
          {
            sum += *argsIt;
          }
        }
        it++;
      }
      std::cout << "\n";
      sumOfArgs.pushBack(sum);
    }
  }
}
