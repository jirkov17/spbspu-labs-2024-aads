#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include <iostream>
#include <cstddef>
#include <utility>
#include <limits>
#include <cassert>
#include <iterator>
#include <memory>
#include "node.hpp"

namespace kovshikov
{
  template < typename T >
  class DoubleList
  {
  public:
    class Iterator;
    class ConstIterator;

    typedef T value_type;

    DoubleList(): head_(nullptr), tail_(nullptr) {};
    DoubleList(const DoubleList& dl);
    DoubleList(DoubleList&& dl);
    DoubleList(size_t size, const T &value);
    ~DoubleList();

    DoubleList<T>& operator=(const DoubleList<T>& dl);
    DoubleList<T>& operator=(DoubleList&& dl);

    T& front() const;
    T& back() const;

    bool empty() const noexcept;
    size_t size() const;

    void pushFront(const T &value);
    void pushBack(const T& value);
    void popFront() noexcept;
    void popBack() noexcept;

    void push_front(const T &value);
    void push_back(const T& value);
    void pop_front() noexcept;
    void pop_back() noexcept;

    void clear() noexcept;
    void swap(DoubleList& dl) noexcept;
    void remove(const T &value);
    template< class Predicate >
    void remove_if(Predicate pred);
    void assign(size_t size, const T &value);

    Iterator begin() const;
    Iterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    details::Node< T >* head_;
    details::Node< T >* tail_;
  };
}

template< typename T >
class kovshikov::DoubleList< T >::Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class DoubleList< T >;
  using this_t = Iterator;

  Iterator(): node(nullptr) {};
  Iterator(const this_t &) = default;
  Iterator(details::Node< T >* ptr): node(ptr) {};
  ~Iterator() = default;

  this_t & operator=(const this_t &) = default;

  this_t & operator++();
  this_t operator++(int);

  this_t & operator--();
  this_t operator--(int);

  bool operator!=(const this_t & other) const;
  bool operator==(const this_t & other) const;

  T & operator*();
  T * operator->();
private:
  details::Node< T >* node;
};

template< typename T >
typename kovshikov::DoubleList< T >::Iterator::this_t & kovshikov::DoubleList< T >::Iterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< typename T >
typename kovshikov::DoubleList< T >::Iterator::this_t kovshikov::DoubleList< T >::Iterator::operator++(int)
{
  assert(node != nullptr);
  this_t result(*this);
  ++(*this);
  return result;
}

template< typename T >
typename kovshikov::DoubleList< T >::Iterator::this_t & kovshikov::DoubleList< T >::Iterator::operator--()
{
  assert(node != nullptr);
  node = node->prev;
  return *this;
}

template< typename T >
typename kovshikov::DoubleList< T >::Iterator::this_t kovshikov::DoubleList< T >::Iterator::operator--(int)
{
  assert(node != nullptr);
  this_t result(*this);
  --(*this);
  return result;
}

template< typename T >
bool kovshikov::DoubleList< T >::Iterator::operator==(const this_t & other) const
{
  return node == other.node;
}

template< typename T >
bool kovshikov::DoubleList< T >::Iterator::operator!=(const this_t & other) const
{
  return !(other == *this);
}

template< typename T >
T & kovshikov::DoubleList< T >::Iterator::operator*()
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
T * kovshikov::DoubleList< T >::Iterator::operator->()
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template < typename T >
class kovshikov::DoubleList< T >::ConstIterator : public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class DoubleList< T >;
  using this_t = ConstIterator;

  ConstIterator(): iterator(nullptr) {};
  ConstIterator(const this_t&) = default;
  ConstIterator(Iterator iter): iterator(iter) {};
  ~ConstIterator() = default;

  this_t & operator=(const this_t &) = default;

  this_t & operator++();
  this_t operator++(int);

  this_t & operator--();
  this_t operator--(int);

  bool operator!=(const this_t & other) const;
  bool operator==(const this_t & other) const;

  const T & operator*() const;
  const T * operator->() const;
private:
  Iterator iterator;
};

template< typename T >
typename kovshikov::DoubleList< T >::ConstIterator::this_t & kovshikov::DoubleList< T >::ConstIterator::operator++()
{
  assert(iterator != nullptr);
  iterator++;
  return iterator;
}

