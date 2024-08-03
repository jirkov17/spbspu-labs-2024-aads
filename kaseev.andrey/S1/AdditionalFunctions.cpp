#include "AdditionalFunctions.hpp"
#include <iostream>
#include <limits>

namespace kaseev {
  void readList(const std::string &line, kaseev::List< ULL_ListPair > &arr, bool &marker)
  {
    std::string ListName;
    size_t space_pos = line.find(' ');
    ListName = line.substr(0, space_pos);
    kaseev::List< unsigned long long > tempList;
    size_t start_pos = space_pos + 1;
    while (start_pos < line.size())
    {
      size_t next_space_pos = line.find(' ', start_pos);
      if (next_space_pos == std::string::npos)
      {
        next_space_pos = line.size();
      }
      std::string num_str = line.substr(start_pos, next_space_pos - start_pos);
      unsigned long long num;
      bool NoNumbers = false;
      num = convertToULL(num_str, NoNumbers);
      if (num > std::numeric_limits< int >::max())
      {
        marker = true;
      }
      if (!NoNumbers)
      {
        tempList.pushBack(num);
      }
      start_pos = next_space_pos + 1;
    }

    std::pair< std::string, kaseev::List< unsigned long long > > list_pair;
    list_pair.first = ListName;
    list_pair.second = kaseev::List < unsigned long long >(tempList);
    arr.pushBack(list_pair);
  }

  unsigned long long sumNumbersInString(const std::string &line)
  {
    unsigned long long sum = 0;
    size_t start_pos = 0;
    while (start_pos < line.size())
    {
      size_t next_space_pos = line.find(' ', start_pos);
      if (next_space_pos == std::string::npos)
      {
        next_space_pos = line.size();
      }
      std::string num_str = line.substr(start_pos, next_space_pos - start_pos);
      long long num;
      num = std::stoll(num_str);
      if (sum > std::numeric_limits< unsigned long long >::max() - num)
      {
        std::cerr << "overflow\n";
      }
      sum += num;
      start_pos = next_space_pos + 1;
    }
    return sum;
  }

  void sumNumbersInArray(const kaseev::List< IntListPair > &sums, bool &marker)
  {
    if (!marker)
    {
      for (int i = 0; i < sums.size(); ++i)
      {
        const auto &pair = sums[i];
        const std::string &line = pair.first;
        unsigned long long sum = 0;
        sum = sumNumbersInString(line);
        std::cout << sum;
        if (i < sums.size() - 1)
        {
          std::cout << " ";
        }
      }
      std::cout << "\n";
    }
  }

  void printListNames(const kaseev::List< ULL_ListPair > &arr)
  {
    bool marker = false;
    for (int i = 0; i < arr.size(); ++i)
    {
      ULL_ListPair list = arr[i];
      std::cout << list.first;
      if (i < arr.size() - 1)
      {
        std::cout << " ";
        marker = true;
      }
    }
    if (marker || !(arr.empty()))
    {
      std::cout << "\n";
    }
  }

  kaseev::List< IntListPair > calculateSumList(const kaseev::List< ULL_ListPair > &arr)
  {
    bool finished = false;
    int index = 0;
    kaseev::List< IntListPair > sum;
    int IfSumEmpty = 0;
    while (!finished)
    {
      finished = true;
      std::string currentString;
      for (int i = 0; i < arr.size(); ++i)
      {
        const kaseev::List< unsigned long long > &sublist = arr[i].second;
        if (index < sublist.size())
        {
          if (!currentString.empty())
          {
            currentString += " ";
          }
          currentString += std::to_string(sublist[index]);
          finished = false;
        }
      }

      if (!finished)
      {
        std::cout << currentString << "\n";
        sum.pushBack({currentString, kaseev::List< int >()});
      }
      index++;
    }
    if (sum.empty())
    {
      sum.pushBack({"", List< int >{IfSumEmpty}});
    }
    return sum;
  }

  unsigned long long convertToULL(const std::string &str, bool &NoNumbers) noexcept
  {
    if (str.empty() || str.find_first_not_of("0123456789") != std::string::npos)
    {
      NoNumbers = true;
      return 0;
    }
    return std::stoull(str);
  }
}
