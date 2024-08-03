#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <iostream>

namespace sobolevsky
{

  template< typename T >
  class List
  {
  public:
    class Node;
    class Iterator;

    List();
    List(const T &val);
    ~List();

    void pushFront(const T &data);
    void pushBack(const T &data);
    void popFront();
    void popBack();
    void clear();
    void remove(T val);
    void erase(Iterator position);
    void assign(size_t n, const T & val);
    bool empty();
    size_t size();
    Node *getAt(size_t index);
    T operator[](size_t index);
    Iterator begin() noexcept;
    Iterator end() noexcept;
  private:
    Node *head;
    Node *tail;
    size_t size_;
  };
}

template< typename T >
class sobolevsky::List< T >::Node
{
  friend class List;
public:
  Node(const T data):
    next(nullptr),
    prev(nullptr),
    data_(data)
  {}
private:
  Node *next;
  Node *prev;
  T data_;
};

template< typename T >
sobolevsky::List< T >::List()
{
  head = nullptr;
  tail = nullptr;
}

template< typename T >
sobolevsky::List< T >::List(const T &val)
{
  Node *ptr = new Node(val);
  head = ptr;
  tail = ptr;
}

template< typename T >
sobolevsky::List< T >::~List()
{
  clear();
}

template< typename T >
void sobolevsky::List< T >::pushFront(const T &data)
{
  Node *ptr = new Node(data);
  ptr->next = head;
  if (head != nullptr)
  {
    head->prev = ptr;
  }
  if (tail == nullptr)
  {
    tail = ptr;
  }
  head = ptr;
  size_++;
}

template< typename T >
void sobolevsky::List< T >::pushBack(const T &data)
{
  Node *ptr = new Node(data);
  ptr->prev = tail;
  if (tail != nullptr)
  {
    tail->next = ptr;
  }
  if (head == nullptr)
  {
    head = ptr;
  }
  tail = ptr;
  size_++;
}

template< typename T >
void sobolevsky::List< T >::popFront()
{
  if (head == nullptr)
  {
    return;
  }

  Node *ptr = head->next;
  if (ptr == nullptr)
  {
    tail = nullptr;
  }
  else
  {
    ptr->prev = nullptr;
  }

  delete head;
  size_--;
  head = ptr;
}

template< typename T >
void sobolevsky::List< T >::popBack()
{
  if (tail == nullptr)
  {
    return;
  }

  Node *ptr = tail->prev;
  if (ptr == nullptr)
  {
    head = nullptr;
  }
  else
  {
    ptr->next = nullptr;
  }

  delete tail;
  size_--;
  tail = ptr;
}

template< typename T >
void sobolevsky::List< T >::clear()
{
  while (head != nullptr)
  {
    popFront();
  }
}

template< typename T >
void sobolevsky::List< T >::remove(T val)
{
  Node *ptr = head;
  Node *tempPtr = nullptr;
  while (ptr != nullptr)
  {
    tempPtr = ptr->next;
    if (ptr->data_ == val)
    {
      if (ptr->prev == nullptr)
      {
        ptr->next->prev = ptr->prev;
        delete ptr;
      }
      else if (ptr->next == nullptr)
      {
        ptr->prev->next = ptr->next;
        delete ptr;
      }
      else
      {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
      }
    }
    ptr = tempPtr;
    size_--;
  }
}

template< typename T >
void sobolevsky::List< T >::erase(Iterator position)
{
  if (position.getNode()->prev == nullptr)
  {
    position.getNode()->next->prev = position.getNode()->prev;
    delete position.getNode();
  }
  else if (position.getNode()->next == nullptr)
  {
    position.getNode()->prev->next = position.getNode()->next;
    delete position.getNode();
  }
  else
  {
    position.getNode()->prev->next = position.getNode()->next;
    position.getNode()->next->prev = position.getNode()->prev;
    delete position.getNode();
  }
}

template< typename T >
void sobolevsky::List< T >::assign(size_t n, const T & val)
{
  clear();
  for (size_t i = 0; i < n; i++)
  {
    pushBack(val);
  }
}

template< typename T >
bool sobolevsky::List< T >::empty()
{
  return (size_ == 0);
}

template< typename T >
size_t sobolevsky::List< T >::size()
{
  return size_;
}

template< typename T >
typename sobolevsky::List< T >::Node *sobolevsky::List< T >::getAt(size_t index)
{
  Node *ptr = head;
  size_t n = 0;

  while(n != index)
  {
    if (ptr == nullptr)
    {
      return ptr;
    }
    ptr = ptr->next;
    n++;
  }

  return ptr;
}

template< typename T >
T sobolevsky::List< T >::operator [] (size_t index)
{
  return getAt(index)->data_;
}

template< typename T >
typename sobolevsky::List< T >::Iterator sobolevsky::List< T >::begin() noexcept
{
  return Iterator(head);
}

template< typename T >
typename sobolevsky::List< T >::Iterator sobolevsky::List< T >::end() noexcept
{
  return Iterator(nullptr);
}

template< typename T >
class sobolevsky::List< T >::Iterator
{
public:
  friend class List< T >;

  Iterator();
  Iterator(Node *ptr);
  Iterator(Iterator &&rhs);
  Iterator(const Iterator&) = default;
  ~Iterator() = default;

  Iterator &operator=(const Iterator&) = default;
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);

  T &operator*();
  T *operator->();

  bool operator==(const Iterator&) const;
  bool operator!=(const Iterator&) const;

  Node *getNode();
private:
  Node *node_;
};

template< typename T >
sobolevsky::List< T >::Iterator::Iterator()
{
  node_ = nullptr;
}

template< typename T >
sobolevsky::List< T >::Iterator::Iterator(Node *ptr)
{
  node_ = ptr;
}

template< typename T >
sobolevsky::List< T >::Iterator::Iterator(Iterator &&rhs)
{
  node_ = rhs.node_;
}

template < typename T >
typename sobolevsky::List< T >::Iterator &sobolevsky::List< T >::Iterator::operator++()
{
  node_ = node_->next;
  return *this;
};

template < typename T >
typename sobolevsky::List< T >::Iterator sobolevsky::List< T >::Iterator::operator++(int)
{
  Iterator temp(*this);
  ++(*this);
  return temp;
}

template < typename T >
typename sobolevsky::List< T >::Iterator &sobolevsky::List< T >::Iterator::operator--()
{
  node_ = node_->prev;
  return *this;
}

template < typename T >
typename sobolevsky::List< T >::Iterator sobolevsky::List< T >::Iterator::operator--(int)
{
  Iterator temp(*this);
  --(*this);
  return temp;
}

template< typename T >
T &sobolevsky::List< T >::Iterator::operator*()
{
  return node_->data_;
}

template< typename T >
T *sobolevsky::List< T >::Iterator::operator->()
{
  return std::addressof(node_->data_);
}

template< typename T >
bool sobolevsky::List< T >::Iterator::operator==(const Iterator &rhs) const
{
  return node_ == rhs.node_;
}

template< typename T >
bool sobolevsky::List< T >::Iterator::operator!=(const Iterator &rhs) const
{
  return node_ != rhs.node_;
}

template< typename T >
typename sobolevsky::List< T >::Node *sobolevsky::List< T >::Iterator::getNode()
{
  return node_;
}

#endif
