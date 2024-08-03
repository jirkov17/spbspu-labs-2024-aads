#ifndef SORTOPERATIONS_HPP
#define SORTOPERATIONS_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <List.hpp>
#include "random.hpp"

namespace zhitnyj {
  template< typename T >
  void printList(const List< T > &list, std::ostream &os) {
    auto it = list.begin();
    while (it != list.end()) {
      os << *it;
      ++it;
      if (it != list.end()) {
        os << " ";
      }
    }
    std::cout << "\n";
  }

  template< typename T >
  void printStdList(const std::list< T > &list, std::ostream &os) {
    auto it = list.begin();
    while (it != list.end()) {
      os << *it;
      ++it;
      if (it != list.end()) {
        os << " ";
      }
    }
    std::cout << "\n";
  }

  template< typename T >
  void printDeque(const std::deque< T > &deq, std::ostream &os) {
    auto it = deq.begin();
    while (it != deq.end()) {
      os << *it;
      ++it;
      if (it != deq.end()) {
        os << " ";
      }
    }
    std::cout << "\n";
  }

  template< typename forwardIterator, typename Compare >
  void oddEvenSort(forwardIterator first, forwardIterator last, Compare comp) {
    bool sorted = false;
    while (!sorted) {
      sorted = true;
      for (auto it = first; it != last; ++it) {
        auto next = it;
        ++next;
        if (next != last && comp(*next, *it)) {
          std::swap(*it, *next);
          sorted = false;
        }
        if (next == last) {
          break;
        }
        ++it;
      }
      auto it = first;
      ++it;
      for (; it != last; ++it) {
        auto next = it;
        ++next;
        if (next != last && comp(*next, *it)) {
          std::swap(*it, *next);
          sorted = false;
        }
        if (next == last) {
          break;
        }
        ++it;
      }
    }
  }

  template< typename forwardIterator, typename Compare >
  void insertionSort(forwardIterator first, forwardIterator last, Compare comp) {
    if (first == last) {
      return;
    }
    for (auto it = std::next(first); it != last; ++it) {
      auto key = *it;
      auto j = it;
      while (j != first && comp(key, *std::prev(j))) {
        *j = *std::prev(j);
        --j;
      }
      *j = key;
    }
  }

  template< typename T, typename Compare >
  void stdSort(std::deque< T > &deq, Compare comp) {
    std::sort(deq.begin(), deq.end(), comp);
  }

  template< typename T, typename Compare >
  void printSort(List< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, Compare comp, std::ostream &os) {
    oddEvenSort(singleList.begin(), singleList.end(), comp);
    printList(singleList, os);

    insertionSort(doubleList.begin(), doubleList.end(), comp);
    printStdList(doubleList, os);
    printList(singleList, os);

    stdSort(deq, comp);
    printDeque(deq, os);
    printList(singleList, os);
    printStdList(doubleList, os);
  }

  template< typename T >
  void performSorts(List< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, bool ascending, std::ostream &os) {
    std::function< bool(const T &, const T &) > comp;
    if (ascending) {
      comp = std::less< T >();
    }
    else {
      comp = std::greater< T >();
    }

    printList(singleList, os);
    printSort(singleList, doubleList, deq, comp, os);
  }
}

#endif
