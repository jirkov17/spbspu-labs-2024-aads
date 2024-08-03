#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "list.hpp"
#include <memory>

namespace sobolevsky
{
  template< typename T >
  class BidirectionalIterator
  {
  public:
    Node< T > * currNode = nullptr;

    BidirectionalIterator(Node< T > * node);
    BidirectionalIterator(const BidirectionalIterator< T > &) = default;
    ~BidirectionalIterator() = default;
    std::string name();

    BidirectionalIterator< T > & operator=(const BidirectionalIterator< T > &) = default;
    BidirectionalIterator& operator++();
    BidirectionalIterator operator++(int);
    BidirectionalIterator& operator--();
    BidirectionalIterator operator--(int);

    bool operator!=(const BidirectionalIterator& other) const;
    bool operator==(const BidirectionalIterator& other) const;

    T & operator * ();
    T * operator->();
  };
}

template< typename T >
sobolevsky::BidirectionalIterator< T >::BidirectionalIterator(Node< T > * node)
{
  currNode = node;
}

template< typename T >
sobolevsky::BidirectionalIterator< T >& sobolevsky::BidirectionalIterator< T >::operator++()
{
  if (currNode)
  {
    currNode = currNode->next;
  }
  return *this;
}

template<typename T>
sobolevsky::BidirectionalIterator<T> sobolevsky::BidirectionalIterator< T >::operator++(int)
{
  sobolevsky::BidirectionalIterator< T > temp(*this);
  operator++();
  return temp;
}

template< typename T >
sobolevsky::BidirectionalIterator< T >& sobolevsky::BidirectionalIterator< T >::operator--()
{
  if (currNode)
  {
    currNode = currNode->prev;
  }
  return *this;
}

template<typename T>
sobolevsky::BidirectionalIterator<T> sobolevsky::BidirectionalIterator< T >::operator--(int)
{
  sobolevsky::BidirectionalIterator< T > temp(*this);
  operator--();
  return temp;
}

template< typename T >
bool sobolevsky::BidirectionalIterator< T >::operator!=(const BidirectionalIterator& other) const
{
  return currNode != other.currNode;
}

template< typename T >
bool sobolevsky::BidirectionalIterator< T >::operator==(const BidirectionalIterator& other) const
{
  return currNode == other.currNode;
}

template< typename T >
T & sobolevsky::BidirectionalIterator< T >::operator * ()
{
  return currNode->data;
}

template< typename T >
T * sobolevsky::BidirectionalIterator< T >::operator->()
{
  return std::addressof(currNode->data);
}

template< typename T >
std::string sobolevsky::BidirectionalIterator< T >::name()
{
  return currNode->name;
}

namespace sobolevsky
{
  template< typename T >
  class ConstBidirectionalIterator
  {
  public:
    ConstBidirectionalIterator(Node< T > * node);
    ConstBidirectionalIterator(const ConstBidirectionalIterator< T > &) = default;
    ~ConstBidirectionalIterator() = default;

    ConstBidirectionalIterator< T > & operator=(const ConstBidirectionalIterator< T > &) = default;

    ConstBidirectionalIterator& operator++();
    ConstBidirectionalIterator operator++(int);
    ConstBidirectionalIterator& operator--();
    ConstBidirectionalIterator operator--(int);

    bool operator!=(const ConstBidirectionalIterator& other) const;
    bool operator==(const ConstBidirectionalIterator& other) const;

    T & operator * ();
    T * operator->();

    std::string name();
  private:
    Node< T > * currNode = nullptr;
  };
}

template< typename T >
sobolevsky::ConstBidirectionalIterator< T >::ConstBidirectionalIterator(Node< T > * node)
{
  currNode = node;
}

template< typename T >
sobolevsky::ConstBidirectionalIterator< T >& sobolevsky::ConstBidirectionalIterator< T >::operator++()
{
  if (currNode)
  {
    currNode = currNode->next;
  }
  return *this;
}

template<typename T>
sobolevsky::ConstBidirectionalIterator<T> sobolevsky::ConstBidirectionalIterator< T >::operator++(int)
{
  sobolevsky::ConstBidirectionalIterator< T > temp(*this);
  operator++();
  return temp;
}

template< typename T >
sobolevsky::ConstBidirectionalIterator< T >& sobolevsky::ConstBidirectionalIterator< T >::operator--()
{
  if (currNode)
  {
    currNode = currNode->prev;
  }
  return *this;
}

template<typename T>
sobolevsky::ConstBidirectionalIterator<T> sobolevsky::ConstBidirectionalIterator< T >::operator--(int)
{
  sobolevsky::ConstBidirectionalIterator< T > temp(*this);
  operator--();
  return temp;
}

template< typename T >
bool sobolevsky::ConstBidirectionalIterator< T >::operator!=(const ConstBidirectionalIterator& other) const
{
  return currNode != other.currNode;
}

template< typename T >
bool sobolevsky::ConstBidirectionalIterator< T >::operator==(const ConstBidirectionalIterator& other) const
{
  return currNode == other.currNode;
}

template< typename T >
T & sobolevsky::ConstBidirectionalIterator< T >::operator * ()
{
  return currNode->data;
}

template< typename T >
T * sobolevsky::ConstBidirectionalIterator< T >::operator->()
{
  return std::addressof(currNode->data);
}

template< typename T >
std::string sobolevsky::ConstBidirectionalIterator< T >::name()
{
  return currNode->name;
}

#endif
