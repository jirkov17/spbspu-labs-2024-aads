#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <initializer_list>
#include <vector>
#include <sstream>

namespace gorbunova
{
  template < typename T >
  class List
  {
  private:
    template < typename D >
    struct Node
    {
      D data;
      Node< D > *next;
      Node(const D &value) : data(value), next(nullptr) {}
    };
    Node< T > *head;
    size_t size = 0;
  public:
    class ListIterator
    {
    public:
      using this_t = ListIterator;
      Node< T > *current;
      friend class List< T >;
      ListIterator(Node< T > *node) : current(node) {}
      T &operator*() const;
      ListIterator &operator++();
      ~ListIterator() {}
      ListIterator(const this_t &other) : current(other.current) {}
      this_t &operator=(const this_t &other)
      {
        if (this != &other)
          current = other.current;
        return *this;
      }
      this_t operator++(int)
      {
        this_t old = *this;
        ++(*this);
        return old;
      }
      bool operator==(const ListIterator &other) const
      {
        return current == other.current;
      }
      bool operator!=(const ListIterator &other) const
      {
        return current != other.current;
      }
      T *operator->() const
      {
        return &(current->data);
      }
    };
    List();
    List(std::initializer_list< std::pair< std::string, std::vector< unsigned long long > > > ilist);

    template < typename InputIterator >
    List(InputIterator first, InputIterator last);
    ~List();
    void push_back(const T &value);
    void clear();
    void assign(std::initializer_list<T> ilist);
    void splice(ListIterator pos, List &other);
    void reverse();
    void insert(ListIterator pos, const T &value);
    void erase(ListIterator pos);
    size_t getSize() const;
    ListIterator begin() const;
    ListIterator end() const;
  };
}

template < typename T >
T &gorbunova::List< T >::ListIterator::operator*() const
{
  return current->data;
}

template < typename T >
typename gorbunova::List< T >::ListIterator &gorbunova::List< T >::ListIterator::operator++()
{
  current = current->next;
  return *this;
}

template < typename T >
gorbunova::List< T >::List() : head(nullptr) {}

template < typename T >
gorbunova::List< T >::List(std::initializer_list<std::pair<std::string, std::vector< unsigned long long >>> ilist) : head(nullptr)
{
  for (const auto &pair : ilist)
  {
    push_back(pair);
  }
}

template < typename T >
template < typename InputIterator >
gorbunova::List< T >::List(InputIterator first, InputIterator last) : head(nullptr)
{
  while(first != last)
  {
    push_back(*first);
    ++first;
  }
}

template < typename T >
gorbunova::List< T >::~List()
{
  clear();
}

template < typename T >
size_t gorbunova::List< T >::getSize() const
{
  return size;
}

template < typename T >
void gorbunova::List< T >::push_back(const T &value)
{
  Node< T > *tmp = new Node< T >(value);
  size++;
  if (head == nullptr)
  {
    head = tmp;
  }
  else
  {
    Node< T > *curr = head;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = tmp;
  }
}

template < typename T >
void gorbunova::List< T >::clear()
{
  while (head != nullptr)
  {
    Node< T > *tmp = head;
    head = head ->next;
    delete tmp;
    size--;
  }
}

template < typename T >
void gorbunova::List< T >::assign(std::initializer_list< T > ilist)
{
  clear();
  for (const auto &value : ilist)
  {
    push_back(value);
  }
}

template < typename T >
void gorbunova::List< T >::splice(ListIterator pos, List &other)
{
  if (other.head != nullptr)
  {
    Node< T > *otherTail = other.head;
    while (otherTail->next != nullptr)
    {
      otherTail = otherTail->next;
    }
    otherTail->next = pos.current;
    pos.current = other.head;
    other.head == nullptr;
    other.size = 0;
  }
}

template < typename T >
void gorbunova::List< T >::reverse()
{
  Node< T > *prev = nullptr, *current = head, *next = nullptr;
  while (current != nullptr)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
}

template < typename T >
void gorbunova::List< T >::insert(ListIterator pos, const T &value)
{
  Node< T > *newNode = new Node< T >(value);
  newNode->next = pos.current->next;
  pos.current->next = newNode;
  size++;
}

template < typename T >
void gorbunova::List< T >::erase(ListIterator pos)
{
  Node< T > *toDelete = pos.current;
  pos.current = pos.current->next;
  delete toDelete;
  size--;
}

template < typename T >
typename gorbunova::List< T >::ListIterator gorbunova::List< T >::begin() const
{
  return ListIterator(head);
}

template < typename T >
typename gorbunova::List< T >::ListIterator gorbunova::List< T >::end() const
{
  return ListIterator(nullptr);
}
#endif
