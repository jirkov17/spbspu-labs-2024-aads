#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <cassert>

template< typename T >
class List
{
public:
  class iterator;
  class const_iterator;

  List();
  List(const List& other);
  List(List&& other) noexcept;
  ~List();

  List& operator=(const List& other);
  List& operator=(List&& other) noexcept;

  T& front();
  T& back();
  size_t get_size() const;
  void push_back(T val);
  bool empty() const;
  void clear();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

private:
  struct Node;
  Node* head;
  Node* tail;
  size_t size;
};

template< typename T >
struct List< T >::Node
{
  T value;
  Node* next;
  Node(T val, Node* next = nullptr);
};

template< typename T >
List< T >::Node::Node(T val, Node* next):
  value(val),
  next(next)
{}

template< typename T >
class List< T >::iterator: public std::iterator< std::forward_iterator_tag, T >
{
  typename List< T >::Node* ptr;
public:
  iterator(List< T >::Node* p = nullptr);
  iterator& operator++();
  bool operator!=(const iterator& other) const;
  T& operator*();
};

template< typename T >
List< T >::iterator::iterator(List< T >::Node* p):
  ptr(p)
{}

template< typename T >
typename List< T >::iterator::iterator& List<T>::iterator::operator++()
{
  assert(ptr);
  ptr = ptr->next;
  return *this;
}

template< typename T >
bool List< T >::iterator::operator!=(const iterator& other) const
{
  return ptr != other.ptr;
}

template< typename T >
T& List< T >::iterator::operator*()
{
  assert(ptr);
  return ptr->value;
}

template< typename T >
class List< T >::const_iterator: public std::iterator< std::forward_iterator_tag, T >
{
  const typename List< T >::Node* ptr;
public:
  const_iterator(const List< T >::Node* p = nullptr);
  const_iterator& operator++();
  bool operator!=(const const_iterator& other) const;
  const T& operator*() const;
};
template< typename T >
List< T >::const_iterator::const_iterator(const List< T >::Node* p):
  ptr(p)
{}

template< typename T >
typename List< T >::const_iterator& List< T >::const_iterator::operator++()
{
  assert(ptr);
  ptr = ptr->next; return *this;
}

template< typename T >
bool List< T >::const_iterator::operator!=(const const_iterator& other) const
{
  return ptr != other.ptr;
}

template< typename T >
const T& List< T >::const_iterator::operator*() const
{
  assert(ptr);
  return ptr->value;
}

template< typename T >
List< T >::List():
  head(nullptr),
  tail(nullptr),
  size(0)
{}

template< typename T >
List< T >::List(const List& other):
  head(nullptr),
  tail(nullptr),
  size(0)
{
    List< T >::Node* current = other.head;
    while (current != nullptr)
    {
      push_back(current->value);
      current = current->next;
    }
}

template< typename T >
List< T >::List(List&& other) noexcept:
  head(other.head),
  tail(other.tail),
  size(other.size)
{
  other.head = other.tail = nullptr;
  other.size = 0;
}

template< typename T >
typename List< T >::List& List< T >::operator=(const List& other)
{
  if (this != &other)
  {
    List tmp(other);
    swap(tmp);
  }
  return *this;
}

template< typename T >
typename List< T >::List& List< T >::operator=(List&& other) noexcept
{
  if (this != &other)
  {
    clear();
    head = other.head;
    tail = other.tail;
    size = other.size;
    other.head = other.tail = nullptr;
    other.size = 0;
  }
  return *this;
}

template< typename T >
List< T >::~List()
{
  clear();
}

template< typename T >
T& List< T >::front()
{
  if (empty())
  {
    throw std::logic_error("Empty");
  }
  return head->value;
}

template< typename T >
T& List< T >::back()
{
  if (empty())
  {
    throw std::logic_error("Empty");
  }
  return tail->value;
}

template< typename T >
size_t List< T >::get_size() const
{
  return size;
}

template< typename T >
void List< T >::push_back(T val)
{
  List< T >::Node* newNode = new List< T >::Node(val);
  if (tail) tail->next = newNode;
  else head = newNode;
  tail = newNode;
  ++size;
}

template< typename T >
bool List< T >::empty() const
{
  return size == 0;
}

template< typename T >
void List< T >::clear()
{
  while (head)
  {
    List< T >::Node* temp = head;
    head = head->next;
    delete temp;
  }
  head = tail = nullptr;
  size = 0;
}

template< typename T >
typename List< T >::iterator List< T >::begin()
{
  return iterator(head);
}

template< typename T >
typename List< T >::iterator List< T >::end()
{
  if (this == nullptr)
  {
    return nullptr;
  }
  else
  {
    return iterator(nullptr);
  }
}

template< typename T >
typename List< T >::const_iterator List< T >::begin() const
{
  return const_iterator(head);
}

template< typename T >
typename List< T >::const_iterator List< T >::end() const
{
  return const_iterator(nullptr);
}

#endif
