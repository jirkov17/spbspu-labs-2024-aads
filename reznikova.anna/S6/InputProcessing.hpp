#ifndef INPUTPROCESSING_HPP
#define INPUTPROCESSING_HPP
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <forward_list>
#include <deque>
#include "List.hpp"
#include "Sort.hpp"

namespace reznikova
{
  void wrongInputOutput(std::ostream & out);
  void sortErrorOutput(std::ostream & out);
  template< typename T >
  void getRandVals(size_t size, std::string type, List< T > & biList, std::forward_list< T > & fList, std::deque< T > & queue);
  template< typename T >
  void outputVals(std::ostream & out, T & conteiner);
  template< typename T, typename Compare >
  void sortData(std::ostream & out, std::string type, size_t size, Compare cmp);
}

void reznikova::wrongInputOutput(std::ostream & out)
{
  out << "<WRONG INPUT>\n";
}

void reznikova::sortErrorOutput(std::ostream & out)
{
  out << "<SORT ERROR>\n";
}

template< typename T >
void reznikova::getRandVals(size_t size, std::string type, List< T > & biList, std::forward_list< T > & fList, std::deque< T > & queue)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   for (size_t i = 0; i < size; ++i)
   {
     if (type == "ints")
     {
       std::uniform_int_distribution< int > dis(-10000, 10000);
       int value = dis(gen);
       fList.push_front(value);
       biList.pushBack(value);
       queue.push_back(value);
     }
     else if (type == "floats")
     {
       std::uniform_real_distribution< float > dis(0.0f, 99.9f);
       float value = dis(gen);
       fList.push_front(value);
       biList.pushBack(value);
       queue.push_back(value);
     }
   }
 }

template< typename T >
void reznikova::outputVals(std::ostream & out, T & conteiner)
{
  auto it = conteiner.begin();
  out << *it;
  it++;
  while (it != conteiner.end())
  {
    out << " ";
    out << *it;
    it++;
  }
  out << "\n";
}

template< typename T, typename Compare >
void reznikova::sortData(std::ostream & out, std::string type, size_t size, Compare cmp)
{
  List< T > biList;
  std::forward_list< T > fList;
  std::deque< T > queue;
  getRandVals(size, type, biList, fList, queue);
  List< T > second_biList(biList);
  std::deque< T > second_queue(queue);
  std::deque< T > third_queue(queue);

  outputVals(out, queue);

  shaker(second_biList.begin(), second_biList.end(), cmp);
  outputVals(out, second_biList);
  qsort(biList.begin(), biList.end(), cmp);
  outputVals(out, biList);
  qsort(fList.begin(), fList.end(), cmp);
  outputVals(out, fList);
  qsort(queue.begin(), queue.end(), cmp);
  outputVals(out, queue);
  shaker(second_queue.begin(), second_queue.end(), cmp);
  outputVals(out, second_queue);
  std::sort(third_queue.begin(), third_queue.end(), cmp);
  outputVals(out, third_queue);
}

#endif
