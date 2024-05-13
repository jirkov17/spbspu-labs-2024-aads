#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <cassert>
#include <memory>
#include <iostream>
#include "node.hpp"
namespace jirkov
{
  template < typename T >
  class List
  {
  public:
    class ConstIterator;
    class Iterator;

    List();
    List(size_t n, const T& value);
    List(const List< T >& otherList);
    List(List< T >&& otherList);
    ~List();

    void pushFront(const T& data);
    void pushBack(const T& data);
    void popFront();
    bool empty() noexcept;
    void clear();
    void swap(List< T >& otherList) noexcept;
    void assign(size_t n, const T& value);
    void remove(const T& value);
    template< typename P >
    void removeIf(P p);
    size_t getSize();
    T& front();
    T& back();

    ConstIterator operator[](const int index);

    Iterator begin() const;
    Iterator end() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;

  private:
    details::Node<T>* head_;
    details::Node<T>* tail_;
  };
}

template< typename T >
class jirkov::List< T >::ConstIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;

  ConstIterator();
  ConstIterator(jirkov::details::Node<T>* pointer);
  ConstIterator(const ConstIterator&) = default;
  ~ConstIterator() = default;

  ConstIterator& operator=(const ConstIterator&) = default;
  ConstIterator& operator++();
  ConstIterator operator++(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const ConstIterator& rhs) const;
  bool operator==(const ConstIterator& rhs) const;

private:
  jirkov::details::Node<T>* node;
};

template< typename T >
jirkov::List< T >::ConstIterator::ConstIterator():
  node(nullptr)
{}

template< typename T >
jirkov::List< T >::ConstIterator::ConstIterator(jirkov::details::Node<T>* pointer):
  node(pointer)
{}

template< typename T >
typename jirkov::List< T >::ConstIterator& jirkov::List< T >::ConstIterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< typename T >
typename jirkov::List< T >::ConstIterator jirkov::List< T >::ConstIterator::operator++(int)
{
  assert(node != nullptr);
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T& jirkov::List< T >::ConstIterator::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
const T* jirkov::List< T >::ConstIterator::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
bool jirkov::List< T >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return !(rhs == *this);
}

template< typename T >
bool jirkov::List< T >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return node == rhs.node;
}

template< typename T >
class jirkov::List< T >::Iterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;
  Iterator();
  Iterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  Iterator(ConstIterator someIterator);
  ~Iterator() = default;

  Iterator& operator++();
  Iterator operator++(int);

  T& operator*();
  T* operator->();

  bool operator!=(const Iterator& rhs) const;
  bool operator==(const Iterator& rhs) const;

private:
  ConstIterator iterator;
};

template< typename T >
jirkov::List< T >::Iterator::Iterator():
  iterator(nullptr)
{}

template< typename T >
jirkov::List< T >::Iterator::Iterator(ConstIterator someIterator):
  iterator(someIterator)
{}

template< typename T >
typename jirkov::List< T >::Iterator& jirkov::List< T >::Iterator::operator++()
{
    assert(iterator.node != nullptr);
    iterator = ConstIterator(iterator.node->next);
    return *this;
}
template< typename T >
typename jirkov::List< T >::Iterator jirkov::List< T >::Iterator::operator++(int)
{
    assert(iterator.node != nullptr);
    Iterator result(*this);
    iterator = ConstIterator(iterator.node->next);
    return result;
}
template< typename T >
T& jirkov::List< T >::Iterator::operator*()
{
  assert(iterator != nullptr);
  return iterator.node->data;
}

template< typename T >
T* jirkov::List< T >::Iterator::operator->()
{
  assert(iterator != nullptr);
  return std::addressof(iterator.node->data);
}

template< typename T >
bool jirkov::List< T >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(rhs.iterator == iterator);
}

template< typename T >
bool jirkov::List< T >::Iterator::operator==(const Iterator& rhs) const
{
  return iterator == rhs.iterator;
}

template< typename T >
jirkov::List< T >::List():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
jirkov::List< T >::List(size_t n, const T& value)
{
  head_ = nullptr;
  tail_ = nullptr;
  for (size_t i = 0; i < n; i++)
  {
    pushBack(value);
  }
}

template< typename T >
jirkov::List< T >::List(const List< T >& otherList)
{
  head_ = nullptr;
  tail_ = nullptr;
  jirkov::details::Node<T>* head = otherList.head_;
  while (head)
  {
    pushBack(head->data);
    head = head->next;
  }
}

template< typename T >
jirkov::List< T >::List(List&& otherList)
{
  head_ = otherList.head_;
  tail_ = otherList.tail_;
  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;
}

template< typename T >
jirkov::List< T >::~List()
{
  clear();
}

