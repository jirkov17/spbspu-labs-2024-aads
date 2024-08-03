#include "IOProcessing.hpp"
#include <limits>

std::pair<miheev::SI_pair*, size_t> miheev::expandArr(SI_pair* pairs, size_t size)
{
    const size_t additionalSize = 5;
    miheev::SI_pair* copy = new SI_pair[size + additionalSize];
    for (size_t i = 0; i < size; i++)
    {
      copy[i] = pairs[i];
    }
    size += additionalSize;
    std::pair< miheev::SI_pair*, size_t > result(copy, size);
    return result;
}

std::string takeWord(std::string& line)
{
  size_t spaceIndex = line.find(' ');
  std::string word = line.substr(0, spaceIndex);
  line = spaceIndex == std::string::npos ? "" : line.substr(spaceIndex + 1);
  return word;
}

miheev::List< size_t > readNumbers(std::string numbers)
{
  miheev::List< size_t > list;
  size_t curNum = 0;

  while (numbers.length() > 0)
  {
    try
    {
      curNum = std::stoull(takeWord(numbers));
    }
    catch(const std::invalid_argument& err)
    {
      return list;
    }
    list.pushBack(curNum);
  }

  return list;
}

miheev::SI_pair miheev::getSIPair(std::istream& stream)
{
  miheev::SI_pair pair;
  std::string line = "";
  std::getline(stream, line);
  pair.first = takeWord(line);

  pair.second = readNumbers(line);
  return pair;
}

miheev::ListIter* miheev::getNonEmptyIters(miheev::SI_pair* pairs, size_t size)
{
  miheev::ListIter* iters = new ListIter[size];
  for (size_t i = 0; i < size; i++)
  {
    if (!pairs[i].second.empty())
    {
      iters[i] = miheev::ListIter(pairs[i].second.begin());
    }
  }
  return iters;
}

miheev::List< size_t >* getLists(miheev::SI_pair* pairs, size_t size)
{
  miheev::List< size_t >* lists = new miheev::List< size_t > [size];
  for (size_t i = 0; i < size; i++)
  {
    lists[i] = pairs[i].second;
  }
  return lists;
}

size_t miheev::maxListSize(List< size_t >* lists, size_t size)
{
  size_t max = lists[0].size();
  for (size_t i = 0; i < size; i++)
  {
    List< size_t > list = lists[i];
    size_t size = list.size();
    if (size > max)
    {
      max = size;
    }
  }
  return max;
}

size_t miheev::calcMaxListSize(miheev::SI_pair* pairs, size_t unusedIndex)
{
  List< size_t >* lists = getLists(pairs, unusedIndex);
  size_t maxSize = maxListSize(lists, unusedIndex);
  delete[] lists;
  return maxSize;
}

bool miheev::calcSumsArr(miheev::SI_pair* pairs, size_t unusedIndex, size_t* accumulator)
{
  size_t index = 0;
  bool isOverflow = false;
  miheev::ListIter* iters = getNonEmptyIters(pairs, unusedIndex);

  bool flag = false;
  do
  {
    flag = false;
    bool isFirstToPrint = true;
    for (size_t i = 0; i < unusedIndex; i++)
    {
      miheev::ListIter iter = iters[i];
      if (iter != nullptr)
      {
        if (!isOverflow && std::numeric_limits<size_t>::max() - *iter >= accumulator[index])
        {
          accumulator[index] += *iter;
        }
        else
        {
          isOverflow = true;
        }
        if (iter)
        {
          flag = true;
        }
        if (!isFirstToPrint)
        {
          std::cout << ' ';
        }
        std::cout << *iter;
        isFirstToPrint = false;
        iters[i] = ++iter;
      }
    }
    index++;
    std::cout << '\n';
  } while (flag);
  delete[] iters;
  return isOverflow;
}

void miheev::printSums(size_t* sums, size_t size, bool isOverflow)
{
  if (!isOverflow)
  {
    pPrint(sums, size);
  }
  if (isOverflow)
  {
    throw std::runtime_error("sum is bigger than size_t can contain\n");
  }
}
