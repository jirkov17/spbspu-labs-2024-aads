#ifndef MAINEXTENSION_HPP
#define MAINEXTENSION_HPP

#include <iostream>
#include <random>
#include <deque>
#include <forward_list>
#include <list.hpp>

namespace anikanov {
  template< typename T, typename Comparator >
  void processData(Comparator comp, size_t size);
  template< typename T >
  void generateRandomData(std::forward_list< T > &fwd, List < T > &list, std::deque< T > &deq, size_t size);
  template< typename T, typename Comparator >
  void fwdSort(std::forward_list< T > &fwd, Comparator comp);
  template< typename BidirectionalIterator, typename Comparator >
  void shakerSort(BidirectionalIterator first, BidirectionalIterator last, Comparator comp);
  template< typename RandomAccessIterator, typename Comparator >
  void mergeSort(RandomAccessIterator first, RandomAccessIterator last, Comparator comp);
  template< typename T, typename Comparator >
  void applySort(std::forward_list< T > &fwd, List < T > &list, std::deque< T > &deq, Comparator comp, std::ostream &os);
  template< typename Container >
  void printContainer(std::ostream &os, const Container &container);
  void printUsingError(std::ostream &os);
  void printInvalidCount(std::ostream &os);
  void printInvalidType(std::ostream &os);
}

template< typename T, typename Comparator >
void anikanov::processData(Comparator comp, size_t size)
{
  std::forward_list< T > fwd;
  List < T > list;
  std::deque< T > deq;

  generateRandomData(fwd, list, deq, size);
  printContainer(std::cout, fwd);
  applySort(fwd, list, deq, comp, std::cout);
}

template< typename T >
void anikanov::generateRandomData(std::forward_list< T > &fwd, List < T > &list, std::deque< T > &deq, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    auto value = static_cast< T >(std::rand() % 100 +
                                  ((std::is_floating_point< T >::value) ? std::rand() % 100 / 100.0 : 0));
    fwd.push_front(value);
    list.push_back(value);
    deq.push_back(value);
  }
}

template< typename Container >
void anikanov::printContainer(std::ostream &os, const Container &container)
{
  for (auto i = container.begin(); i != container.end(); ++i) {
    os << *i;
    auto j = i;
    if (++j != container.end()) {
      os << " ";
    }
  }
  std::cout << "\n";
}

template< typename T, typename Comparator >
void anikanov::fwdSort(std::forward_list< T > &fwd, Comparator comp)
{
  fwd.sort(comp);
}

template< typename BidirectionalIterator, typename Comparator >
void anikanov::shakerSort(BidirectionalIterator first, BidirectionalIterator last, Comparator comp)
{
  if (first == last) return;
  auto begin = first;
  auto end = last;
  --end;

  bool swapped = true;
  while (swapped) {
    swapped = false;

    for (auto it = begin; it != end; ++it) {
      auto next = it;
      ++next;
      if (next == end) {
        break;
      }
      if (comp(*next, *it)) {
        std::iter_swap(it, next);
        swapped = true;
      }
    }

    if (!swapped) break;

    --end;

    swapped = false;

    auto back = begin;
    while (back + 1 != end) {
      ++back;
    }

    for (auto it = back; it != begin; --it) {
      auto prev = it;
      --prev;
      if (comp(*it, *prev)) {
        std::iter_swap(it, prev);
        swapped = true;
      }
    }

    ++begin;
  }
}

template< typename RandomAccessIterator, typename Comparator >
void anikanov::mergeSort(RandomAccessIterator first, RandomAccessIterator last, Comparator comp)
{
  auto distance = std::distance(first, last);
  if (distance <= 1) return;

  auto mid = first;
  std::advance(mid, distance / 2);

  mergeSort(first, mid, comp);
  mergeSort(mid, last, comp);

  using ValueType = typename std::iterator_traits< RandomAccessIterator >::value_type;
  List < ValueType > buffer;
  RandomAccessIterator left = first;
  RandomAccessIterator right = mid;

  while (left != mid && right != last) {
    if (comp(*left, *right)) {
      buffer.push_back(*left);
      ++left;
    } else {
      buffer.push_back(*right);
      ++right;
    }
  }

  while (left != mid) {
    buffer.push_back(*left);
    ++left;
  }

  while (right != last) {
    buffer.push_back(*right);
    ++right;
  }

  auto buf_it = buffer.begin();
  for (auto it = first; it != last; ++it, ++buf_it) {
    *it = *buf_it;
  }
}

template< typename T, typename Comparator >
void
anikanov::applySort(std::forward_list< T > &fwd, List < T > &list, std::deque< T > &deq, Comparator comp,
                    std::ostream &os)
{
  fwdSort(fwd, comp);
  printContainer(os, fwd);
  shakerSort(list.begin(), list.end(), comp);
  printContainer(os, fwd);
  printContainer(os, list);
  mergeSort(deq.begin(), deq.end(), comp);
  printContainer(os, fwd);
  printContainer(os, list);
  printContainer(os, deq);
}

#endif