template< typename T >
void jirkov::List< T >::pushFront(const T& data)
{
  jirkov::details::Node<T>* node = new jirkov::details::Node<T>(data);
  if (head_ != nullptr)
  {
    node->next = head_;
    head_ = node;
  }
  else
  {
    head_ = tail_ = node;
  }
}

template< typename T >
void jirkov::List< T >::pushBack(const T& data)
{
  jirkov::details::Node<T>* node = nullptr;
  try
  {
    node = new jirkov::details::Node<T>(data);
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }
  if (head_ == nullptr)
  {
    head_ = tail_ = node;
  }
  else
  {
    tail_->next = node;
    tail_ = node;
  }
}

template< typename T >
size_t jirkov::List< T >::getSize()
{
  jirkov::details::Node<T>* head = head_;
  size_t size = 0ull;
  while (head)
  {
    size++;
    head = head->next;
  }
  return size;
}


template< typename T >
void jirkov::List< T >::popFront()
{
  if (head_ == tail_)
  {
    delete tail_;
    head_ = tail_ = nullptr;
  }
  if (head_ != nullptr)
  {
    jirkov::details::Node<T>* node = head_;
    head_ = node->next;
    delete node;
  }
}

template< typename T >
bool jirkov::List< T >::empty() noexcept
{
  return head_ == nullptr ? true : false;
}

template< typename T >
void jirkov::List< T >::clear()
{
  while (head_)
  {
    popFront();
  }
}

template< typename T >
void jirkov::List< T >::swap(List< T >& otherList) noexcept
{
  std::swap(head_, otherList.head_);
  std::swap(tail_, otherList.tail_);
}

template< typename T >
void jirkov::List< T >::assign(size_t n, const T& value)
{
  clear();
  for (size_t i = 0; i < n; i++)
  {
    push_back(value);
  }
}

template< typename T >
void jirkov::List< T >::remove(const T& value)
{
  ConstIterator iterator = cbegin();
  jirkov::details::Node<T>* nextNode = iterator.node->next;
  jirkov::details::Node<T>* toRemove = nullptr;
  if (!empty())
  {
    while (*iterator == value)
    {
      popFront();
      iterator = cbegin();
      nextNode = iterator.node->next;
    }
    while (nextNode)
    {
      if (nextNode->data == value)
      {
        if (nextNode->next == nullptr)
        {
          toRemove = nextNode;
          nextNode = nullptr;
          iterator.node->next = nullptr;
          tail_ = iterator.node;
          delete toRemove;
        }
        else
        {
          toRemove = nextNode;
          iterator.node->next = nextNode->next;
          nextNode = iterator.node->next;
          delete toRemove;
        }
      }
      else
      {
        iterator++;
        nextNode = iterator.node->next;
      }
    }
  }
}

template< typename T >
template< typename P >
void jirkov::List< T >::removeIf(P p)
{
  ConstIterator iterator = cbegin();
  jirkov::details::Node<T>* nextNode = iterator.node->next;
  jirkov::details::Node<T>* toRemove = nullptr;
  if (!empty())
  {
    while (p(*iterator))
    {
      popFront();
      iterator = cbegin();
      nextNode = iterator.node->next;
    }
    while (nextNode)
    {
      if (p(nextNode->data))
      {
        if (nextNode->next == nullptr)
        {
          toRemove = nextNode;
          nextNode = nullptr;
          iterator.node->next = nullptr;
          tail_ = iterator.node;
          delete toRemove;
        }
        else
        {
          toRemove = nextNode;
          iterator.node->next = nextNode->next;
          nextNode = iterator.node->next;
          delete toRemove;
        }
      }
      else
      {
        iterator++;
        nextNode = iterator.node->next;
      }
    }
  }
}

template< typename T >
T& jirkov::List< T >::front()
{
  return head_->data;
}

template< typename T >
T& jirkov::List< T >::back()
{
  return tail_->data;
}

template< typename T >
typename jirkov::List< T >::ConstIterator jirkov::List< T >::operator[](const int index)
{
  ConstIterator iterator = cbegin();
  for (int i = 0; i < index; i++)
  {
    if (iterator == nullptr)
    {
      return nullptr;
    }
    iterator++;
  }
  return iterator.node;
}

template< typename T >
typename jirkov::List< T >::Iterator jirkov::List< T >::begin() const
{
  return Iterator(head_);
}

template< typename T >
typename jirkov::List< T >::Iterator jirkov::List< T >::end() const
{
  return Iterator(nullptr);
}

template< typename T >
typename jirkov::List< T >::ConstIterator jirkov::List< T >::cbegin() const
{
  return ConstIterator(head_);
}

template< typename T >
typename jirkov::List< T >::ConstIterator jirkov::List< T >::cend() const
{
  return ConstIterator(tail_->next);
}

#endif