template< typename T >
typename kovshikov::DoubleList< T >::ConstIterator::this_t kovshikov::DoubleList< T >::ConstIterator::operator++(int)
{
  assert(iterator != nullptr);
  ++iterator;
  return iterator;
}

template< typename T >
typename kovshikov::DoubleList< T >::ConstIterator::this_t & kovshikov::DoubleList< T >::ConstIterator::operator--()
{
  assert(iterator != nullptr);
  iterator--;
  return iterator;
}

template< typename T >
typename kovshikov::DoubleList< T >::ConstIterator::this_t kovshikov::DoubleList< T >::ConstIterator::operator--(int)
{
  assert(iterator != nullptr);
  --iterator;
  return iterator;
}

template< typename T >
bool kovshikov::DoubleList< T >::ConstIterator::operator==(const this_t & other) const
{
  return iterator == other;
}

template< typename T >
bool kovshikov::DoubleList< T >::ConstIterator::operator!=(const this_t & other) const
{
  return !(other == iterator);
}

template< typename T >
const T & kovshikov::DoubleList< T >::ConstIterator::operator*() const
{
  assert(iterator != nullptr);
  return iterator.node->data;
}

template< typename T >
const T * kovshikov::DoubleList< T >::ConstIterator::operator->() const
{
  assert(iterator != nullptr);
  return std::addressof(iterator.node->data);
}

template< typename T >
kovshikov::DoubleList< T >::DoubleList(size_t size, const T &value)
{
  head_ = nullptr;
  tail_ = nullptr;
  for(size_t i = 0; i < size; i++)
  {
    this->pushBack(value);
  }
}

template < typename T >
kovshikov::DoubleList< T >::~DoubleList()
{
  clear();
}

template < typename T >
kovshikov::DoubleList< T >::DoubleList(const DoubleList& dl)
{
  this->head_ = nullptr;
  this->tail_ = nullptr;
  details::Node< T > *temp = dl.head_;
  while(temp != nullptr)
  {
    this->pushBack(temp->data);
    temp = temp->next;
  }
}

template < typename T >
kovshikov::DoubleList< T >& kovshikov::DoubleList< T >::operator=(const DoubleList& dl)
{
  DoubleList< T > newDl(dl);
  this->swap(newDl);
  return *this;
}

template < typename T >
kovshikov::DoubleList< T >::DoubleList(DoubleList&& dl)
{
  this->head_ = nullptr;
  this->tail_ = nullptr;
  details::Node< T > *temp = std::move(dl.head_);
  while(temp != nullptr)
  {
    this->pushBack(std::move(temp->data));
    temp = temp->next;
  }
}

template< typename T >
kovshikov::DoubleList< T >& kovshikov::DoubleList< T >::operator=(DoubleList&& dl)
{
  this->clear();
  details::Node< T > *temp = std::move(dl.head_);
  while(temp != nullptr)
  {
    this->pushBack(std::move(temp->data));
    temp = temp->next;
  }
  return *this;
}

template < typename T >
T& kovshikov::DoubleList< T >::front() const
{
  return head_->data;
}

template < typename T >
T& kovshikov::DoubleList< T >::back() const
{
  return tail_->data;
}

template < typename T >
bool kovshikov::DoubleList< T >::empty() const noexcept
{
  return (head_ == nullptr && tail_ == nullptr) ? true : false;
}

template < typename T >
size_t kovshikov::DoubleList< T >::size() const
{
  size_t size = 0;
  Iterator current = begin();
  while(current != end())
  {
    size += 1;
    current++;
  }
  return size;
}

template < typename T >
void kovshikov::DoubleList< T >::pushFront(const T &value)
{
  details::Node< T >* newNode = new details::Node< T >(value);
  if (this->empty() == true)
  {
    head_ = newNode;
    tail_ = newNode;
  }
  else
  {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  }
}

template < typename T >
void kovshikov::DoubleList< T >::pushBack(const T& value)
{
  details::Node< T >* newNode = new details::Node< T >(value);
  if (this->empty() == true)
  {
    head_ = newNode;
    tail_ = newNode;
  }
  else
  {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }
}

