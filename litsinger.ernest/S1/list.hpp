#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <cassert>
#include <memory>
#include <iostream>

namespace litsinger
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
    bool isEmpty() noexcept;
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
    struct Node
    {
    public:
      friend class List;
      Node(T value) :
        data(value),
        next(nullptr)
      {}
    private:
      T data;
      Node* next;
    };

    Node* head_;
    Node* tail_;
  };
}

template< typename T >
class litsinger::List< T >::ConstIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class List< T >;

  ConstIterator();
  ConstIterator(Node* pointer);
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
  Node* node;
};

template< typename T >
litsinger::List< T >::ConstIterator::ConstIterator():
  node(nullptr)
{}

template< typename T >
litsinger::List< T >::ConstIterator::ConstIterator(Node* pointer):
  node(pointer)
{}

template< typename T >
typename litsinger::List< T >::ConstIterator& litsinger::List< T >::ConstIterator::operator++()
{
  assert(node != nullptr);
  node = node->next;
  return *this;
}

template< typename T >
typename litsinger::List< T >::ConstIterator litsinger::List< T >::ConstIterator::operator++(int)
{
  assert(node != nullptr);
  ConstIterator result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T& litsinger::List< T >::ConstIterator::operator*() const
{
  assert(node != nullptr);
  return node->data;
}

template< typename T >
const T* litsinger::List< T >::ConstIterator::operator->() const
{
  assert(node != nullptr);
  return std::addressof(node->data);
}

template< typename T >
bool litsinger::List< T >::ConstIterator::operator!=(const ConstIterator& rhs) const
{
  return !(rhs == *this);
}

template< typename T >
bool litsinger::List< T >::ConstIterator::operator==(const ConstIterator& rhs) const
{
  return node == rhs.node;
}

template< typename T >
class litsinger::List< T >::Iterator : public std::iterator< std::forward_iterator_tag, T >
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
litsinger::List< T >::Iterator::Iterator():
  iterator(nullptr)
{}

template< typename T >
litsinger::List< T >::Iterator::Iterator(ConstIterator someIterator):
  iterator(someIterator)
{}

template< typename T >
typename litsinger::List< T >::Iterator& litsinger::List< T >::Iterator::operator++()
{
  assert(iterator != nullptr);
  iterator++;
  return iterator;
}

template< typename T >
typename litsinger::List< T >::Iterator litsinger::List< T >::Iterator::operator++(int)
{
  assert(iterator != nullptr);
  ++iterator;
  return iterator;
}

template< typename T >
T& litsinger::List< T >::Iterator::operator*()
{
  assert(iterator != nullptr);
  return iterator.node->data;
}

template< typename T >
T* litsinger::List< T >::Iterator::operator->()
{
  assert(iterator != nullptr);
  return std::addressof(iterator.node->data);
}

template< typename T >
bool litsinger::List< T >::Iterator::operator!=(const Iterator& rhs) const
{
  return !(rhs.iterator == iterator);
}

template< typename T >
bool litsinger::List< T >::Iterator::operator==(const Iterator& rhs) const
{
  return iterator == rhs.iterator;
}

template< typename T >
litsinger::List< T >::List():
  head_(nullptr),
  tail_(nullptr)
{}

template< typename T >
litsinger::List< T >::List(size_t n, const T& value)
{
  head_ = nullptr;
  tail_ = nullptr;
  for (size_t i = 0; i < n; i++)
  {
    pushBack(value);
  }
}

template< typename T >
litsinger::List< T >::List(const List< T >& otherList)
{
  head_ = nullptr;
  tail_ = nullptr;
  Node* head = otherList.head_;
  while (head)
  {
    pushBack(head->data);
    head = head->next;
  }
}

template< typename T >
litsinger::List< T >::List(List&& otherList)
{
  head_ = otherList.head_;
  tail_ = otherList.tail_;
  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;
}

template< typename T >
litsinger::List< T >::~List()
{
  clear();
}

template< typename T >
void litsinger::List< T >::pushFront(const T& data)
{
  Node* node = new Node(data);
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
void litsinger::List< T >::pushBack(const T& data)
{
  Node* node = new Node(data);
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
size_t litsinger::List< T >::getSize()
{
  Node* head = head_;
  size_t size = 0ull;
  while (head)
  {
    size++;
    head = head->next;
  }
  return size;
}


template< typename T >
void litsinger::List< T >::popFront()
{
  if (head_ == tail_)
  {
    delete tail_;
    head_ = tail_ = nullptr;
  }
  if (head_ != nullptr)
  {
    Node* node = head_;
    head_ = node->next;
    delete node;
  }
}

template< typename T >
bool litsinger::List< T >::isEmpty() noexcept
{
  return head_ == nullptr ? true : false;
}

template< typename T >
void litsinger::List< T >::clear()
{
  while (head_)
  {
    popFront();
  }
}

template< typename T >
void litsinger::List< T >::swap(List< T >& otherList) noexcept
{
  std::swap(head_, otherList.head_);
  std::swap(tail_, otherList.tail_);
}

template< typename T >
void litsinger::List< T >::assign(size_t n, const T& value)
{
  clear();
  for (size_t i = 0; i < n; i++)
  {
    push_back(value);
  }
}

template< typename T >
void litsinger::List< T >::remove(const T& value)
{
  ConstIterator iterator = cbegin();
  Node* nextNode = iterator.node->next;
  Node* toRemove = nullptr;
  if (!isEmpty())
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
void litsinger::List< T >::removeIf(P p)
{
  ConstIterator iterator = cbegin();
  Node* nextNode = iterator.node->next;
  Node* toRemove = nullptr;
  if (!isEmpty())
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
T& litsinger::List< T >::front()
{
  return head_->data;
}

template< typename T >
T& litsinger::List< T >::back()
{
  return tail_->data;
}

template< typename T >
typename litsinger::List< T >::ConstIterator litsinger::List< T >::operator[](const int index)
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
typename litsinger::List< T >::Iterator litsinger::List< T >::begin() const
{
  return Iterator(head_);
}

template< typename T >
typename litsinger::List< T >::Iterator litsinger::List< T >::end() const
{
  return Iterator(tail_->next);
}

template< typename T >
typename litsinger::List< T >::ConstIterator litsinger::List< T >::cbegin() const
{
  return ConstIterator(head_);
}

template< typename T >
typename litsinger::List< T >::ConstIterator litsinger::List< T >::cend() const
{
  return ConstIterator(tail_->next);
}

#endif