template < typename T >
void kovshikov::DoubleList< T >::popFront() noexcept
{
  if(head_ != nullptr && tail_ != nullptr)
  {
    details::Node< T >* temp = head_->next;
    delete head_;
    head_ = temp;
    if(head_ == nullptr)
    {
      tail_ = nullptr;
    }
    else
    {
      head_->prev = nullptr;
    }
  }
}

template < typename T >
void kovshikov::DoubleList< T >::popBack() noexcept
{
  if(head_ != nullptr && tail_ != nullptr)
  {
    details::Node< T >* temp = tail_->prev;
    delete tail_;
    tail_ = temp;
    if(tail_ == nullptr)
    {
      head_ = nullptr;
    }
    else
    {
      tail_->next = nullptr;
    }
  }
}

template < typename T >
void kovshikov::DoubleList< T >::push_front(const T &value)
{
  pushFront(value);
}

template < typename T >
void kovshikov::DoubleList< T >::push_back(const T& value)
{
  pushBack(value);
}

template < typename T >
void kovshikov::DoubleList< T >::pop_front() noexcept
{
  popFront();
}

template < typename T >
void kovshikov::DoubleList< T >::pop_back() noexcept
{
  popBack();
}

template < typename T >
void kovshikov::DoubleList< T >::clear() noexcept
{
  while (head_ && tail_)
  {
    popFront();
  }
}

template < typename T >
void kovshikov::DoubleList< T >::swap(DoubleList& dl) noexcept
{
  details::Node< T >* tempHead = dl.head_;
  details::Node< T >* tempTail = dl.tail_;
  dl.head_ = this->head_;
  this->head_ = tempHead;
  dl.tail_ = this->tail_;
  this->tail_ = tempTail;
}

template< typename T >
void kovshikov::DoubleList< T >::remove(const T &value)
{
  Iterator iterator = this->begin();
  while(iterator != this->end())
  {
    if(iterator.node->data == value)
    {
      details::Node< T >* tempPrev = iterator.node->prev;
      details::Node< T >* tempNext = iterator.node->next;
      Iterator iteratorToDelete = iterator;
      if(head_ == tail_)
      {
        head_ = tail_ = nullptr;
      }
      else if(iterator.node == head_)
      {
        head_ = tempNext;
        tempNext->prev = nullptr;
      }
      else
      {
        tempPrev->next = tempNext;
        tempNext->prev = tempPrev;
      }
      delete iteratorToDelete.node;
    }
    iterator++;
   }
}

template< typename T >
template< class Predicate >
void kovshikov::DoubleList< T >::remove_if(Predicate pred)
{
  Iterator iterator = this->begin();
  while(iterator != this->end())
  {
    if(pred(iterator.node->data))
    {
      details::Node< T >* tempPrev = iterator.node->prev;
      details::Node< T >* tempNext = iterator.node->next;
      Iterator iteratorToDelete = iterator;
      if(head_ == tail_)
      {
        head_ = tail_ = nullptr;
      }
      else if(iterator.node == head_)
      {
        head_ = tempNext;
        tempNext->prev = nullptr;
      }
      else
      {
        tempPrev->next = tempNext;
        tempNext->prev = tempPrev;
      }
      delete iteratorToDelete.node;
    }
    iterator++;
   }
}

template< typename T >
void kovshikov::DoubleList< T >::assign(size_t size, const T &value)
{
  this->clear();
  for(size_t i = 0; i < size; i++)
  {
    this->pushBack(value);
  }
}

template< typename T >
typename kovshikov::DoubleList< T >::Iterator kovshikov::DoubleList< T >::begin() const
{
  return Iterator(head_);
}

template< typename T >
typename kovshikov::DoubleList< T >::Iterator kovshikov::DoubleList< T >::end() const
{
  if(this->empty())
  {
    return this->begin();
  }
  else
  {
    details::Node< T >* pastTheEnd = tail_->next;
    return Iterator(pastTheEnd);
  }
}

template< typename T >
typename kovshikov::DoubleList< T >::ConstIterator kovshikov::DoubleList< T >::cbegin() const
{
  return ConstIterator(head_);
}

template< typename T >
typename kovshikov::DoubleList< T >::ConstIterator kovshikov::DoubleList< T >::cend() const
{
  if(this->empty)
  {
    return this->cbegin();
  }
  else
  {
    details::Node< T >* pastTheEnd = tail_->next;
    return ConstIterator(pastTheEnd);
  }
}

#endif
